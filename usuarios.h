
int usus(struct usuarios usuarios[100],int cantusuarios)
{
	
	cantusuarios=menuusuario(usuarios,cantusuarios);
	
	impresionusuarios(usuarios,cantusuarios);
	
	return cantusuarios;
}
//_----------------------------------------------------------------------------
int lecturausuarios(struct usuarios usuarios[100],int cantusuarios) // esta funcion leera todos los usuarios del archivo y los pasara al struct usuarios, aparte de regresar la cantidad de usuarios.
{
	FILE *usuariofile;
	int i;
	char nombree[50];
	char direcc[100];
	usuariofile = fopen("usuarios.txt","r"); // Se checa que funcione correctamente.
	if(usuariofile == NULL)
	{
		usuariofile=fopen("usuarios.txt","w+"); //Si no funciona se abre en modo escritura
		if(usuariofile==NULL)
		{
			printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tError! Fallo en el sistema.\n\n\n\n\n"); 
			system("pause");  
			exit(1);    
		}
	}
	fscanf(usuariofile,"%s\n",&usuarios[cantusuarios].mat);
   	while(feof(usuariofile)==0) //Hasta el fin del archivo
   	{
   		fgets(nombree,50,usuariofile);
   		fgets(direcc,100,usuariofile);
   		// Borra el salto de linea
   		nombree[strlen(nombree)-1]=' ';
   		direcc[strlen(direcc)-1]=' ';
   		
   		strcpy(usuarios[cantusuarios].nombre,nombree);
   		strcpy(usuarios[cantusuarios].direc,direcc);
   		
   		fscanf(usuariofile,"%d\n%d",&usuarios[cantusuarios].estado,&usuarios[cantusuarios].cantlibros);

   		// printf("\n\nmat: %s nom:%s dir:%s estado:%d cantlib:%d",usuarios[cantusuarios].mat,usuarios[cantusuarios].nombre,usuarios[cantusuarios].direc,usuarios[cantusuarios].estado,usuarios[cantusuarios].cantlibros);

   		cantusuarios++;
   		fscanf(usuariofile,"%s\n",&usuarios[cantusuarios].mat);
	}
	fclose(usuariofile);
	return cantusuarios;
}
//_----------------------------------------------------------------------------------
int menuusuario(struct usuarios usuarios[100],int cantusuarios) // ESTE MENU SERA UN SUBMENU DEL MENU PRINCIPAL.
{
	
	/*
		ESTE SERA EL MENU DE USUARIOS, LO QUE HARA ES DIRIGIR A LOS SIGUIENTES FUNCIONES:
		AGREGAR USUARIOS.- AGREGARA UN USUARIO CON LA MATRICULA INGRESADA.
		MODIFICAR USUARIOS.-MODIFICA USUARIO INGRESANDO UNA MATRICULA EXISTENTE.
		BUSCAR USUARIO.- BUSCA UN USUARIO INGRESANDO UNA MATRICULA EXISTENTE.
		CONSULTA USUARIO.- SE CREA UNA LISTA DE TODOS LOS USUARIOS.
		REPORTES.- SE MANDA A UN SUBMENU, ESTE SUBMENU SERA DE LOS VARIOS REPORTES DE UN USUARIO.
		
	*/
	int op;
	do
	{
		system("cls");
		printf("\n\n\n\t\t MENU USUARIOS:");
		printf("\n\n\t\t 1) Agregar usuarios ");
		printf("\n\t\t 2) Modificar usuarios");
		printf("\n\t\t 3) Buscar un usuario por nombre");
		printf("\n\t\t 4) Consulta general de usuarios");
		printf("\n\t\t 5) Reportes de usuario");
		printf("\n\t\t 6) Volver al menu principal");
		printf("\n\n\t\t Escriba el numero de su eleccion: ");
		do
		{
			op=validar();
			
			if(op!=1 && op!=2 && op!=3 && op!=4 && op!=5 && op!=6)
				printf("\n\n\t Introduzca un numero del 1 al 5: \n");
		}	while(op!=1 && op!=2 && op!=3 && op!=4 && op!=5 && op!=6);
		
		switch(op)
		{
			case 1: cantusuarios=agusuario(usuarios,cantusuarios);	 // FUNCION AGREGAR USUARIO
					break;
			case 2:	modifusuario(usuarios,cantusuarios);	 // FUNCION MODIFICAR USUARIO
					break;
			case 3:	conusumatricula(usuarios,cantusuarios);			
					break;	
			case 4:	conusugen(usuarios,cantusuarios);	// CONSULTA GENERAL DE USUARIOS
					break;	
			case 5:	conusu(usuarios,cantusuarios);	// SUBMENU REPORTES DE USUARIOS
					break;
			case 6:	system("cls");
					gotoxy(20,20);
					printf("Volviendo al menu principal...");
					break;						
		}
			
	}	while (op!=6);
	return cantusuarios;
}
//_--------------------------------------------------------------------------------------------------
int agusuario(struct usuarios usuarios[100],int cantusuarios)
{
	/*
	 PRIMERO SE PIDE LA MATRICULA, ESTA MATRICULA NO TIENE QUE TENER '\t' PORQUE MUERE EL PROGRAMA, POR LO QUE NOS ASEGURAMOS DE QUE EL USUARIO NO HAYA PUESTO ESTO,
	 TAMBIEN CHECAMOS QUE LA MATRICULA NO SEA REPETIDA.
	 LUEGO INICIALIZAMOS EL ESTADO EN 0 (OSEASE NO TIENE MULTAS) Y LA CANTIDAD DE LIBROS PEDIDOS EN 0.
	FINALMENTE PREGUNTAMOS SI QUIERE AGREGAR OTRO USUARIO.
	
	*/
	int op,op2,i,boton=0;
	
	do
	{
		do
		{
			system("cls");
			printf("\n\n\n\t AGREGAR USUARIO");
			printf("\n\n\t Introduzca el identificador del usuario: ");
			do
			{
				
				fflush(stdin);
				gets(usuarios[cantusuarios].mat);
				
				// Se convierte a mayusculas
				for(i=0;usuarios[cantusuarios].mat[i]!='\0';i++)
					usuarios[cantusuarios].mat[i]=toupper(usuarios[cantusuarios].mat[i]);
				
				boton=0;
				
				for(i=0;i<strlen(usuarios[cantusuarios].mat);i++)  // CHECAMOS QUE NO HAYA PUESTO TABULADOR AL INGRESAR LA MATRICULA
					if(usuarios[cantusuarios].mat[i]=='\t' || usuarios[cantusuarios].mat[i]==' ')
					{
						boton=1;
						printf("\n Introduzca un identificador sin espacios: ");
						break;
					}
						
				for(i=0;boton!=1&&i<cantusuarios;i++)
					if(strcmp(usuarios[i].mat,usuarios[cantusuarios].mat)==0) // CHECAMOS QUE NO ESTÉ REPETIDA
					{
						boton=1;
						printf("\n\n\t El identificador esta repetido, introduzca otro: ");
						break;
					}
				
			} while(boton==1);
		
		
			printf("\n\n\t Introduzca el nombre: ");
			fflush(stdin);
			gets(usuarios[cantusuarios].nombre);
			
			for(i=0;usuarios[cantusuarios].nombre[i]!='\0';i++)
					usuarios[cantusuarios].nombre[i]=toupper(usuarios[cantusuarios].nombre[i]);
			
			printf("\n\n\t Introduzca la direccion: ");
			fflush(stdin);
			gets(usuarios[cantusuarios].direc);
			
			for(i=0;usuarios[cantusuarios].direc[i]!='\0';i++)
					usuarios[cantusuarios].direc[i]=toupper(usuarios[cantusuarios].direc[i]);
			
			usuarios[cantusuarios].estado=0; // INICIALIZAMOS SU ESTADO EN 0, PORQUE AL SER UN USUARIO NUEVO, NO TIENE MULTAS
			usuarios[cantusuarios].cantlibros=0; // INICIALIZAMOS SU ESTADO EN 0, PORQUE NO HA PEDIDO PRESTADO NADA

			do
			{
				printf("\n\n\t Son correctos los datos introducidos? [1.-Si 2.-No]:");
				op2=validar();
				if(op2!=1 && op2!=2)
					printf("\n Entrada incorrecta. ");
			}	while(op2!=1 && op2!=2);
			
		} while(op2==2);
		cantusuarios++; // AUMENTAMOS LA CANTIDAD TOTAL DE USUARIOS		
		
		do
		{
			printf("\n\n\t Desea agregar otro usuario? [1.- Si,2.- No]:");
			op=validar();	
			if(op2!=1 && op2!=2)
					printf("\n Entrada incorrecta. ");
		}	while(op!=1 && op!=2);
	}	while(op==1);
	printf("\n\nRegresando al menu principal...\n\n\n\n");
	return cantusuarios;
}
//-----------------------------------------------------------------------------------------
void modifusuario(struct usuarios usuarios[100],int cantusuarios)
{
	/*
		PRIMERO INGRESAMOS LA MATRICULA Y CHECAMOS QUE EXISTA,
		SINO EXISTE SALIMOS.
	*/
	char busqueda[' '];
	int boton=0,nuevo;
	int i,op;
	char nuevonom[50];
	char nuevadir[100];
	
	system("cls");
	printf("\n\n\n\t MODIFICAR USUARIO.");
	printf("\n\n\t\t Introduzca el identificador del usuario que desea modificar: ");
	fflush(stdin);
	gets(busqueda);
		
	for(i=0;i<cantusuarios;i++) // CHECAMOS QUE ESTE LA MATRICULA EN LOS USUARIOS QUE EXISTEN EN EL MOMENTO.
	{
		if(strcmp(usuarios[i].mat,busqueda)==0)
		{
			boton=1;
			break;	
		}		
	}
		
	if(boton==0)
	{
		printf("\n\n\t\t No se encontro el usuario.\n\n");
		system("pause");
		return;
	}
			
	// si llego a este punto, si existe el usuario
	
	do
	{
		printf("\n\n\n\t\t Matricula: %s",usuarios[i].mat);
		printf("\n\n\t\t Nombre: %s",usuarios[i].nombre);
		printf("\n\n\t\t Direccion: %s",usuarios[i].direc);
		printf("\n\n\t\t Cantidad de libros prestados: %d",usuarios[i].cantlibros);
			
		printf("\n\n\t\t Introduzca el nuevo nombre: "); 
		fflush(stdin);
		gets(nuevonom);
		
		printf("\n\n\t\t Introduzca la nueva direccion: "); 
		fflush(stdin);
		gets(nuevadir);
		do
		{
			printf("\n\n\t Son correctos los datos introducidos? [1.-Si 2.-No]:");
			op=validar();
			if(op!=1 && op!=2)
					printf("\n Entrada incorrecta. ");
		}	while(op!=1 && op!=2);
	}	while(op==2);
	
	strcpy(usuarios[i].nombre,nuevonom);
	strcpy(usuarios[i].direc,nuevadir);
	return;
}
//-------------------------------------------------------------------------------------------------------------
void conusumatricula(struct usuarios usuarios[100],int cantusuarios)
{
	/*
		PRIMERO SE INGRESA UN NOMBRE, SI EXISTE SE IMPRIMEN LOS DATOS, SINO NO IMPRIME NADA.
	*/
	int i,boton=0;
	char busqueda[50];
	printf("\n\n\n\t CONSULTA POR NOMBRE"); // SE BUSCAN LOS USUARIOS CON UN NOMBRE
	
	printf("\n\n\t\t Introduzca el nombre del usuario: ");
	fflush(stdin);
	gets(busqueda);
	for(i=0;busqueda[i]!='\0';i++)
		busqueda[i]=toupper(busqueda[i]);
	
	printf("\n\n\nNombre                                  Direccion                                                                     Identificador  Debe libros?   Cantidad de libros prestados");
	
	for(i=0;i<cantusuarios;i++)
		if(strstr(usuarios[i].nombre,busqueda)!=NULL)
		{
			printf("\n%-40s%-78s%-15s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
			if(usuarios[i].estado==0)
				printf("No             ");
			else
				printf("Si             ");
			printf("%d",usuarios[i].cantlibros);
			boton=1;	
		}
	if(boton==0)
		printf("\n\n\n\t\t No se encontraron coincidencias.");
	printf("\n\n\n\n\t\t");
	system("pause");
	return;
}
//-------------------------------------------------------------------------------------------------------------
void conusugen(struct usuarios usuarios[100],int cantusuarios)
{
	/*
		REPORTE GENERAL DE LOS USUARIOS.
	*/
	int i;
	printf("\n\n\n\t CONSULTA GENERAL DE USUARIOS");
	printf("\n\n\nNombre                                  Direccion                                                                     Identificador  Debe libros?   Cantidad de libros prestados");
	
	for(i=0;i<cantusuarios;i++)
	{
		printf("\n%-40s%-78s%-15s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
		if(usuarios[i].estado==0)
			printf("No             ");
		else
			printf("Si             ");
		printf("%d",usuarios[i].cantlibros);	
	}
	printf("\n\n\n\n\t\t");
	system("pause");
	return;
}
//--------------------------------------------------------------------------------------------
void conusu(struct usuarios usuarios[100],int cantusuarios)
{
	/*
		ESTE ES UN SUBMENU DE LOS REPORTES DE USUARIOS.
		REPORTE  GENERAL DE USUARIOS.- SE GENERA UN REPORTE DE TODOS LOS USUARIOS.
		REPORTE POR CANTIDAD DE LIBROS PRESTADOS.- SE GENERA UN REPORTE DEPENDIENDO DE LO QUE QUIERA EL USUARIO CON RESPECTO A LA CANTIDAD DE LIBROS PRESTADOS.
		REPORTE DE LOS USUARIOS CON MULTAS.- SE GENERA UN REPORTE DE LOS USUARIOS CON ESTADO==1	
	*/
	int op;
	do
	{
		system("cls");
		printf("\n\n\n\t\t REPORTES DE USUARIOS:");
		printf("\n\n\t\t 1) Reporte de usuarios ordenados por identificador");
		printf("\n\t\t 2) Reporte por cantidad de libros prestados");
		printf("\n\t\t 3) Reporte de usuarios con multa");
		printf("\n\t\t 4) Volver al menu de usuarios");
		printf("\n\t\t Escriba el numero de su eleccion: ");
		do
		{
			op=validar();
			if(op!=1 && op!=2 && op!=3 && op!=4)
				printf("\n Introduzca un numero del 1 al 4: ");
		}	while(op!=1 && op!=2 && op!=3 && op!=4);
		
		system("cls");
		
		switch(op)
		{
				
			case 1:	conusugenrep(usuarios,cantusuarios);
					break;	
			case 2: conusucantlibros(usuarios,cantusuarios);
					break;
			case 3:	conusuestado(usuarios,cantusuarios);
					break;
		}
			
	}	while (op!=4);
	return;
}
//-------------------------------------------------------------------------------------------
void conusugenrep(struct usuarios usuarios[100],int cantusuarios)
{
	/*
		SE IMPRIMEN TODOS LOS USUARIO ES LA PANTALLA Y EN UN ARCHIVO.
	
	*/
	FILE *reporteusugen;
	int i,j;
	struct usuarios aux;
	
	reporteusugen = fopen("reporteusugen.txt","w"); 
	if(reporteusugen == NULL)
	{
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tError! Fallo en el sistema.\n\n\n\n\n");  
		system("pause"); 
		exit(1);             
	}
	
	for(i=0;i<cantusuarios;i++) // Ordenamiento por matricula
		for(j=i+1;j<cantusuarios;j++)
			if(strcmp(usuarios[i].mat,usuarios[j].mat)>0);
			{
				aux=usuarios[i];
				usuarios[i]=usuarios[j];
				usuarios[j]=aux;
			}
	
	system("cls");
	printf("\n\n\n\t\t REPORTE GENERAL DE USUARIOS");
	printf("\n\n\nNombre                                  Direccion                                                                     Identificador  Debe libros?   Cantidad de libros prestados");
	
	fprintf(reporteusugen,"LISTA DE USUARIOS POR IDENTIRICADOR\nNombre\tDireccion\tIdentificador\tDebe libros\tCantidad libros prestados");
	
	for(i=0;i<cantusuarios;i++)
	{
		fprintf(reporteusugen,"\n%s\t%s\t%s\t%d\t%d",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat,usuarios[i].estado,usuarios[i].cantlibros);
		printf("\n%-40s%-78s%-15s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
		if(usuarios[i].estado==0)
			printf("No             ");
		else
			printf("Si             ");
		printf("%d",usuarios[i].cantlibros);
	}
	
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'reporteusugen.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	system("pause");
	fclose(reporteusugen);
	return;
	
}
//--------------------------------------------------------------------------------------------------
void conusucantlibros(struct usuarios usuarios[100],int cantusuarios)
{
	/*
	
	SE LE PREGUTNA AL USUARIO QUE DESEA HACER, BUSCAR TODOS LOS USUARIOS QUE TENGAN MENOS DE X LIBROS PRESTADOS,
	BUSCAR TODOS LOS USUARIOS QUE TENGAN MAS DE X LIBROS PRESTADO 
	O BUSCAR TODOS LOS USUARIOS QUE TENGAN X LIBROS PRESTADOS.
	*/
	int i,j,busqueda,op;
	struct usuarios aux;
	
	FILE *reporteusucant;

	reporteusucant = fopen("reporteusucant.txt","w"); 
	if(reporteusucant == NULL)
	{
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tError! Fallo en el sistema.\n\n\n\n\n");
		system("pause");   
		exit(1);             
	}
	
	for(i=0;i<cantusuarios;i++)
		for(j=i+1;j<cantusuarios;j++)
			if(usuarios[i].cantlibros<usuarios[j].cantlibros)
			{
				aux=usuarios[i];
				usuarios[i]=usuarios[j];
				usuarios[j]=aux;
			}
	
	system("cls");
	printf("\n\n\n\t\t REPORTE	POR CANTIDAD DE LIBROS PRESTADOS"); // SE BUSCA TODOS LOS USUARIOS QUE CUMPLEN CON LAS SIGUIENTES CONDICIONES
	do
	{
		printf("\n\n\t :Que desea realizar?");
		printf("\n\t 1) Buscar todos los usuarios con mas de X libros prestados");
		printf("\n\t 2) Buscar todos los usuarios con menos de X libros prestados");	
		printf("\n\t 3) Buscar todos los usuarios con X libros prestados");
		printf("\n\t\t Escriba el numero de su eleccion: ");
		op=validar();
	}	while(op!= 1 && op!=2 && op!=3);
	
	printf("\n\n\t Cantidad de libros: ");
	busqueda=validar();
	
	printf("\n\n\nNombre                                  Direccion                                                                     Identificador  Debe libros?   Cantidad de libros prestados");
	fprintf(reporteusucant,"LISTA DE USUARIOS POR CANTIDAD DE LIBROS PRESTADOS\nNombre\tDireccion\tIdentificador\tDebe libros\tCantidad libros prestados");
	
	for(i=0;i<cantusuarios;i++) // SE HACE EL SWITCH PARA SABER QUE PIDIO EL USUARIO.
	{	
		switch(op)
		{
			case 1:
					if(usuarios[i].cantlibros>busqueda)
					{
						printf("\n%-40s%-78s%-15s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
						if(usuarios[i].estado==0)
							printf("No             ");
						else
							printf("Si             ");
						printf("%d",usuarios[i].cantlibros);
						fprintf(reporteusucant,"\n%s\t%s\t%s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
						if(usuarios[i].estado==0)
							fprintf(reporteusucant,"\tNo");
						else
							fprintf(reporteusucant,"\tSi");
						fprintf(reporteusucant,"\t%d",usuarios[i].cantlibros);	
					}
					break;	
			case 2:
					if(usuarios[i].cantlibros<busqueda)
					{
						printf("\n%-40s%-78s%-15s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
						if(usuarios[i].estado==0)
							printf("No             ");
						else
							printf("Si             ");
						printf("%d",usuarios[i].cantlibros);
						fprintf(reporteusucant,"\n%s\t%s\t%s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
						if(usuarios[i].estado==0)
							fprintf(reporteusucant,"\tNo");
						else
							fprintf(reporteusucant,"\tSi");
						fprintf(reporteusucant,"\t%d",usuarios[i].cantlibros);		
					}		
					break;	
			case 3:
					if(usuarios[i].cantlibros==busqueda)
					{
						printf("\n%-40s%-78s%-15s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
						if(usuarios[i].estado==0)
							printf("No             ");
						else
							printf("Si             ");
						printf("%d",usuarios[i].cantlibros);
						fprintf(reporteusucant,"\n%s\t%s\t%s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
						if(usuarios[i].estado==0)
							fprintf(reporteusucant,"\tNo");
						else
							fprintf(reporteusucant,"\tSi");
						fprintf(reporteusucant,"\t%d",usuarios[i].cantlibros);	
					}
						
					break;		
		}		
	}
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'reporteusucant.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	system("pause");
	
	fclose(reporteusucant);
	return;
}
//-------------------------------------------------------------------------------------------------------------
void conusuestado(struct usuarios usuarios[100],int cantusuarios)
{
	/*
		SE IMPRIMEN EN UN ARCHIVO TODOS LOS USUARIOS CON  ESTADO==1 OSEA TIENEN MULTA.
	*/
	int i,busqueda;
	
	FILE *reporteusuestado;

	reporteusuestado = fopen("reporteusuestado.txt","w"); 
	if(reporteusuestado == NULL)
	{
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tError! Fallo en el sistema.\n\n\n\n\n");
		system("pause");   
		exit(1);             
	}
	
	printf("\n\n\n\t\t CONSULTA	DE USUARIOS CON MULTAS"); // SE BUSCAN LOS USUARIOS EN LOS CUALES USUARIOS[I].ESTADO TENGAN UN '1' , OSEA, TENGAN ALGUNA MULTA
	 
	printf("\n\n\nNombre                                  Direccion                                                                     Identificador  Debe libros?   Cantidad de libros prestados");
	fprintf(reporteusuestado,"LISTA DE USUARIOS CON MULTAS\nNombre\tDireccion\tIdentificador\tDebe libros\tCantidad libros prestados");
	
	for(i=0;i<cantusuarios;i++)
		if(usuarios[i].estado!=0)
		{
			printf("\n%-40s%-78s%-15s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
			if(usuarios[i].estado==0)
				printf("No             ");
			else
				printf("Si             ");
			printf("%d",usuarios[i].cantlibros);
			fprintf(reporteusuestado,"\n%s\t%s\t%s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
			if(usuarios[i].estado==0)
				fprintf(reporteusuestado,"\tNo");
			else
				fprintf(reporteusuestado,"\tSi");
			fprintf(reporteusuestado,"\t%d",usuarios[i].cantlibros);	
		}
				
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'reporteusuestado.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	system("pause");
	
	fclose(reporteusuestado);
	return;
}
//-------------------------------------------------------------------------------------------------------------
void impresionusuarios(struct usuarios usuarios[100],int cantusuarios)
{
	/*
		SE GUARDAN TODOS LOS DATOS DEL STRUCT USUARIOS EN EL ARCHIVO USUARIOS
	*/
	FILE *usuariofile;
	int i;

	usuariofile = fopen("usuarios.txt","w"); // Se checa que funcione correctamente.
	if(usuariofile == NULL)
	{
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tError! Fallo en el sistema.\n\n\n\n\n");  
		system("pause"); 
		exit(1);             
	}
   	
   	for(i=0;i<cantusuarios;i++)
	{
		if(i!=0)
			fprintf(usuariofile,"\n");
		fprintf(usuariofile,"%s\n%s\n%s\n%d\n%d",usuarios[i].mat,usuarios[i].nombre,usuarios[i].direc,usuarios[i].estado,usuarios[i].cantlibros);   	
	}	
	fclose(usuariofile);
	return;
}
