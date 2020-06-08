int prests(struct biblio libros[100],struct usuarios usuarios[100],struct prestamo prestamos[200],int cantlibros,int cantusuarios,int cantprestamos,struct multa multas[200],int cantmultas,float valormulta)
{
	int i;
	//MENU
	cantprestamos=menuprestamos(prestamos,cantprestamos,cantlibros,cantusuarios,usuarios,libros,multas,cantmultas);	
	
//SE GUARDAN LOS DATOS
	impresionprestamos(prestamos,cantprestamos);
	impresionusuarios(usuarios,cantusuarios);
	impresionlibros(libros,cantlibros);
	impresionmultas(multas,cantmultas,valormulta);
	return cantprestamos;
}



// esta funcion leera todos los prestamos del archivo y los pasara al struct prestamos, aparte de regresar la cantidad de prestamos.
int lecturaprestamos(struct prestamo prestamos[' '],int cantprestamos) 
{
	FILE *prestamosfile;
	prestamosfile = fopen("prestamos.txt","r"); // Se checa que funcione correctamente.

	if(prestamosfile == NULL)
	{
		prestamosfile=fopen("prestamos.txt","w+");
		if(prestamosfile==NULL)
		{
			printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tError! Fallo en el sistema.\n\n\n\n\n");   
			system("pause");
			exit(1);             
		}
	}

	fscanf(prestamosfile,"%d\t",&prestamos[cantprestamos].num);

   	while(feof(prestamosfile)==0)
   	{	
   		fscanf(prestamosfile,"%s\t%s\t%s\t%s\t%d\n",&prestamos[cantprestamos].fechap,&prestamos[cantprestamos].fechae,&prestamos[cantprestamos].mat,&prestamos[cantprestamos].clave,&prestamos[cantprestamos].estado);
   		cantprestamos++;   
		fscanf(prestamosfile,"%d\t",&prestamos[cantprestamos].num);
		
	}
	fclose(prestamosfile);
	return cantprestamos;
}

