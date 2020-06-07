//--------------ESTRUCTURAS-------------
struct usuarios
{
	char mat[' '];
	char nombre[50];
	char direc[100];
	int estado;
	int cantlibros;	
};

struct biblio{
	char clave[' ']; 		//Clave del libro estilo sistema dewey
	int exi;				//Cantidad de libros en existencia
	int edi;				//Numero de edicion del libro
	int dia;				//Dia de publicacion del libro
	int mes;				//Mes de publicacion del libro
	int ano;				//Año de publicacion del libro
	int vecesprestado;		//Numero de veces que se ha prestado un libro
	int cat;				//Categoria del libro siguiendo el sistema dewey
	char pais[' '];			//País de origen del libro
	char titulo[' '];		//Titulo del libro
	char autor[' ']; 		//Autor del libro
	char editorial[' '];	//Editorial del libro
};

struct prestamo
{
	int num;
	char fechap[10];
	char fechae[10];	
	char mat[' ']; // de usuarios
	char clave[' ']; // de libros
	int estado; 
};

struct multa
{
	int num; // de prestamos
	float monto;
	char fecha[10];
	int estado;
};
//--------------------------------------

//----------------FUNCIONES-------------

// USUARIOS
int usus(struct usuarios usuarios[100],int cantusuarios);

// menus 
int menuusuario(struct usuarios usuarios[100],int cantusuarios); //

// operaciones de captura de datos
int agusuario(struct usuarios usuarios[100],int cantusuarios); //

//eliminar usuario
int eliminarusuario(struct usuarios usuarios[100],int cantusuarios);

// operaciones de lectura de los datos en el archivo
int lecturausuarios(struct usuarios usuarios[100],int cantusuarios); //
void impresionusuarios(struct usuarios usuarios[100],int cantusuarios);

// operaciones de modificacion de datos
void modifusuario(struct usuarios usuarios[100],int cantusuarios);

// operaciones de consulta
void conusu(struct usuarios usuarios[100],int cantusuarios); //

// consulta de usuario
void conusugen(struct usuarios usuarios[100],int cantusuarios);
void conusugenrep(struct usuarios usuarios[100],int cantusuarios);
void conusumatricula(struct usuarios usuarios[100],int cantusuarios); //
void conusuestado(struct usuarios usuarios[100],int cantusuarios);
void conusucantlibros(struct usuarios usuarios[100],int cantusuarios);

// LIBROS
int libs(struct biblio libros[100],int cantl,struct prestamo prestamos[' '],int cantprestamos);
void impresionlibros(struct biblio libros[100],int cantlibros);

//eliminar libro
int rip(struct biblio libros[100],int cunt);

//captura de datos
int add(struct biblio libros[100],int cunt);

// reportes
void reportes(struct biblio libros[100],int cunt,struct prestamo prestamos[200],int cantprestamos),rtitulo(struct biblio libros[100],int cunt),rautor(struct biblio libros[100],int cunt),rano(struct biblio libros[100],int cunt),rpais(struct biblio libros[100],int cunt),reditorial(struct biblio libros[100],int cunt),rcant(struct biblio libros[100],int cunt),rclave(struct biblio libros[100],int cunt), redo(struct biblio libros[100],int cunt,struct prestamo prestamos[' '],int cantprestamos);

// formatos
void encabezado(),tabla(struct biblio libros[100],int l,int i);

// busquedas
void search(struct biblio libros[100],int cunt),asearch(struct biblio libros[100],int cunt),nsearch(struct biblio libros[100],int cunt),isearch(struct biblio libros[100],int cunt),csearch(struct biblio libros[100],int cunt);

// Lectura de archivo
int contarlibros(struct biblio libros[100]);

