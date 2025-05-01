// IMPORTANT: Winsock Library ("ws2_32") should be linked
//Un socket es un mecanimo de comunicaci�n entre 2 procesos cualesquiera
#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include "domain/menu.h"
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
using namespace std;

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	/*
	 * En sendBuff guardaremos lo que el cliente le env�a al servidor
	 * En recvBuff guardaremos lo que el servidor le env�a al cliente
	 * */
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	/*EMPIEZA EL PROGRAMA DEL CLIENTE*/
	char opcion, opcionAdminInicio, usuario[50], contrasenia[50];
	int intentos, resultado;
	do{
		opcion =  menuPrincipal();
		sprintf(sendBuff,"%c",opcion); //almacena opción
		send(s,sendBuff,sizeof(sendBuff),0); //enviar
		recv(s,recvBuff,sizeof(recvBuff),0);  //recibir
		cout<<recvBuff<<endl;
		switch(opcion){
		case '1':
			do{
				opcionAdminInicio = menuAdministradorInicio();
				sprintf(sendBuff,"%c",opcionAdminInicio); //almacena opción
				send(s,sendBuff,sizeof(sendBuff),0); //enviar
				recv(s,recvBuff,sizeof(recvBuff),0);  //recibir
				cout<<recvBuff<<endl;

				switch(opcionAdminInicio){
				case '1':
					recv(s,recvBuff,sizeof(recvBuff),0); //recibir
					sscanf(recvBuff, "%d", &intentos); //obtener
					recv(s,recvBuff,sizeof(recvBuff),0);
					sscanf(recvBuff, "%d", &resultado); //???

					cout<<"\033[1;36mIniciando sesion como administrador...\n\033[0m"<<endl;
					cout<<"Introduce tu nombre de usuario: "<<endl;
					cin>>usuario;
					cout<<"Introduce tu contraseña (" << intentos << "intentos restantes): " <<endl;
					cin>>contrasenia;
					sprintf(sendBuff,"%s",usuario); //almacenamos
					send(s,sendBuff,sizeof(sendBuff),0); //enviamos
					sprintf(sendBuff,"%s",contrasenia);  //almacenamos
					send(s,sendBuff,sizeof(sendBuff),0);  //enviamos
					//hacer el if
					recv(s,recvBuff,sizeof(recvBuff),0);
					cout<<recvBuff<<endl;
					recv(s,recvBuff,sizeof(recvBuff),0);
					sscanf(recvBuff,"%d", &resultado);

					while (resultado != 2 && intentos > 0){
						(intentos)--;
						if (resultado == 0){
							cout<<"Introduce tu usuario (" << intentos << "intentos restantes): " <<endl;
							cin>>usuario;

						} else if (resultado == 1){
							cout<<"Introduce tu contraseña (" << intentos << "intentos restantes): " <<endl;
							cin>>contrasenia;
						}
				}
				break;
				}
			}while (opcionAdminInicio != '0');
			break;
		}

	}while(opcion!='0');


	/*ACABA EL PROGRAMA DEL CLIENTE*/
	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}