//MENU DE OPCIONES DE PRESTAMOS
int menuprestamos(struct prestamo prestamos[' '],int cantprestamos,int cantlib,int cantusuarios,struct usuarios usuarios[' '],struct biblio libros[' '],struct multa multas[200],int cantmultas) // ESTE MENU SERA UN SUBMENU DEL MENU PRINCIPAL.
{
	int op,i;
	do
	{
		system("cls");
		//OPCIONES
			printf("\n\n\n\t\t MENU PRESTAMOS:");
			printf("\n\n\t\t 1) Prestamo de un libro ");
			printf("\n\t\t 2) Devolucion de un libro");
			printf("\n\t\t 3) Reportes de prestamos");
			printf("\n\t\t 4) Volver al menu principal");
			printf("\n\t\t Escriba el numero de su eleccion: ");
		do
		{
			op=validar();
			if(op!=1 && op!=2 && op!=3 && op!=4)
				printf("\n\n\t Introduzca un numero entre 1 y 4: ");
		}	while(op!=1 && op!=2 && op!=3 && op!=4);
		system("cls");
		//OPCIONES DEL MENU
		switch(op)
		{
			case 1: cantprestamos=represtamos(prestamos,cantprestamos,cantlib,cantusuarios,usuarios,libros);	 // FUNCION REALIZAR PRESTAMO
					break;
			case 2:	entprestamos(prestamos,cantprestamos,multas,cantmultas,usuarios,cantusuarios);	 // FUNCION HACER LA ENTREGA DE UN LIBRO
					break;
			case 3:conprestamos(prestamos,cantprestamos);		// SUBMENU CONSULTA
					break;		
		}
			
	}	while (op!=4);
	return cantprestamos;
}
//ESTA FUNCION SE USA PARA REALIZAR PRESTAMOS
//_--------------------------------------------------------------------------------------------------
int represtamos(struct prestamo prestamos[' '],int cantprestamos,int cantlib,int cantusuarios,struct usuarios usuarios[' '],struct biblio libros[' '])
{
	int sn,l,op,op2,i,boton2=0,boton3=0,boton4=0;
	char aux[10],numero[' '];
	printf("\n\n\n\t REALIZAR UN PRESTAMO:");
	do
	{	
		printf("\n\n\nNombre                                  Direccion                                                                     Identificador  Debe algo?   Cantidad de libros prestados");
		for(i=0;i<cantusuarios;i++)
		{
			printf("\n%-40s%-78s%-15s",usuarios[i].nombre,usuarios[i].direc,usuarios[i].mat);
			if(usuarios[i].estado==0)
				printf("No             ");
			else
				printf("Si             ");
			printf("%d",usuarios[i].cantlibros);	
		}
		do
		{
			//Se ingresan los datos
			printf("\n\n\n\t Introduzca el identificador del usuario (Esc+Enter para cancelar): ");
			fflush(stdin);
			gets(prestamos[cantprestamos].mat);
			if(prestamos[cantprestamos].mat[0]==27)
				return cantprestamos;
			boton2=0;
			boton3=0;
			boton4=0;			
			for(i=0;i<strlen(prestamos[cantprestamos].mat);i++)  // MAYUSCULAS
				prestamos[cantprestamos].mat[i]=toupper(prestamos[cantprestamos].mat[i]);
					
			for(i=0;i<cantusuarios;i++)
				if(strcmp(usuarios[i].mat,prestamos[cantprestamos].mat)==0) // CHECAMOS SI LA MATRICULA ESTA EN LOS ARCHIVOS
				{
					boton2=1;
					printf("\n\n\t Identificador encontrado!");
					if(usuarios[i].estado==1)
					{
						boton4=1;
						printf("\n\n\t ESTE USUARIO TIENE UNA MULTA");
					}
					break;
				}
			for(i=0;i<cantprestamos;i++)
				if(strcmp(prestamos[i].mat,prestamos[cantprestamos].mat)==0 && prestamos[i].estado==1) // CHECAMOS SI LA MATRICULA TIENE UN PRESTAMO ACTIVO
				{
					boton3=1;
					printf("\n\n\t ESTE USUARIO TIENE UN PRESTAMO ACTIVO");
					break;
				}
			if(boton2==0)
				printf("\n\n\t Identificador no encontrado");
			if(boton3==1||boton4==1)
			{
				do
				{
					printf("\n\n\t Desea proceder? [1) Si - 2) No]\n");
					sn=validar();
				}while(sn<1||sn>2);
				if(sn==2)
					return cantprestamos;
			}
		} while(boton2==0);
		
		system("cls");
		encabezado();
	    l = 8;
	
	    //-------------Escritura de la tabla--------------------
	    for (i = 0; i < cantlib; i++) {
	
	      tabla(libros, l, i);
	      l++;
	    }
		//SE PREGUNTA LA CLAVE DEL LIBRO
		printf("\n\n\n\t Introduzca la clave del libro (Esc+Enter para cancelar): ");
		char busca[' '];
		fflush(stdin);
		gets(busca);
		if(busca[0]==27)
			return cantprestamos;
		boton2=0;
		boton3=0;
		for(i=0;i<strlen(busca);i++)  // MAYUSCULAS
			busca[i]=toupper(busca[i]);
		strcpy(prestamos[cantprestamos].clave,busca);
		for(i=0;i<cantlib;i++)
		{
			if(strcmpi(busca,libros[i].clave)==0) // CHECAMOS SI LA CLAVE ESTA EN LOS ARCHIVOS
			{
				boton2=1;
				printf("\n\n\t Clave encontrada");
				break;
			}	
		}
		
		for(i=0;i<cantprestamos;i++)
			if(strcmp(prestamos[i].clave,prestamos[cantprestamos].clave)==0 && prestamos[i].estado==1) // CHECAMOS SI EL LIBRO ESTA PRESTADO
			{
				boton3=1;
				printf("\n\n\t ESTE LIBRO ESTA PRESTADO\n\n");
				system("pause");
				return cantprestamos;
			}
		do  //Nos aseguramos de que este correcta la informacion
		{
			printf("\n Desea proceder con el prestamo? [1) Si - 2) No]\n\t");
			sn=validar();
			if(sn<1||sn>2)
				printf("\n\n Introduzca 1 o 2\n");
		}while(sn<1||sn>2);
		if(sn==2)
			return cantprestamos;
		if(boton2==0)
		{
			printf("\n\n\t Libro no encontrado.\n\n");
			system("pause");
			return cantprestamos;
		}
		prestamos[cantprestamos].num=cantprestamos+1;//NUMERO DEL PRESTAMO
		time_t t = time(NULL);
		struct tm *tm = localtime(&t);
		//Aqui obtenemos la fecha de hoy y llenamos los demas datos
		strftime(prestamos[cantprestamos].fechap, 100, "%d/%m/%y", tm);
	
		strcpy(prestamos[cantprestamos].fechae,"00/00/00");
		prestamos[cantprestamos].estado=1;	
		
		for(i=0;i<cantusuarios;i++)
				if(strcmp(usuarios[i].mat,prestamos[cantprestamos].mat)==0) // EDITAMOS INFO. DE LA MATRICULA
				{
					usuarios[i].cantlibros++;	
					break;
				}	
		for(i=0;i<cantlib;i++)
				if(strcmp(libros[i].clave,prestamos[cantprestamos].clave)==0)
				{
					libros[i].vecesprestado++;
					break;
				}
		cantprestamos=cantprestamos+1;
		 // AUMENTAMOS LA CANTIDAD TOTAL DE PRESTAMOS
		//SE PREGUNTA SI SE DESEA REALIZAR OTRO PRESTAMO
		
		do
		{
			printf("\n\n\t Desea realizar otro prestamo? [1.- Si,2.- No]:");
			op=validar();	
		}	while(op!=1 && op!=2);
	}	while(op==1);
	
	
	
	printf("\n\n\t Prestamo realizado con exito! Recuerde que el libro se devuelve en 3 dias.\n\n\n\t");
	return cantprestamos;
}




