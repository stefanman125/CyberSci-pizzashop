#include <iostream>
#include <vector>
#include <Windows.h>
#include <Iphlpapi.h>
#include <Assert.h>
#include <Lmcons.h>
#pragma comment(lib, "iphlpapi.lib")


// Typedef for shutdown API, used when I perform dynamic DLL loading
typedef void(_stdcall* InitiateSystemShutdownExAFormat)(LPSTR lpMachineName,
    LPSTR lpMessage,
    DWORD dwTimeout,
    BOOL  bForceAppsClosed,
    BOOL  bRebootAfterShutdown,
    DWORD dwReason
    );


/// <summary>
/// Detect if we are running in a hypervisor by probing CPUID response
/// </summary>
/// <returns>Will retrun an Integer. 1 -> In Hypervisor 0 -> Not Hypervisor</returns>
__declspec(naked) bool cpuidHypervisorCheck() {
    __asm {
        ; Zero out ECX output register
        xor ecx, ecx

        ; call cpuid with argument in EAX
        mov eax, 1; Indicates we want version Information : Type, Family, Model, and Stepping

        ; Page 292 for CPUID - https://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-instruction-set-reference-manual-325383.pdf
        cpuid 

        ; "Intel and AMD CPUs have reserved bit 31 of ECX of CPUID leaf 0x1 as the hypervisor present bit" - https://kb.vmware.com/s/article/1009458
        ; Sets CF depending on the 31st bit in ECX, 1 indicates its a hypervisor
        bt ecx, 31

        ; set AL to the value of CF
        setc al

        ; return from function
        retn
    }
}

/// <summary>
/// Check MAC addressess against blacklisted hypervisor MAC addresess
/// </summary>
/// <param name="macAddressToCheck"></param>
/// <returns></returns>
bool isMacAddressBlacklisted(char *macAddressPassed) {

    // Blacklisted MAC addresess
    /// https://blog.talosintelligence.com/2018/04/gravityrat-two-year-evolution-of-apt.html
    /// https://1.bp.blogspot.com/-AG6M5oChPus/Wt7M2wcMVyI/AAAAAAAAAYU/NtT04MdbZmYit7d7wBZPVZZYfBiBsPNBwCLcBGAs/s1600/image15.png
    std::vector<std::string> blacklistedMACS = {
        "00:50:56",  // VMware
        "00:0C:29",  // VMware
        "00:05:69",  // VMware
        "08:00:27",  // Virtualbox
        "00:1C:42",  // Parallels, Inc.
        "00:16:3E",  // Xensource, Inc.

        // WSL creates a NAT interface with this prefix, so it may generate a false postive. To lazy to add checks and what not. 
        // But who uses WSL anyway, right?
        "00:15:5D"   // Hyper-V  https://macaddress.io/faq/how-to-recognise-a-microsoft-hyper-v-virtual-machine-by-its-mac-address
    };



    std::string macAddressString = std::string(macAddressPassed);
    std::string macAddressPrefix = macAddressString.substr(0, 8);

    // If the MAC address prefix matches any that are blacklisted, return true
    for (std::string blacklistedMAC : blacklistedMACS)
    {
        if (blacklistedMAC.compare(macAddressPrefix) == 0) {
            return true;
        }
    }

    return false;
}

