float multax(struct multa multas[200],int cantmultas,float valormulta)
{
	int op;
	do
	{
		system("cls");
		// OPCIONES
		printf("\n\n\n\t\t MENU MULTAS:");
		printf("\n\n\t\t 1) Editar multa");
		printf("\n\t\t 2) Reportes de multas");
		printf("\n\t\t 3) Volver al menu principal");
		printf("\n\t\t Escriba el numero de su eleccion: ");
		do
		{
			op=validar();
			if(op<1||op>3)
				printf("\n\n Entrada invalida, introduzca un numero del 1 al 3");
		}while(op<1||op>3);
		system("cls");
		switch(op)
		{
			case 1:
				valormulta=editar_multa(valormulta);
				impresionmultas(multas,cantmultas,valormulta);
				break;
			case 2:
				reportes_multa(multas,cantmultas);
				break;
			case 3:
				break;
		}
	}while(op!=3);
	return valormulta;
}

int lecturamultas(struct multa multas[200],int cantmultas,struct prestamo prestamos[200],int cantprestamos,struct usuarios usuarios[100],int cantusuarios)
{
	int i,j,dia,mes,ano,diferencia;
	char aux[20];
	float valormulta;
	FILE *mult;
	time_t t=time(NULL);
	struct tm *tm = localtime(&t);
	mult = fopen("multas.txt","r"); // Se checa que funcione correctamente.

	if(mult == NULL)
	{
		mult=fopen("multas.txt","w+");
		if(mult==NULL)
		{
			printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tError! Fallo en el sistema.\n\n\n\n\n");   
			system("pause");
			exit(1);             
		}
	}
	fscanf(mult,"%f\n",&valormulta);
	fscanf(mult,"%d\t",&multas[cantmultas].num);
	while(feof(mult)==0)
	{
		fscanf(mult,"%f\t%s\t%d\n",&multas[cantmultas].monto,&multas[cantmultas].fecha,&multas[cantmultas].estado);
		if(multas[cantmultas].estado==1)
		{
			aux[0]=multas[cantmultas].fecha[0];
			aux[1]=multas[cantmultas].fecha[1];
			aux[2]='\0';
			dia=atoi(aux);
			aux[0]=multas[cantmultas].fecha[3];
			aux[1]=multas[cantmultas].fecha[4];
			mes=atoi(aux);
			aux[0]=multas[cantmultas].fecha[6];
			aux[1]=multas[cantmultas].fecha[7];
			ano=atoi(aux);
			diferencia=compara_fechas(dia,mes,ano,tm->tm_mday,(tm->tm_mon)+1,(tm->tm_year)%100);
			if(diferencia>3)
				multas[cantmultas].monto=valormulta*(diferencia-3);
		}
		cantmultas++;
		fscanf(mult,"%d\t",&multas[cantmultas].num);
	}
	for(i=0;i<cantprestamos;i++)
		if(prestamos[i].estado==1)
		{
			aux[0]=prestamos[i].fechap[0];
			aux[1]=prestamos[i].fechap[1];
			aux[2]='\0';
			dia=atoi(aux);
			aux[0]=prestamos[i].fechap[3];
			aux[1]=prestamos[i].fechap[4];
			mes=atoi(aux);
			aux[0]=prestamos[i].fechap[6];
			aux[1]=prestamos[i].fechap[7];
			ano=atoi(aux);
			diferencia=compara_fechas(dia,mes,ano,tm->tm_mday,(tm->tm_mon)+1,(tm->tm_year)%100);
			if(diferencia>3)
			{
				for(j=0;j<cantmultas;j++)
					if(prestamos[i].num==multas[j].num)
						break;
				if(j==cantmultas)
				{
					multas[cantmultas].num=prestamos[i].num;
					multas[cantmultas].monto=valormulta*(diferencia-3);
					strcpy(multas[cantmultas].fecha,prestamos[i].fechap);
					multas[cantmultas].estado=1;
					cantmultas++;
					for(j=0;j<cantusuarios;j++)
						if(strcmp(prestamos[i].mat,usuarios[j].mat)==0)
						{
							usuarios[j].estado++;
							break;
						}
				}
			}
		}
	fclose(mult);
	return cantmultas;
}