//Esta funcion se usa para regresar los libros
void entprestamos(struct prestamo prestamos[' '],int cantprestamos,struct multa multas[200],int cantmultas,struct usuarios usuarios[100],int cantusuarios)
{
	char busqueda[' '],numero[' '];
	int boton=0,nuevo;
	int sn,i,j,k;
	printf("\n\n\n\t DEVOLUCION DE UN LIBRO:");
	//SE INGRESA LA CLAVE
	printf("\n\n\t\t Introduzca la clave del libro que desea devolver:");
	fflush(stdin);
	gets(busqueda);
	
	for(i=0;busqueda[i]!='\0';i++)
		busqueda[i]=toupper(busqueda[i]);
	
	for(i=0;i<cantprestamos;i++) // CHECAMOS SI HAY UN PRESTAMO CON ESA CLAVE
	{
		if(strcmp(prestamos[i].clave,busqueda)==0 && prestamos[i].estado==1)
		{
			boton=1;
			k=i;
			break;	
		}		
	}
		
	if(boton==0)
	{
		printf("\n\n\t\t No se encontro un registro de este prestamo.\n\n");
	}
	else
	{
		for(i=0;i<cantmultas;i++)
			if(multas[i].num==prestamos[k].num)
				{
					printf("\n\n\t El usuario cuenta con una multa por el monto de %.2f.",multas[i].monto);
					printf("\n\t Se pago la multa? [1) Si - 2) No]");
					do
					{
						sn=validar();
						if(sn!=1&&sn!=2)
							printf("Introduzca 1 o 2: ");
					}while(sn!=1&&sn!=2);
					if(sn==2)
						return;
					multas[i].estado=0;
					for(j=0;j<cantusuarios;j++)
						if(strcmp(prestamos[i].mat,usuarios[j].mat)==0)
						{
							usuarios[j].estado--;
							break;
						}
					break;
				}
		strcpy(prestamos[k].fechae,"");
		time_t t = time(NULL);
  		struct tm *tm = localtime(&t);
  		//Aqui obtenemos la fecha de hoy para cambiar los datos de esta
  		strftime(prestamos[k].fechae, 100, "%d/%m/%y", tm);
			
		prestamos[k].estado=0;//0 Significa que ya se pago todo
			
		printf("\n\tSe devolvio con exito\n\t");
		// si llego a este punto, si existe el usuario	
	}		
	
	system("pause");		
	return;
}