// PRESTAMOS
int prests(struct biblio libros[100],struct usuarios usuarios[100],struct prestamo prestamos[200],int cantlibros,int cantusuarios,int cantprestamos,struct multa multas[200],int cantmultas,float valormulta);
int menuprestamos(struct prestamo prestamos[' '],int cantprestamos,int cantlib,int cantusuarios,struct usuarios usuarios[' '],struct biblio libros[' '],struct multa multas[200],int cantmultas);

//	FUNCIONES PARA CARGAR Y GUARDAR DATOS
void impresionprestamos(struct prestamo prestamos[' '],int cantprestamos);
//	FUNCIONES DEL MENU PRINCIPAL
int represtamos(struct prestamo prestamos[' '],int cantprestamos,int cantlib,int cantusuarios,struct usuarios usuarios[' '],struct biblio libros[' ']);
void entprestamos(struct prestamo prestamos[' '],int cantprestamos,struct multa multas[200],int cantmultas,struct usuarios usuarios[100],int cantusuarios);
//	FUNCIONES DE CONSULTAS
void conprestamos(struct prestamo prestamos[' '],int cantprestamos);
void conpresgen(struct prestamo prestamos[' '],int cantprestamos);
void conpresdia(struct prestamo prestamos[' '],int cantprestamos);
void conpresmes(struct prestamo prestamos[' '],int cantprestamos);
void conpresano(struct prestamo prestamos[' '],int cantprestamos);
void conpresclav(struct prestamo prestamos[' '],int cantprestamos);
void conpresest(struct prestamo prestamos[' '],int cantprestamos);
void conpresmat(struct prestamo prestamos[' '],int cantprestamos);
//	FUNCIONES PARA REALIZAR ACCIONES
void encabezadopres(int l);
void tablapres(int l,int i,struct prestamo prestamos[' '],int cantprestamos,FILE *ap);
void convertirfechae(int i,char dia[' '],char mes[' '],char ano[' '],struct prestamo prestamos[' '],int cantprestamos);
void convertirfechap(int i,char dia2[' '],char mes2[' '],char ano2[' '],struct prestamo prestamos[' '],int cantprestamos);

//--------------------------------------

// MULTAS
float multax(struct multa multas[200],int cantmultas,float valormulta);

// lectura
int lecturamultas(struct multa multas[200],int cantmultas,struct prestamo prestamos[200],int cantprestamos,struct usuarios usuarios[100],int cantusuarios);
int compara_fechas(int dia1,int mes1,int ano1,int dia2,int mes2,int ano2);
float lecturavalor(struct multa multas[200],int cantmultas);

// editar multa
float editar_multa(float valormulta);

// reportes
void reportes_multa(struct multa multas[200],int cantmultas);
void multasporfecha(struct multa multas[200],int cantmultas);
int fechamayor(char *fecha1,char *fecha2);
void multasporestado(struct multa multas[200],int cantmultas);
void multaspormonto(struct multa multas[200],int cantmultas);

void impresionmultas(struct multa multas[200],int cantmultas,float valormulta);

// VALIDACIONES

int validar_entero(char *n)//valida entero positivo, regresa un valor booleano
{
	int i;
	for(i=0;n[i]!='\0';i++)
		if(isdigit(n[i])==0)
			return 1;
	return 0;
}

//----------------------------------------------------------------------------------------------------
int validar() //validacion integrada en la funcion
{
		int entero,iint,yint,pint;
		char num[' '];
		do
		{
			
			fflush(stdin);
			gets(num);
			yint=strlen(num);
			pint=1;
			for(iint=0;iint<yint;iint++)
			{	
				if(!isdigit(num[iint]))	
				{
					pint=0;
					printf("\n\n\t Introduzca un numero entero mayor a cero: ");
					break;
				}					
			}
			if(yint==0)
			{
				pint=0;
				printf("\n\n\t Introduzca un numero entero mayor a cero: ");							
			}
		}	while(pint==0);
		
		entero= atoi(num);
		return entero;
		
}