int compara_fechas(int dia1,int mes1,int ano1,int dia2,int mes2,int ano2)
{
	int i,j,mes_inicial,mes_final,dia_inicial,dia_final,dias_mes,total=0;
	
	for(i=ano1;i<=ano2;i++)
	{
		if(i==ano1)
			mes_inicial=mes1;
		else
			mes_inicial=1;
		if(i==ano2)
			mes_final=mes2;
		else
			mes_final=12;
		for(j=mes_inicial;j<=mes_final;j++)
		{
			switch(j)
			{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					dias_mes=31;
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					dias_mes=30;
					break;
				case 2:
					if(i%4==0&&i%100!=0||i%400==0)
						dias_mes=29;
					else
						dias_mes=28;
					break;
			}
			if(i==ano1&&j==mes1)
				dia_inicial=dia1;
			else
				dia_inicial=0;
			if(i==ano2&&j==mes2)
				dia_final=dia2;
			else
				dia_final=dias_mes;
			total+=dia_final-dia_inicial;
		}
	}
	return total;		
}

float lecturavalor(struct multa multas[200],int cantmultas)
{
	float valormulta;
	FILE *mult;
	mult = fopen("multas.txt","r"); // Se checa que funcione correctamente.
	if(mult == NULL)
	{
		mult=fopen("multas.txt","w+");
		if(mult==NULL)
		{
			printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tError! Fallo en el sistema.\n\n\n\n\n");   
			system("pause");
			exit(1);             
		}           
	}
	fscanf(mult,"%f\n",&valormulta);
	fclose(mult);
	if(valormulta==0)
		return 10;
	else
		return valormulta;
}

float editar_multa(float valormulta)
{
	char aux[20];
	printf("\n\n\t EDITAR MULTA:");
	printf("\n\n\t Introduzca el nuevo valor de la multa: ");
	do
	{
		gets(aux);
		if(validar_real(aux)==1)
			printf("\n\n\t Introduzca un valor valido: ");
	}while(validar_real(aux)==1);
	if(strlen(aux)>8)
	{
		printf("\n\n\t Valor fuera de rango\n\n\t");
		system("pause");
		return valormulta;
	}
	valormulta=atof(aux);
	return valormulta;
}

void reportes_multa(struct multa multas[200],int cantmultas)
{
	int op;
	do
	{
		system("cls");
		printf("\n\n\n\t\t REPORTES DE MULTAS: ");
		printf("\n\t\t 1) Por fecha");
		printf("\n\t\t 2) Por estado");
		printf("\n\t\t 3) Por monto a pagar");
		printf("\n\t\t 4) Volver al menu de multas");
		printf("\n\t\t Escriba el numero de su eleccion: ");
		do
		{
			op=validar();
			if(op<1||op>4)
				printf("\n\n\t Introduzca un numero del 1 al 4");
		}while(op<1||op>4);
		system("cls");
		switch(op)
		{
			case 1:
				multasporfecha(multas,cantmultas);
				break;
			case 2:
				multasporestado(multas,cantmultas);
				break;
			case 3:
				multaspormonto(multas,cantmultas);
				break;
			case 4:
				break;
		}
	}while(op!=4);
	return;
}

void multasporfecha(struct multa multas[200],int cantmultas)
{
	int i,j,boton=0;
	struct multa aux;
	FILE *ap;
	ap=fopen("rep_multas_fecha.txt","w");
	if(ap==NULL)
	{
		printf("\n\n\n\t\t\t Error! Fallo en el sistema\n\n\n\n");
		system("pause");
		exit(1);
	}
	for(i=0;i<cantmultas;i++)
		for(j=i+1;j<cantmultas;j++)
			if(fechamayor(multas[i].fecha,multas[j].fecha)>0)
			{
				aux=multas[i];
				multas[i]=multas[j];
				multas[j]=aux;
			}
	printf("\n\n\t\t REPORTE DE MULTAS POR FECHA:");
	fprintf(ap,"REPORTE DE MULTAS POR FECHA\nNumero de prestamo\tMonto de la multa\tFecha\tEstado");
	printf("\n\nNumero de prestamo            Monto de la multa             Fecha                         Estado\n");
	for(i=0;i<cantmultas;i++)
		if(multas[i].estado==1)
		{
			boton=1;
			printf("\n%-30d%-30.2f%-30s",multas[i].num,multas[i].monto,multas[i].fecha);
			printf("No pagado");
			fprintf(ap,"\n%-30d%-30.2f%-30s",multas[i].num,multas[i].monto,multas[i].fecha);
			fprintf(ap,"No pagado");
		}
	if(boton==0)
		printf("\n\n\t No hay multas activas");
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'rep_multas_fecha.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	fclose(ap);
	system("pause");
	return;
}

int fechamayor(char *fecha1,char *fecha2)
{
	if(fecha1[6]>fecha2[6])
		return 1;
	else if(fecha1[6]==fecha2[6])
		if(fecha1[7]>fecha2[7])
			return 1;
		else if(fecha1[7]==fecha2[7])
			if(fecha1[3]>fecha2[3])
				return 1;
			else if(fecha1[3]==fecha2[3])
				if(fecha1[4]>fecha2[4])
					return 1;
				else if(fecha1[4]==fecha2[4])
					if(fecha1[0]>fecha2[0])
						return 1;
					else if(fecha1[0]==fecha2[0])
						if(fecha1[1]>fecha2[1])
							return 1;
						else if(fecha1[1]==fecha1[1])
							return 0;
	return -1;
}