//--------------------------------------------------------------------------------------------
//REPORTE DE PRESTAMOS
void conprestamos(struct prestamo prestamos[' '],int cantprestamos)
{
	int op;
	do
	{
		//OPCIONES
		system("cls");
		printf("\n\n\n\t\t REPORTES DE PRESTAMOS:");
		printf("\n\t\t 1.- Reporte general de prestamos");
		printf("\n\t\t 2.- Reporte de prestamos por dia");
		printf("\n\t\t 3.- Reporte de prestamos por mes");
		printf("\n\t\t 4.- Reporte de prestamos anual");
		printf("\n\t\t 5.- Reporte por identificador de usuario");
		printf("\n\t\t 6.- Reporte por clave del libro");
		printf("\n\t\t 7.- Reporte por estado");
		printf("\n\t\t 8.- Volver al menu prestamos");
		printf("\n\t\t Escriba el numero de su eleccion: ");
		do
		{
			
			op=validar();
			if(op!=1 && op!=2 && op!=3 && op!=4 && op!=5 && op!=6 && op!=7 && op!=8)
				printf("\n Introduzca un numero del 1 al 8: ");
		}	while(op!=1 && op!=2 && op!=3 && op!=4 && op!=5 && op!=6 && op!=7 && op!=8);
		
		system("cls");
		
		switch(op)
		{
				
			case 1:	conpresgen(prestamos,cantprestamos);//GENERAL
					break;	
			case 2: conpresdia(prestamos,cantprestamos);//POR DIA
					break;
			case 3:	conpresmes(prestamos,cantprestamos);//POR MES
					break;	
			case 4:	conpresano(prestamos,cantprestamos);//POR AÑO
					break;	
			case 5: conpresmat(prestamos,cantprestamos);//POR MATRICULA
					break;
			case 6:	conpresclav(prestamos,cantprestamos);//POR CLAVE
					break;	
			case 7:	conpresest(prestamos,cantprestamos);//POR ESTADO
					break;
		}
			
	}	while (op!=8);
	return;
}

