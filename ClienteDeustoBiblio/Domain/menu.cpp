#include <iostream>
using namespace std;

char menuPrincipal(){
	char opcion;

	cout<<"Bienvenid@ a DeustoBiblio"<<endl;
	cout<<"Menu Principal\n"<<endl;
	cout<<"1. Administrador\n"<<endl;
	cout<<"2. Cliente\n"<<endl;
	cout<<"0. Salir\n"<<endl;
	cout<<"\033[1;36mElige una opción: \033[0m"<<endl;

	cin>>opcion;
	return opcion;
}


char menuClienteInicio(){
	char opcion;

	cout<<"\033[1;36mMenu Inicio de Sesión de Cliente\n\033[0m"<<endl;
	cout<<"1. Iniciar Sesión\n"<<endl;
	cout<<"2. Registrarse\n"<<endl;
	cout<<"0. Salir\n"<<endl;
	cout<<"\033[1;36mElige una opción: \033[0m"<<endl;

	cin>>opcion;
	return opcion;

}


char menuPrincipalCliente(){
	char opcion;

	cout<<"\033[1;36mMenu Principal del Cliente\n\033[0m"<<endl;
	cout<<"1. Ver Perfil\n"<<endl;
	cout<<"2. Ver libros disponibles\n"<<endl;
	cout<<"3. Reservar libros\n"<<endl;
	cout<<"4. Devolver libros\n"<<endl;
	cout<<"5. Libros Reservados\n"<<endl;
	cout<<"0. Salir\n"<<endl;
	cout<<"\033[1;36mElige una opción: \033[0m"<<endl;

	cin>>opcion;
	return opcion;

}

char menuAdministradorInicio(){
	char opcion;

	cout<<"\033[1;36mMenu Inicio de Sesión del Administrador\n\033[0m"<<endl;
	cout<<"1. Iniciar Sesión\n"<<endl;
	cout<<"0. Salir\n"<<endl;
	cout<<"\033[1;36mElige una opción:\033[0m "<<endl;

	cin>>opcion;
	return opcion;

}

char menuPrincipalAdministrador(){
	char opcion;

	cout<<"\033[1;36mMenu Principal del Administrador\n\033[0m"<<endl;
	cout<<"1. Eliminar libro\n"<<endl;
	cout<<"2. Visualizar datos de los cliente\n"<<endl;
	cout<<"3. Visualizar datos de los libros\n"<<endl;
	cout<<"0. Salir\n"<<endl;
	cout<<"\033[1;36mElige una opción: \033[0m"<<endl;

	cin>>opcion;
	return opcion;
}




