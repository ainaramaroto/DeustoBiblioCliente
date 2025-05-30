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
	char opcion, opcionAdminInicio, usuario[50], contrasenia[50], dni[10], nombre[20], apellido[20], email[50], numeroTlf[10], direccion[50],
		opcionClienteInicio, opcionClientePrincipal, titulo[100]																										 ;
	int intentos = 3, resultado, encontrado;
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
					cout<<"Introduce tu contraseña ( " << intentos << " intentos restantes): " <<endl;
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
		case '2':
					do {
						opcionClienteInicio = menuClienteInicio();
						sprintf(sendBuff, "%c", opcionClienteInicio); //almacena opción
						send(s, sendBuff, sizeof(sendBuff), 0); //enviar

						//recv(s, recvBuff, sizeof(recvBuff), 0);  //recibir
						//cout << recvBuff << endl;

						switch (opcionClienteInicio) {
						case '1':  //HECHO Y SE VISUALIZA
							cout << "Introduce tu DNI: ";
							cin >> dni;
							cout << "Introduce tu contraseña: ";
							cin >> contrasenia;
							//VARIABLES DNI Y CONTRASEÑA MANDADAS
							sprintf(sendBuff, "%s", dni); //almacena opción
							send(s, sendBuff, sizeof(sendBuff), 0); //enviar
							sprintf(sendBuff, "%s", contrasenia); //almacena opción
							send(s, sendBuff, sizeof(sendBuff), 0); //enviar

							recv(s, recvBuff, sizeof(recvBuff), 0);
							cout << recvBuff << endl;

							recv(s, recvBuff, sizeof(recvBuff), 0);
							sscanf(recvBuff, "%d", &encontrado);
							cout<<encontrado<<endl;
							if (encontrado) {
								do {
									opcionClientePrincipal = menuPrincipalCliente();
									sprintf(sendBuff, "%c", opcionClientePrincipal); //almacena opción
									send(s, sendBuff, sizeof(sendBuff), 0); //enviar
									//recv(s, recvBuff, sizeof(recvBuff), 0);  //recibir
									//cout << recvBuff << endl;

									switch (opcionClientePrincipal) {
									case '1':
										//VER PERFIL
										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout << recvBuff;

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout << recvBuff;

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout << recvBuff;

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout << recvBuff;

										break;
							case '2':
										recv(s, recvBuff, sizeof(recvBuff), 0); //VISUALIZAR VER LIBROS DISPONIBLES
										cout << recvBuff;

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout << recvBuff;

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout << recvBuff;

										recv(s, recvBuff, sizeof(recvBuff), 0);
										int fin;
										sscanf(recvBuff, "%d", &fin);

										while (fin == 0) {
											recv(s, recvBuff, sizeof(recvBuff), 0);
											cout << recvBuff;
											recv(s, recvBuff, sizeof(recvBuff), 0);
											sscanf(recvBuff, "%d", &fin);

										}

										//IF(COUNT == 0)
										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout << recvBuff;

										break;
									case '3':
										//VISUALIZAR: RESERVAR LIBROS
										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;

										cout<<"Introduce el título del libro que quieres alquilar: ";
										cin.ignore();
										cin.getline(titulo, sizeof(titulo));

										strcpy(sendBuff, titulo);
										send(s, sendBuff, strlen(sendBuff)+1, 0);

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;

										break;

									case '4':
										//VISUALIZAR DEVOLVER LIBRO
										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;

										cout<<"Introduce el titulo del libro que quieres devolver: ";
										cin.ignore();
										cin.getline(titulo, sizeof(titulo));
										strcpy(sendBuff, titulo);
										send(s, sendBuff, strlen(sendBuff)+1, 0);

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;

										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;

										break;

									case '5':
										//VISUALIZA VER LIBROS RESERVADOS
										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;

										recv(s, recvBuff, sizeof(recvBuff),0);
										cout<<recvBuff;

										recv(s, recvBuff, sizeof(recvBuff),0);
										cout<<recvBuff;

										//recv(s, recvBuff, sizeof(recvBuff),0);
										//cout<<recvBuff;

										break;

									case '0':
										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;
										break;

									default://MIRAR POR QUE NO SALE ESTE MENSAJE
										recv(s, recvBuff, sizeof(recvBuff), 0);
										cout<<recvBuff;

									}
								} while (opcionClientePrincipal != '0');
							}
							break;
					case '2':
							printf("Introduce DNI:");
							cin.ignore();
							cin.getline(dni, sizeof(dni));
							strcpy(sendBuff, dni);
							send(s, sendBuff, strlen(sendBuff)+1, 0);

							recv(s, recvBuff, sizeof(recvBuff), 0);
							sscanf(recvBuff, "%d", &encontrado);

							if(encontrado == 1){
								printf("\033[1;32m El usuario con DNI %s ya está registrado.\033[0m\n", dni);
								break;
							}

							printf("Introduce nombre:");
							cin.getline(nombre, sizeof(nombre));
							strcpy(sendBuff, nombre);
							send(s, sendBuff, strlen(sendBuff)+1, 0);

							printf("Introduce apellido: ");
							cin.getline(apellido, sizeof(apellido));
							strcpy(sendBuff, apellido);
							send(s, sendBuff, strlen(sendBuff)+1, 0);

							printf("Introduce email: ");
							cin.getline(email, sizeof(email));
							strcpy(sendBuff, email);
							send(s, sendBuff, strlen(sendBuff)+1, 0);

							printf("Introduce contraseña: ");
							cin.getline(contrasenia, sizeof(contrasenia));
							strcpy(sendBuff, contrasenia);
							send(s, sendBuff, strlen(sendBuff)+1, 0);

							printf("Introduce número de teléfono: ");
							cin.getline(numeroTlf, sizeof(numeroTlf));
							strcpy(sendBuff, numeroTlf);
							send(s, sendBuff, strlen(sendBuff)+1, 0);

							printf("Introduce dirección: ");
							cin.getline(direccion, sizeof(direccion));
							strcpy(sendBuff, direccion);
							send(s, sendBuff, strlen(sendBuff)+1, 0);

							recv(s, recvBuff, sizeof(recvBuff), 0);
							cout<<recvBuff;
							break;
						}

					} while (opcionClienteInicio != '0');
					break;
				}

	}while(opcion!='0');


	/*ACABA EL PROGRAMA DEL CLIENTE*/
	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}