void conpresgen(struct prestamo prestamos[' '],int cantprestamos)
{
	int i,l=8;
	FILE *ap;
	ap=fopen("rep_prestamos_general.txt","w");
	if(ap==NULL)
	{
		printf("\n\n\n\t\t\t Error! Fallo en el sistema\n\n\n\n");
		system("pause");
		exit(1);
	}
	printf("\n\t\t REPORTE GENERAL DE PRESTAMOS");	
	fprintf(ap,"REPORTE GENERAL DE PRESTAMOS\nN_Prestamo\tFecha_Prestamo\tFecha_Entrega\tIdentificador_usuario\tClave_libro\tEstado");
	encabezadopres(l);//IMPRIME EL ESCABEZADO
	for(i=0;i<cantprestamos;i++)
	{
		
		tablapres(l,i,prestamos,cantprestamos,ap);//IMPRIME LOS DATOS EN FORMA DE TABLA
		l++;		
	}
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'rep_prestamos_general.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	fclose(ap);
	system("pause");
	return;
}
//ESTA FUNCION HACE REPORTES POR DIA
void conpresdia(struct prestamo prestamos[' '],int cantprestamos)
{
	int i,l=5,diabus,mesbus,anobus,boton=0;
	char dia[' '],mes[' '],ano[' '],dia2[' '],mes2[' '],ano2[' '];
	FILE *ap;
	ap=fopen("rep_prestamos_dia.txt","w");
	if(ap==NULL)
	{
		printf("\n\n\n\t\t\t Error! Fallo en el sistema\n\n\n\n");
		system("pause");
		exit(1);
	}
	do
	{
		printf("\n\tIngrese el dia (1 a 31):");
		diabus=validar();
		if(diabus<0 || diabus>31)
			printf("Dato incorrecto.");
	}while(diabus<0 || diabus>31);
	
	do
	{
		printf("\n\tIngrese el mes (1 a 12): ");
		mesbus=validar();
		if(mesbus<0 || mesbus>12)
			printf("Dato incorrecto.");
	}while(mesbus<0 || mesbus>12);
	
	do
	{
		printf("\n\tIngrese el ano: ");
		anobus=validar();
		if(anobus<2000||anobus>2100)
			printf("Dato incorrecto. Introduzca un ano entre 2000 y 2100. ");
	}while(anobus<2000||anobus>2100);
	
	system("cls");
	printf("\n\t\t REPORTE DE PRESTAMOS POR DIA");	
	fprintf(ap,"REPORTE DE PRESTAMOS POR DIA\nN_Prestamo\tFecha_Prestamo\tFecha_Entrega\tIdentificador_usuario\tClave_libro\tEstado");
	encabezadopres(l);//IMPRIME EL ESCABEZADO
	for(i=0;i<cantprestamos;i++)
	{
		
		convertirfechae(i,dia,mes,ano,prestamos,cantprestamos);
		convertirfechap(i,dia2,mes2,ano2,prestamos,cantprestamos);
		if(atoi(dia)==diabus&&atoi(mes)==mesbus&&atoi(ano)==anobus%100 || atoi(dia2)==diabus&&atoi(mes2)==mesbus&&atoi(ano2)==anobus%100 )
		{
			boton=1;
			l++;
			tablapres(l,i,prestamos,cantprestamos,ap);//IMPRIME LA TABLA
		}
				
	}
	if(boton==0)
		printf("\n No se encontraron prestamos en la fecha indicada");
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'rep_prestamos_dia.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	fclose(ap);
	system("pause");
	return;
}
//ESTA FUNCION HACE REPORTES POR MES
void conpresmes(struct prestamo prestamos[' '],int cantprestamos)
{
	int i,l=5,mesbus,anobus,boton=0;
	char dia[' '],mes[' '],ano[' '],dia2[' '],mes2[' '],ano2[' '];
	FILE *ap;
	ap=fopen("rep_prestamos_mes.txt","w");
	if(ap==NULL)
	{
		printf("\n\n\n\t\t\t Error! Fallo en el sistema\n\n\n\n");
		system("pause");
		exit(1);
	}
	
	do
	{
		printf("\n\tIngrese el mes (1 a 12): ");
		mesbus=validar();
		if(mesbus<0 || mesbus>12)
			printf("Dato incorrecto.");
	}while(mesbus<0 || mesbus>12);
	
	do
	{
		printf("\n\tIngrese el ano: ");
		anobus=validar();
		if(anobus<2000||anobus>2100)
			printf("Dato incorrecto. Introduzca un ano entre 2000 y 2100. ");
	}while(anobus<2000||anobus>2100);
	
	system("cls");
	printf("\n\t\t REPORTE DE PRESTAMOS POR MES");	
	fprintf(ap,"REPORTE DE PRESTAMOS POR MES\nN_Prestamo\tFecha_Prestamo\tFecha_Entrega\tIdentificador_usuario\tClave_libro\tEstado");
	encabezadopres(l);//IMPRIME EL ESCABEZADO
	for(i=0;i<cantprestamos;i++)
	{
		
		convertirfechae(i,dia,mes,ano,prestamos,cantprestamos);
		convertirfechap(i,dia2,mes2,ano2,prestamos,cantprestamos);
		if(atoi(mes)==mesbus&&atoi(ano)==anobus%100 || atoi(mes2)==mesbus&&atoi(ano2)==anobus%100)
		{	
			boton=1;
			l++;
			tablapres(l,i,prestamos,cantprestamos,ap);//IMPRIME EN FORMA DE TABLA
		}
				
	}
	if(boton==0)
		printf("\n No se encontraron prestamos en la fecha indicada");
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'rep_prestamos_mes.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	fclose(ap);
	system("pause");
	return;
}

