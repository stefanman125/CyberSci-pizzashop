/^\.Ss SELinux_Spec/,/^\.Ss [^S]/{;/^\.Ss [^S][^o][^l]/!d;};
/^On BSD systems/,/\.$/d
/^\.It use_loginclass$/,/^by default\./d
s/Solaris_Priv_Spec | //
/^Solaris_Priv_Spec ::=/ {
N
d
}
/^\.It \(limit\)*privs$/,/is built on Solaris 10 or higher\.$/d
/^On Solaris 10/,/^\.Pp/d
s/SELinux_Spec | //
/^SELinux_Spec ::=/ {
N
d
}
/^\.It [rt][oy][lp]e$/,/is built with SELinux support\.$/d