void multasporestado(struct multa multas[200],int cantmultas)
{
	int i,estadobus,boton=0;
	char est[20];
	FILE *ap;
	ap=fopen("rep_multas_estado.txt","w");
	if(ap==NULL)
	{
		printf("\n\n\n\t\t\t Error! Fallo en el sistema\n\n\n\n");
		system("pause");
		exit(1);
	}
	do
	{
		printf("\n\t Que estado desea reportar? [0) Multas pagadas - 1) Multas no pagadas]");
		estadobus=validar();
		if(estadobus!=0 && estadobus!=1)
			printf("\n Opcion incorrecta.");
	}while(estadobus!=0 && estadobus!=1);
	if(estadobus==0)
		strcpy(est,"PAGADAS");
	else
		strcpy(est,"NO PAGADAS");
	printf("\n\n\t\t REPORTE DE MULTAS %s:",est);
	fprintf(ap,"REPORTE DE MULTAS %s\nNumero de prestamo\tMonto de la multa\tFecha\tEstado",est);
	printf("\n\nNumero de prestamo            Monto de la multa             Fecha                         Estado\n");
	for(i=0;i<cantmultas;i++)
		if(multas[i].estado==estadobus)
		{
			boton=1;
			printf("\n%-30d%-30.2f%-30s",multas[i].num,multas[i].monto,multas[i].fecha);
			if(estadobus==0)
				printf("Pagado");
			else
				printf("No pagado");
			fprintf(ap,"\n%-30d%-30.2f%-30s",multas[i].num,multas[i].monto,multas[i].fecha);
			if(estadobus==0)
				fprintf(ap,"Pagado");
			else
				fprintf(ap,"No pagado");
		}
	if(boton==0)
		printf("\n\n\t No se encontraron resultados");
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'rep_multas_estado.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	fclose(ap);
	system("pause");
	return;
}

void multaspormonto(struct multa multas[200],int cantmultas)
{
	int i,j,boton=0;
	struct multa aux;
	FILE *ap;
	ap=fopen("rep_multas_monto.txt","w");
	if(ap==NULL)
	{
		printf("\n\n\n\t\t\t Error! Fallo en el sistema\n\n\n\n");
		system("pause");
		exit(1);
	}
	for(i=0;i<cantmultas;i++)
		for(j=i+1;j<cantmultas;j++)
			if(multas[i].monto<multas[j].monto)
			{
				aux=multas[i];
				multas[i]=multas[j];
				multas[j]=aux;
			}
	printf("\n\n\t\t REPORTE DE MULTAS POR FECHA:");
	fprintf(ap,"REPORTE DE MULTAS POR FECHA\nNumero de prestamo\tMonto de la multa\tFecha\tEstado");
	printf("\n\nNumero de prestamo            Monto de la multa             Fecha                         Estado\n");
	for(i=0;i<cantmultas;i++)
		if(multas[i].estado==1)
		{
			boton=1;
			printf("\n%-30d%-30.2f%-30s",multas[i].num,multas[i].monto,multas[i].fecha);
			printf("No pagado");
			fprintf(ap,"\n%-30d%-30.2f%-30s",multas[i].num,multas[i].monto,multas[i].fecha);
			fprintf(ap,"No pagado");
		}
	if(boton==0)
		printf("\n\n\t No hay multas activas");
	printf("\n\n\t\t LISTO, PARA ABRIR EL ARCHIVO EN EXCEL, UBIQUE EL ARCHIVO 'rep_multas_monto.txt' Y SIGA LAS INSTRUCCIONES EN EL MANUAL DE USUARIO.");			
	printf("\n\n\n\n\t\t");
	fclose(ap);
	system("pause");
	return;
}

void impresionmultas(struct multa multas[200],int cantmultas,float valormulta)
{
	int i;
	FILE *ap;
	ap = fopen("multas.txt","w"); // Se checa que funcione correctamente.
	if(ap == NULL)
	{
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tError! Fallo en el sistema.\n\n\n\n\n");   
		exit(1);             
	}
	fprintf(ap,"%f",valormulta);
	for(i=0;i<cantmultas;i++)
		fprintf(ap,"\n%d\t%f\t%s\t%d",multas[i].num,multas[i].monto,multas[i].fecha,multas[i].estado);
	fclose(ap);
	return;
}