//ESTA FUNCION HACE REPORTES POR AÑO
void conpresano(struct prestamo prestamos[' '],int cantprestamos)
{
	int i,l=8,anobus,boton=0;
	char dia[' '],mes[' '],ano[' '],dia2[' '],mes2[' '],ano2[' '];
	FILE *ap;
	ap=fopen("rep_prestamos_ano.txt","w");
	if(ap==NULL)
	{
		printf("\n\n\n\t\t\t Error! Fallo en el sistema\n\n\n\n");
		system("pause");
		exit(1);
	}
	
	do
	{
		printf("\n\tIngrese el ano: ");
		anobus=validar();
		if(anobus<2000||anobus>2100)
			printf("Dato incorrecto. Introduzca un ano entre 2000 y 2100. ");
	}while(anobus<2000||anobus>2100);
	
	printf("\n\t\t REPORTE DE PRESTAMOS POR ANO");	
	fprintf(ap,"REPORTE DE PRESTAMOS POR ANO\nN_Prestamo\tFecha_Prestamo\tFecha_Entrega\tIdentificador_usuario\tClave_libro\tEstado");
	encabezadopres(l);//IMPRIME EL ESCABEZADO
	for(i=0;i<cantprestamos;i++)
	{
		
		convertirfechae(i,dia,mes,ano,prestamos,cantprestamos);
		convertirfechap(i,dia2,mes2,ano2,prestamos,cantprestamos);
		if(atoi(ano)==anobus%100 || atoi(ano2)==anobus%100)
		{	
			boton=1;
			l++;
			tablapres(l,i,prestamos,cantprestamos,ap);//IMPRIME EN FORMA DE TABLA
		}
				
	}
	if(boton==0)
		printf("\n No se encontraron prestamos en la fecha indicada");
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'rep_prestamos_ano.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	fclose(ap);
	system("pause");
	return;
}


//ESTA FUNCION HACE REPORTES POR MATRICULA
void conpresmat(struct prestamo prestamos[' '],int cantprestamos)
{
	int i,l=5,boton=0;
	char clavebus[' '];
	FILE *ap;
	ap=fopen("rep_prestamos_mat.txt","w");
	if(ap==NULL)
	{
		printf("\n\n\n\t\t\t Error! Fallo en el sistema\n\n\n\n");
		system("pause");
		exit(1);
	}
	printf("\n\t\t CONSULTA DE PRESTAMOS POR IDENTIFICADOR DE USUARIO");	
	printf("\n\n\t Introduzca el identificador del usuario: ");
	fflush(stdin);
	gets(clavebus);
	for(i=0;clavebus[i]!='\0';i++)
			clavebus[i]= toupper(clavebus[i]);
	
	system("cls");
	printf("\n\t\t REPORTE DE PRESTAMOS A UN USUARIO");	
	fprintf(ap,"REPORTE DE PRESTAMOS A UN USUARIO\nN_Prestamo\tFecha_Prestamo\tFecha_Entrega\tIdentificador_usuario\tClave_libro\tEstado");
	encabezadopres(l);//IMPRIME EL ENCABEZADO
	for(i=0;i<cantprestamos;i++)
	{
		
		if(strstr(prestamos[i].mat,clavebus)!=NULL)
		{
			boton=1;
			l++;
			tablapres(l,i,prestamos,cantprestamos,ap);//IMPRIME EN FORMA DE TABLA
		}
				
	}
	if(boton==0)
		printf("\n No se encontraron prestamos del usuario indicado");
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'rep_prestamos_mat.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	fclose(ap);
	system("pause");
	return;
}
//ESTA FUNCION HACE REPORTES POR CLAVE
void conpresclav(struct prestamo prestamos[' '],int cantprestamos)
{
	int i,l=5,boton=0;
	char clavebus[' '];
	FILE *ap;
	ap=fopen("rep_prestamos_clave.txt","w");
	if(ap==NULL)
	{
		printf("\n\n\n\t\t\t Error! Fallo en el sistema\n\n\n\n");
		system("pause");
		exit(1);
	}
	printf("\n\t\t CONSULTA DE PRESTAMOS POR CLAVE DE LIBRO");	
		
	printf("\n\n\t Introduzca la clave del libro que desea buscar: ");
	fflush(stdin);
	gets(clavebus);
	for(i=0;clavebus[i]!='\0';i++)
			clavebus[i]= toupper(clavebus[i]);
	
	system("cls");
	printf("\n\t\t REPORTE DE PRESTAMOS DE UN LIBRO");	
	fprintf(ap,"REPORTE DE PRESTAMOS DE UN LIBRO\nN_Prestamo\tFecha_Prestamo\tFecha_Entrega\tIdentificador_usuario\tClave_libro\tEstado");
	encabezadopres(l);//IMPRIME EL ESCABEZADO
	for(i=0;i<cantprestamos;i++)
	{
		
		if(strstr(prestamos[i].clave,clavebus)!=NULL)
		{
			boton=1;
			l++;
			tablapres(l,i,prestamos,cantprestamos,ap);//IMPRIME EN FORMA DE TABLA
		}
				
	}
	if(boton==0)
		printf("\n No se encontraron prestamos del libro indicado");
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'rep_prestamos_clave.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	fclose(ap);
	system("pause");
	return;
}

