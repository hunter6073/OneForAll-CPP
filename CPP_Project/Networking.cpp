// this script contains the features and usage of Boost.Asio to perform networking programming, the code used here is 
// taken from microsoft's winsock documentation. unix/linux based c++ network programming can be done by looking at the code
// on geeks for geeks https://www.geeksforgeeks.org/socket-programming-cc/

// ifndef means if not defined, the #ifndef endif is a pre defined if statement, normal usage also include ifdef
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define DEFAULT_PORT "3030" // define a default port for connection
#define DEFAULT_HOST "127.0.0.1" // define a default host for connection
#define DEFAULT_BUFLEN 512 // define default buffer length to be 512 bytes
// libraries to handle socket programming
# include <windows.h>
# include <winsock2.h>
# include <ws2tcpip.h>
# include <iphlpapi.h>
# include <stdio.h>
# include <iostream>
# include <thread> // library for threds

// put Ws2_32.lib into library
#pragma comment(lib, "Ws2_32.lib") 
using namespace std;

void startclient() {

	WSADATA wsaData; // The WSADATA structure contains information about the Windows Sockets implementation
	int iResult; // integer to get return result of different operation

	// Initialize Winsock, The WSAStartup function is called to initiate use of WS2_32.dll
	// The MAKEWORD(2, 2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system,
	// and sets the passed version as the highest version of Windows Sockets support that the caller can use.
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); 
	if (iResult != 0) { // if WSAStartup fails and wsaData is not initiated, all following operations will not be able to proceed
		printf("WSAStartup failed: %d\n", iResult);
		return;
	}

	// Declare an addrinfo object that contains a sockaddr structure and initialize these values.
	// For this application, the Internet address family is unspecified so that either an IPv6 or IPv4 address can be returned.
	// The application requests the socket type to be a stream socket for the TCP protocol.
	struct addrinfo *result = NULL,	*ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));// zeromemory is used to allocate a memory space and fill it with zeroes
	hints.ai_family = AF_UNSPEC; // address family left unspecified, could be IPV4 or IPV6, IPV4 flag is  AF_INET and IPV6 flag is AF_INET6
	hints.ai_socktype = SOCK_STREAM; // request the socket type to be a stream socket
	hints.ai_protocol = IPPROTO_TCP; // use TCP protocol

	// Call the getaddrinfo function to resolve the given address using 
	// the set up hints, the end result will be stored in *result pointer
	// The function returns its value as an integer that is later checked for errors.
	iResult = getaddrinfo(DEFAULT_HOST, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup(); // WSACleanup is used to terminate the use of the WS2_32 DLL.
		return;
	}

	SOCKET ConnectSocket = INVALID_SOCKET; //Create a SOCKET object called ConnectSocket with default value set as an invalid socket
	ptr = result; // pointer *ptr points to the *result pointer after resolving the address and port
	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	// if the socket creation fails, it returns INVALID_SOCKET, in this step there are no actual connection to the server
	if (ConnectSocket == INVALID_SOCKET) {
		// WSAGetLastError returns an error number associated with the last error that occurred
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result); // free address info from the result pointer
		WSACleanup();
		return;
	}

	// Call the connect function to connect to the server, passing the created socket and the sockaddr structure as parameters
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) { // if there is a socket error result
		closesocket(ConnectSocket); // close the socket
		//ConnectSocket = INVALID_SOCKET; // change ConnectSocket into an invalid socket
		freeaddrinfo(result);
		printf("Unable to connect to server!\n");
		WSACleanup();
		return;
	}

	/*
	The send and recv functions both return an integer value of the number of bytes sent or received, respectively,
	or an error. Each function also takes the same parameters:
	the active socket, a char buffer, the number of bytes to send or receive, and any flags to use.
	*/

	int recvbuflen = DEFAULT_BUFLEN; // get buffer length for receiving
	const char* sendbuf = "this is a test"; // a test string to send
	char recvbuf[DEFAULT_BUFLEN]; // receive buffer consisting of 512 chars

	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0); // Send an initial buffer
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return;
	}
	// if the send is successful, print iResult, which returns the amount of bytes sent
	printf("Bytes Sent: %ld\n", iResult);

	// shutdown the connection for sending since no more data will be sent
	// the client can still use the ConnectSocket for receiving data
	iResult = shutdown(ConnectSocket, SD_SEND); // the flag for receive is SD_RECEIVE, for both the flag is SD_BOTH
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return;
	}

	// Receive data until the server closes the connection
	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			cout << "content is" << recvbuf << endl;
		}
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());
	} while (iResult > 0);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();


}

void startserver() {
	WSADATA wsaData;
	int iResult;
	// Create a SOCKET object called ListenSocket for the server to listen for client connections.
	SOCKET ListenSocket = INVALID_SOCKET;
	// Create a temporary SOCKET object called ClientSocket for accepting connections from clients.
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL, hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
	}

	// initalizing hints variable with socket information
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port, NULL means using 0.0.0.0 for broadcasting
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	// Setup the TCP listening socket by calling the bind function, will allow the program to listen on selected ports
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	// The freeaddrinfo function is called to free the memory allocated by the getaddrinfo function for this address information.
	freeaddrinfo(result);

	/*
	Call the listen function, passing as parameters the created socket and a value for the backlog,
	maximum length of the queue of pending connections to accept. 
	In this example, the backlog parameter was set to SOMAXCONN. 
	This value is a special constant that instructs the Winsock provider 
	for this socket to allow a maximum reasonable number of pending connections in the queue.
	*/
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}


	/*
	Normally a server application would be designed to listen for connections from multiple clients. 
	For high-performance servers, multiple threads are commonly used to handle the multiple client connections.
	There are several different programming techniques using Winsock that can be used to listen for multiple client connections.
	One programming technique is to create a continuous loop that checks for connection requests using the listen function (see Listening on a Socket). 
	If a connection request occurs, the application calls the accept, AcceptEx, 
	or WSAAccept function and passes the work to another thread to handle the request. Several other programming techniques are possible.
	Note that this basic example is very simple and does not use multiple threads.
	The example also just listens for and accepts only a single connection.
	*/

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}
	/*
	When the client connection has been accepted,
	a server application would normally pass the accepted client socket (the ClientSocket variable in the above sample code)
	to a worker thread or an I/O completion port and continue accepting additional connections. In this basic example, 
	the server continues to the next step.
	There are a number of other programming techniques that can be used to listen for and accept multiple connections. 
	These include using the select or WSAPoll functions. 
	Examples of some of these various programming techniques are illustrated in the Advanced Winsock Samples 
	included with the Microsoft Windows Software Development Kit (SDK).
	*/


	// No longer need server socket
	closesocket(ListenSocket);


	/*
	The send and recv functions both return an integer value of the number of bytes sent or received, respectively,
	or an error. Each function also takes the same parameters: the active socket, a char buffer,
	the number of bytes to send or receive, and any flags to use.
	*/
	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return;
		}

	} while (iResult > 0);


	/*
	When the server is done sending data to the client, 
	the shutdown function can be called specifying SD_SEND to shutdown the sending side of the socket. 
	This allows the client to release some of the resources for this socket. 
	The server application can still receive data on the socket.
	*/
	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return;
	}

	/*
	When the client application is done receiving data, the closesocket function is called to close the socket.
	When the client application is completed using the Windows Sockets DLL, the WSACleanup function is called to release resources.
	*/
	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

}


void ShowNetworking() {
	// use two threads to start both the server and the client

	thread thserver(startserver);
	thread thclient(startclient);
	thserver.join();

	thclient.join();

}