/// <summary>
/// Check MAC address prefix for known hypervisor vendors
/// Found on Stackoverflow and altered a bit
/// https://stackoverflow.com/questions/13646621/how-to-get-mac-address-in-windows-with-c
/// </summary>
/// <returns>Boolean</returns>
bool macAddressHypervisorCheck() {
    PIP_ADAPTER_INFO AdapterInfo;
    DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
    char* mac_addr = (char*)malloc(18);

    AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    if (AdapterInfo == NULL) {
        free(mac_addr);
        return NULL; // it is safe to call free(NULL)
    }

    // Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(AdapterInfo);
        AdapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufLen);
        if (AdapterInfo == NULL) {
            free(mac_addr);
            return NULL;
        }
    }

    // AdapterInfo is a linked list, so we traverse this list
    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
        // Contains pointer to current adapter info
        PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
        do {
            // technically should look at pAdapterInfo->AddressLength
            //   and not assume it is 6.
            sprintf_s(mac_addr, 18, "%02X:%02X:%02X:%02X:%02X:%02X",  // Changed to sprintf_s, added 18 bytes max as specfied in the beginning
                pAdapterInfo->Address[0], pAdapterInfo->Address[1],
                pAdapterInfo->Address[2], pAdapterInfo->Address[3],
                pAdapterInfo->Address[4], pAdapterInfo->Address[5]);


            // Check if the MAC address is blacklisted
            if (isMacAddressBlacklisted(mac_addr)) {
                return true;
            }


            // Go to next element in the linked list
            pAdapterInfo = pAdapterInfo->Next;
        } while (pAdapterInfo);
    }
    free(AdapterInfo);
    free(mac_addr);

    return false; // If we got to this point, there is no match on the MAC addressess
}


/// <summary>
/// Shutdown the computer
/// </summary>
void shutdownComputer() {


    /*
    
    Our first goal is to get SeShutdownPrivilege for the current procesess.
    This should not be a problom, running as non admin usually even has this privivlige.
    
    */

    HANDLE hToken;              // handle to process token 
    TOKEN_PRIVILEGES tkp;       // pointer to token structure 

   // Get the current process token handle so we can get shutdown 
   // privilege. 
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        return;
    }

    // Get the LUID for shutdown privilege. 
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1;  // one privilege to set    
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // Get shutdown privilege for this process. 
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
        (PTOKEN_PRIVILEGES)NULL, 0);

    // Cannot test the return value of AdjustTokenPrivileges. 
    if (GetLastError() != ERROR_SUCCESS)
        return;

    /*
    
    Our next step is to link the DLL with the InitiateSystemShutdownExA function and run it
    Note, Dynamic DLL loading is being used here to hide the fact that we are using the InitiateSystemShutdownExA function
    
    */

    // Load Advapi32.dll which contains windows.h which defines GetUserNameA
    LPCSTR dllPath = "C:\\Windows\\System32\\advapi32.dll";
    HINSTANCE hGetProcIDLL = LoadLibraryA(dllPath);

    // Check if DLL loaded
    if (!hGetProcIDLL) {
        //std::cout << "Could not load DLL library" << std::endl;
        // TODO Maybe do something else rather then return, but in theory it should succeed
        return;
    }

    //Resolve function address
    InitiateSystemShutdownExAFormat InitiateSystemShutdownExAPointer = (InitiateSystemShutdownExAFormat)GetProcAddress(hGetProcIDLL, "InitiateSystemShutdownExA");
    if (!InitiateSystemShutdownExAPointer) {
        //std::cout << "Could not locate the function" << std::endl;
        // TODO Maybe do something else rather then return, but in theory it should succeed
        return;
    }

    // Run shutdown command
    InitiateSystemShutdownExAPointer(NULL, NULL, 0, TRUE, FALSE, SHTDN_REASON_FLAG_PLANNED);
}

/// <summary>
/// 
/// </summary>
void beginSecretCheck() {

    // Secret is supersecretpizzapassword
    // Each ASCII value is incremented by 4 to get the encoded string
    std::string encodedSecret = "wytivwigvixtm~~eteww{svh";


    for (int i = 0; i < 5; i++) {

        std::string userInput;
        std::cout << "Please say the magic word: ";
        std::cin >> userInput;

        // If size does not match, wrong input
        if (encodedSecret.length() != userInput.length()) {
            std::cout << "Wrong\n";
            continue;
        }
        else {

            // If incrementing by 4 on input string does not match, wrong input
            for (size_t i = 0; i < userInput.length(); i++) {

                if (encodedSecret[i] != (userInput[i] + 4)) {
                    std::cout << "Wrong\n";
                    continue;
                }
            }
        }

        // If we get here means the input is correct
        std::cout << "Correct! Type that into the remote server\n";
        break;

    }
}

int main()
{


    if (cpuidHypervisorCheck() || macAddressHypervisorCheck()) {
        shutdownComputer();
        return 0;
    }

    beginSecretCheck();
    

}