//ESTA FUNCION HACE REPORTES POR ESTADO
void conpresest(struct prestamo prestamos[' '],int cantprestamos)
{
	int i,l=5,estadobus,boton=0;
	char est[20];
	FILE *ap;
	ap=fopen("rep_prestamos_estado.txt","w");
	if(ap==NULL)
	{
		printf("\n\n\n\t\t\t Error! Fallo en el sistema\n\n\n\n");
		system("pause");
		exit(1);
	}
	printf("\n\t\t CONSULTA DE PRESTAMOS POR ESTADO");	
		
	do
	{
		printf("\n\t Introduzca el estado que desea reportar [ 0) Devuelto - 1) En curso]:");
		estadobus=validar();
		if(estadobus!=0 && estadobus!=1)
			printf("\n Opcion incorrecta.");
	}while(estadobus!=0 && estadobus!=1);
	if(estadobus==0)
		strcpy(est,"DEVUELTOS");
	else
		strcpy(est,"EN CURSO");
	system("cls");
	printf("\n\t\t REPORTE DE PRESTAMOS POR ESTADO");	
	fprintf(ap,"REPORTE DE PRESTAMOS %s\nN_Prestamo\tFecha_Prestamo\tFecha_Entrega\tIdentificador_usuario\tClave_libro\tEstado",est);
	encabezadopres(l);//IMPRIME EL ESCABEZADO
	for(i=0;i<cantprestamos;i++)
	{
		if(prestamos[i].estado==estadobus)
		{	
			boton=1;
			l++;
			tablapres(l,i,prestamos,cantprestamos,ap);//IMPRIME EN FORMA DE TABLA
		}
				
	}
	if(boton==0)
		printf("\n No se encontraron prestamos %s",est);
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'rep_prestamos_estado.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	fclose(ap);
	system("pause");
	return;
}

