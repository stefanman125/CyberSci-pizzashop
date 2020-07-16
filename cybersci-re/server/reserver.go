package main

import (
	"log"
	"net"
	"strings"
)


func main() {
	l, err := net.Listen("tcp", ":4444")
	if err != nil {
		log.Panicln(err)
	}
	log.Println("Listening")
	defer l.Close()

	for {
		conn, err := l.Accept()
		if err != nil {
			log.Panicln(err)
		}

		go handleRequest(conn)
	}
}

func handleRequest(conn net.Conn) {
	log.Println("Accepted new connection.")
	defer conn.Close()
	defer log.Println("Closed connection.")

	// Intro
	introText := "In order to get the secret Pizza formula find the binary at https://qq.qq/b.exe and enter the secret password\n\n\n"
	conn.Write([]byte(introText))

	for {
		buf := make([]byte, 1024)
		size, err := conn.Read(buf)
		if err != nil {
			return
		}
		data := buf[:size]

		flagValue := string(data)
		flagValue = strings.TrimSuffix(flagValue, "\n")

		correctFlag := "flag{dbb936cf3d5c4bf6f0d144997d93c924}"
		secretKey := "supersecretpizzapassword"

		if strings.Compare(flagValue, secretKey) == 0 {
			log.Println("LOG: Input correct")
			conn.Write([]byte(correctFlag))
			break // Disconnect user when they get the secret
		} else {
			log.Println("LOG: Input wrong")
			conn.Write([]byte("Sorry, try again\n"))
		}
	}
}
