#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<windows.h>
#include<locale.h>
#include<time.h>
#include"gotoxy.h"
#include"estructuras.h"
#include"usuarios.h"
#include"libros.h"
#include"prestamos.h"
#include"multas.h"

int main()
{
	int sn,opc,cantusuarios=0,cantlibros=0,cantprestamos=0,cantmultas=0;
	float valormulta;
	char aux[30];
	struct usuarios usuarios[100];
	struct biblio libros[100];
	struct prestamo prestamos[200];
	struct multa multas[200];
	
	//Maximizar el tamaño de la consola
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd,SW_SHOWMAXIMIZED);
	// Establecer el idioma a español
	setlocale(LC_ALL, "spanish");
	
	//Se leen los datos
	cantlibros=contarlibros(libros);
	cantusuarios=lecturausuarios(usuarios,cantusuarios);
	cantprestamos=lecturaprestamos(prestamos,cantprestamos);
	valormulta=lecturavalor(multas,cantmultas);
	cantmultas=lecturamultas(multas,cantmultas,prestamos,cantprestamos,usuarios,cantusuarios);
	impresionmultas(multas,cantmultas,valormulta);
	impresionusuarios(usuarios,cantusuarios);
	printf("\n\n\n\n\n\t\t\t\t\t SISTEMA DE LA BIBLIOTECA\n\n\n\n\n\t\t\t\t\t BIENVENIDO\n\n\n\n\n\t\t\t");
	system("pause");
	do
	{
		system("cls");
		printf("\n\n\n\t\t MENU PRINCIPAL:");
		printf("\n\n\t\t Seleccione un menu");
		printf("\n\t\t 1) Menu de usuarios");
		printf("\n\t\t 2) Menu de libros");
		printf("\n\t\t 3) Menu de prestamos");
		printf("\n\t\t 4) Menu de multas");
		printf("\n\t\t 5) Salir");
		printf("\n\n\t\t Escriba el numero de su eleccion: ");
		do
		{
			do
			{
				gets(aux);
				if(validar_entero(aux)==1)
					printf("\n\n\t Introduzca un numero entero mayor a cero: ");
			}while(validar_entero(aux)==1);
			opc=atoi(aux);
			if(opc<1||opc>5)
				printf("\n\n\t Introduzca un numero del 1 al 5: ");
		}while(opc<1||opc>5);
		
		switch(opc)
		{
			case 1:
				cantusuarios=usus(usuarios,cantusuarios);
				break;
			case 2:
				cantlibros=libs(libros,cantlibros,prestamos,cantprestamos);
				break;
			case 3:
				cantprestamos=prests(libros,usuarios,prestamos,cantlibros,cantusuarios,cantprestamos,multas,cantmultas,valormulta);
				break;	
			case 4:
				valormulta=multax(multas,cantmultas,valormulta);
				cantmultas=lecturamultas(multas,cantmultas,prestamos,cantprestamos,usuarios,cantusuarios);
				break;
			case 5:
				break;
			default:
				printf("\n Opcion incorrecta");
		}
		if(opc==5)
		{
			printf("\n Esta seguro de salir? [1.-Si - 2.-No]: ");
			do
			{
				sn=validar();
				if(sn!=1&&sn!=2)
					printf("\n\t Introduzca 1 o 2: ");
			}while(sn!=1&&sn!=2);
			if(sn==2)
				opc=1;
		}
	}while(opc!=5);
	return 0;
}