//ESTA FUNCION SEPARA LA FECHA DE ENTREGA EN DIA MES Y AÑO
void convertirfechae(int i,char dia[' '],char mes[' '],char ano[' '],struct prestamo prestamos[' '],int cantprestamos)
{
	int ban,j;
	strcpy(dia,"");
	strcpy(mes,"");
	strcpy(ano,"");
	//COMO SABEMOS EL FORMATO DE LA FECHA PODEMOS ACOMODAR ASI LOS DATOS
	dia[0]=prestamos[i].fechae[0];
	dia[1]=prestamos[i].fechae[1];
	dia[2]='\0';
	mes[0]=prestamos[i].fechae[3];
	mes[1]=prestamos[i].fechae[4];
	mes[2]='\0';
	ano[0]=prestamos[i].fechae[6];
	ano[1]=prestamos[i].fechae[7];
	ano[2]='\0';
	
}
void convertirfechap(int i,char dia2[' '],char mes2[' '],char ano2[' '],struct prestamo prestamos[' '],int cantprestamos)
{
	char cosa[' '];
	int ban,j;
	strcpy(dia2,"");
	strcpy(mes2,"");
	strcpy(ano2,"");
	//COMO SABEMOS EL FORMATO DE LA FECHA PODEMOS ACOMODAR ASI LOS DATOS
	dia2[0]=prestamos[i].fechap[0];
	dia2[1]=prestamos[i].fechap[1];
	dia2[2]='\0';
	mes2[0]=prestamos[i].fechap[3];
	mes2[1]=prestamos[i].fechap[4];
	mes2[2]='\0';
	ano2[0]=prestamos[i].fechap[6];
	ano2[1]=prestamos[i].fechap[7];
	mes2[2]='\0';
	
}
void encabezadopres(int l){					//Formato de tabla de prestamos
	
		gotoxy(5,l);
		printf("N_Prestamo");
		gotoxy(20,l);
		printf("Fecha_Prestamo");
		gotoxy(50,l);
		printf("Fecha_Entrega");
		gotoxy(80,l);
		printf("Identificador_Usuario");
		gotoxy(110,l);
		printf("Clave_Libro");
		gotoxy(140,l);
		printf("Estado");
}


void tablapres(int l,int i,struct prestamo prestamos[' '],int cantprestamos,FILE *ap)
{		//Impresion de los datos de la tabla de prestamos

			gotoxy(5,l+3);
			printf("%d",prestamos[i].num);
			gotoxy(20,l+3);
			printf("%s",prestamos[i].fechap);
			gotoxy(50,l+3);
			if(strcmp(prestamos[i].fechae,"00/00/00")==0)
				printf("No entregado");
			else
				printf("%s",prestamos[i].fechae);
			gotoxy(80,l+3);
			printf("%s",prestamos[i].mat);
			gotoxy(110,l+3);
			printf("%s",prestamos[i].clave);
			gotoxy(140,l+3);
			if(prestamos[i].estado==0)
				printf("Entregado");
			else
				printf("No entregado");
			fprintf(ap,"\n%d\t%s\t",prestamos[i].num,prestamos[i].fechap);
			if(strcmp(prestamos[i].fechae,"00/00/00")==0)
				fprintf(ap,"No entregado");
			else
				fprintf(ap,"%s",prestamos[i].fechae);
			fprintf(ap,"\t%s\t%s\t",prestamos[i].mat,prestamos[i].clave);
			if(prestamos[i].estado==0)
				fprintf(ap,"Entregado");
			else
				fprintf(ap,"No entregado");
				
			return;
}
//PASA LOS DATOS DE PRESTAMOS AL ARCHIVO
void impresionprestamos(struct prestamo prestamos[' '],int cantprestamos)
{
	
	FILE *prestamofile;
	int i;
	prestamofile = fopen("prestamos.txt","w"); // Se checa que funcione correctamente.
	if(prestamofile == NULL)
	{
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tError! Fallo en el sistema.\n\n\n\n\n");   
		exit(1);             
	}
   	
   	for(i=0;i<cantprestamos;i++)
	{
		if(i!=0)
			fprintf(prestamofile,"\n");
			fprintf(prestamofile,"%d\t%s\t%s\t%s\t%s\t%d",prestamos[i].num,prestamos[i].fechap,prestamos[i].fechae,prestamos[i].mat,prestamos[i].clave,prestamos[i].estado);  
		
	}	
	fclose(prestamofile);
	return;
}