int valifecha(int dia,int mes,int anio)
{
	//La funcion devuelve 1 si la fecha ingresada es correcta
	//Y devolvera 0 si la fecha ingresada no es correcta
   
    if ( mes >= 1 && mes <= 12 )
    {
        switch ( mes )
        {
            case  1 :
            case  3 :
            case  5 :
            case  7 :
            case  8 :
            case 10 :
            case 12 : if ( dia >= 1 && dia <= 31 )
                          return 1;
                      else
                          return 0;
                      break;

            case  4 :
            case  6 :
            case  9 :
            case 11 : if ( dia >= 1 && dia <= 30 )
                          return 1;
                      else
                          return 0;
                      break;

            case  2 : if( anio % 4 == 0 && anio % 100 != 0 || anio % 400 == 0 )
                          if ( dia >= 1 && dia <= 29 )
                              return 1;
                          else
                              return 0;
                      else
                          if ( dia >= 1 && dia <= 28 )
                              return 1;
                          else
                              return 0;
        }
    }
    else
        return 0;
    
}

int revisarInt(char str[]) //valida entero
{
	// marcador es 1 si ya se ha encontrado un numero 
	// marcador2 es 1 si ya se ha encontrado un signo negativo
	int k, marcador, marcador2;
	
	if (strlen(str) == 0)
		return 0;
	
	for (k=0, marcador=0, marcador2 = 0; str[k] != '\0'; k++)
	{
		if (marcador == 0 && isdigit(str[k]) != 0)
			marcador = 1;
			
		if (isdigit(str[k]) == 0 && str[k] != ' ' && str[k] != '-')
			return 0;
			
		if (str[k] == ' ' && (marcador == 1 || marcador2 == 1))
			return 0;
		
		if (str[k] == '-')
		{
			if (marcador == 1 || marcador2 == 1)
				return 0;
			marcador2 = 1;
		}
	}
	
	if (marcador == 0)
		return 0;
	
	return 1;
}

// revisarFloat retorna 1 si el numero dado es flotante, 0 de lo contrario
// esta funcion requere hacer un #include <string.h>
int revisarFloat(char str[])
{
	// marcador es 1 si ya se ha encontrado un numero 
	// marcador2 es 1 si ya se ha encontrado un signo negativo
	// marcador3 es si ya se ha encontrado un punto
	
	int k, marcador, marcador2, marcador3;
	
	if (strlen(str) == 0)
		return 0;
	
	for (k=0, marcador=0, marcador2=0, marcador3=0; str[k] != '\0'; k++)
	{
		if (marcador == 0 && isdigit(str[k]) != 0)
			marcador = 1;
			
		if (isdigit(str[k]) == 0 && str[k] != ' ' && str[k] != '-' && str[k] !='.')
			return 0;
			
		if (str[k] == ' ' && (marcador == 1 || marcador2 == 1 || marcador3 == 1))
			return 0;
		
		if (str[k] == '-')
		{
			if (marcador == 1 || marcador2 == 1 || marcador3 == 1)
				return 0;
			marcador2 = 1;
		}
		
		if (str[k] == '.')
		{
			if (marcador3 == 1)
				return 0;
			marcador3 = 1;
		}
	}
	
	if (marcador == 0)
		return 0;
	
	return 1;
}

// revisarString retorna 1 si el numero dado es una cadena de caracteres que consiste solo de caracteres alfabeticos, 0 de lo contrario
// esta funcion requere hacer un #include <ctype.h>
int revisarString(char str[])
{
	int i;
	
	for (i=0; str[i] != '\0'; i++)
	{
		if(isalpha(str[i]) == 0 && str[i] != ' ')
		{
	 		return 0;
		}
	}
	
	return 1;
}

int validar_real(char *aux)
{
	int i,p=0;
	if(strlen(aux)==0)
		return 1;
	for(i=0;aux[i]!='\0';i++)
		if(p==0&&aux[i]=='.')
			p=1;
		else
			if(isdigit(aux[i])==0)
				return 1;
	return 0;
}

//--------------------------------------
