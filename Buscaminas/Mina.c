#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
#define Terreno 11

char tablero_comp[Terreno][Terreno];
char terreno_del_juego[Terreno][Terreno];
int pierdes = 0;
 
/* Prototipos de funciones utilizadas */
void Pantalla();
void Tablero();
void Tablero_M();
void Minas();
void Imprimir_tab();
void Tablero_C();
void Inicio();
int juego();
void otra_vez();
int ganar();
void Minas_P(int, int);
int registro_minas_a(int, int);
 

int main ()
{
	setlocale(LC_ALL, "spanish");
    Pantalla();
    sleep(2);
 	Beep(100, 1000);
 	system("color B0");
    printf("\t\t\t\t\t      Presiona ENTER para iniciar.");
    

 
    getchar();
    system("cls");
 
    Inicio();
 
    return 0;
 
}
 
/* Crea un tablero con las minas randomizadas */
void Tablero()
{
 
    int i, j;
 
    for(i = 0; i < Terreno; i++)
        for(j = 0; j < Terreno; j++)
            tablero_comp[i][j] = 'o';
 
    Minas();			//FUNCIÓN QUE CREA LAS MINAS *Importante*
}
 

void Tablero_M()
{
 
    int i, j;
    int fil, col, cur = 4;
    printf("Generando minas... \nIniciado\n\n");
    // Coloca 'o' en el terreno
    for(i = 0; i < Terreno; i++)
        for(j = 0; j < Terreno; j++)
            terreno_del_juego[i][j] = 'o';
     

    // Imprime la parte exterior
 
    for(col = 0; col < Terreno; col++)
        printf("%d ", col + 1);
     
    printf("\n\n");
 
    for(fil = 0; fil < Terreno; fil++)
    {
        for(col = 0; col < Terreno; col++)
        {
            printf("%c ", terreno_del_juego[fil][col]);
        }
        printf(" %d ", fil + 1);
        printf("\n");
    }
}
 
/* Creación de minas aleatorias */
void Minas()
{
    int i, random;
    srand(time(0));
     
    for (i = 0; i < Terreno; i++)
    {
        random = rand() % (Terreno);
        tablero_comp[random][i] = '*';
    }
 
}
 
/* Imprime solo el tablero (In-Game) */
void Imprimir_tab()
{
    int fil, col;
 
    system("cls");
    for(col = 0; col < Terreno; col++)
        printf("%d ", col + 1);
     
    printf("\n\n");
        for(fil = 0; fil < Terreno; fil++)
    {
        for(col = 0; col < Terreno; col++)
        {
            printf("%c ", terreno_del_juego[fil][col]);
        }
        printf(" %d ", fil + 1);
        printf("\n");
    }
}
 
/* Imprime el tablero y sus minas */
void Tablero_C()
{
    int fil, col;
 
    system("cls");
    for(col = 0; col < Terreno; col++)
        printf("%d ", col + 1);
     
    printf("\n\n");
        for(fil = 0; fil < Terreno; fil++)
    {
        for(col = 0; col < Terreno; col++)
        {
            printf("%c ", tablero_comp[fil][col]);
        }
        printf(" %d ", fil + 1);
        printf("\n");
    }
}
 
int juego()
{
    int seleccion_fila2 = 0, seleccion_columna2 = 0, 
        minas_cercanas = 0, minas_cercanas2 = 0,
        minas_cercanas3 = 0, minas_cercanas4 = 0,
        minas_cercanas5 = 0, minas_cercanas6 = 0,
        minas_cercanas7 = 0, minas_cercanas8 = 0,
        i = 0;
 
    //- Determina el número de fila seleccionada y luego procede a 
    //-	Preguntar el número de columna (base)
    do {
    printf("\nSelecciona una casilla (Utiliza las coordenadas de los costados) \n");
    printf("Fila--> ");
    scanf("%d", &seleccion_fila2);
    printf("Columna--> ");
    scanf("%d", &seleccion_columna2);
     
    } while(seleccion_fila2 < 1 || seleccion_fila2 > Terreno || seleccion_columna2 < 1 || seleccion_fila2 > Terreno);
    // ^ Determina si el usuario repitió jugada
 
    Minas_P(seleccion_fila2 - 1, seleccion_columna2 - 1);
 
    if(pierdes == 1)
        return -1;
     
    // Verifica si hay minas cercanas al jugador
    // determina las coordenadas de cada mina generada en el tablero
    // en las minas cercanas actualiza el tablero_comp.
    minas_cercanas = registro_minas_a(seleccion_fila2 - 1, seleccion_columna2 - 1);
    terreno_del_juego[seleccion_fila2 - 1][seleccion_columna2 - 1] = (char)( ((int)'0') + minas_cercanas );
 
    /*--------------------------------------------------
     La siguiente lista pretender determinar las minas aledañas	
     para ello se estima el ciclo y las casillas descubiertas (0)	
     una vez el programa detecta que casillas tienen minas		
     Asigna el digito de minas aledañas en las direcciones		
     arriba, abajo, izq, der, y sus diagonales (NE, SO, etc...)	
    */
    if(minas_cercanas == 0)
    {
        if(seleccion_columna2 != Terreno)
        {
            i = 0;
            while(minas_cercanas == 0 && (seleccion_columna2 - 1 + i) < Terreno)
            {
        
                minas_cercanas = registro_minas_a(seleccion_fila2 - 1, (seleccion_columna2 - 1 + i));
                if(minas_cercanas != -1)
                {
                terreno_del_juego[seleccion_fila2 - 1][(seleccion_columna2 - 1) + i] = (char) ( ((int)'0') + minas_cercanas );
                i++;
                }
            }
                if(seleccion_fila2 != 1)
                {
                    i = 0;
                    while(minas_cercanas5 == 0 && (seleccion_columna2 - 1 + i) < Terreno && (seleccion_fila2 - 1 - i) > 0)
                    {
            
                        minas_cercanas5 = registro_minas_a((seleccion_fila2 - 1 - i), (seleccion_columna2 - 1 + i));
                        if(minas_cercanas5 != -1)
                        {
                        terreno_del_juego[(seleccion_fila2 - 1) - i][(seleccion_columna2 - 1) + i] = (char) ( ((int)'0') + minas_cercanas5);
                        i++;
                        }
                    }
                }
                if(seleccion_fila2 != Terreno)
                {
                    i = 0;
                    while(minas_cercanas6 == 0 && (seleccion_fila2 - 1 + i) < Terreno && (seleccion_columna2 - 1 + i) < Terreno )
                    {
             
                        minas_cercanas6 = registro_minas_a((seleccion_fila2 - 1 + i), (seleccion_columna2 - 1 + i));
                        if(minas_cercanas != -1)
                        {
                        terreno_del_juego[(seleccion_fila2 - 1) + i][(seleccion_columna2 - 1) + i] = (char) ( ((int)'0') + minas_cercanas6);
                        i++;
                        }
                    }
                }
        }
 
        if(seleccion_fila2 != Terreno)
        {
            i = 0;
            while(minas_cercanas2 == 0 && (seleccion_fila2 - 1 + i) < Terreno)
            {
              
                minas_cercanas2 = registro_minas_a((seleccion_fila2 - 1 + i), seleccion_columna2 - 1);
                if(minas_cercanas2 != -1)
                {
                terreno_del_juego[(seleccion_fila2 - 1) + i][seleccion_columna2 - 1] = (char) ( ((int)'0') + minas_cercanas2 );
                i++;
                }
            }
 
            if(seleccion_columna2 != Terreno)
            {
                i = 0;
                while(minas_cercanas7 == 0 && (seleccion_fila2 - 1 + i) < Terreno && (seleccion_columna2 - 1 - i) > 0)
                {
           
                    minas_cercanas7 = registro_minas_a((seleccion_fila2 - 1 + i), (seleccion_columna2 - 1 - i));
                    if(minas_cercanas != -1)
                    {
                    terreno_del_juego[(seleccion_fila2 - 1) + i][(seleccion_columna2 - 1) - i] = (char) ( ((int)'0') + minas_cercanas7);
                    i++;
                    }
                }
            }
        }
 
        if(seleccion_fila2 != 1)
        {
            i = 0;
            while(minas_cercanas3 == 0 && (seleccion_fila2 - i) > 0)
            {
  
                minas_cercanas3 = registro_minas_a((seleccion_fila2 - 1 - i), seleccion_columna2 - 1);
                if(minas_cercanas3 != -1)
                {
                terreno_del_juego[(seleccion_fila2 - 1) - i][seleccion_columna2 - 1] = (char) ( ((int)'0') + minas_cercanas3 );
                i++;
                }
            }
            if(seleccion_columna2 != Terreno)
            {
                while(minas_cercanas8 == 0 && (seleccion_columna2 - 1 - i) > 0 && (seleccion_fila2 - 1 - i) > 0)
                {
  
                    minas_cercanas8 = registro_minas_a((seleccion_fila2 - 1 - i), (seleccion_columna2 - 1 - i));
                    if(minas_cercanas8 != -1)
                    {
                    terreno_del_juego[(seleccion_fila2 - 1) - i][(seleccion_columna2 - 1) - i] = (char) ( ((int)'0') + minas_cercanas8);
                    i++;
                    }
                }    
            }
        }
 
        if(seleccion_columna2 != 1)
        {
            i = 0;
            while(minas_cercanas4 == 0 && (seleccion_columna2 - i) > 0)
            {
 
                minas_cercanas4 = registro_minas_a(seleccion_fila2 - 1, (seleccion_columna2 - 1 - i));
                if(minas_cercanas4 != -1)
                {
                terreno_del_juego[seleccion_fila2 - 1][(seleccion_columna2 - 1) - i] = (char) ( ((int)'0') + minas_cercanas4 );
                i++;
                }
            }
        }
    }
 
 
 
    // Determina si el jugador ha ganado (no quedan casillas)
    if(ganar() == TRUE)
    {
        system("cls");
        Tablero_C();
        printf("\n\nHas ganado, felicidades!\n\n");
        otra_vez();
    }
 
    return 0;
}
 
void Minas_P(int seleccion_fila, int seleccion_colum)
{
    if(tablero_comp[seleccion_fila][seleccion_colum] == '*')
    {
        printf("\nBOOM! pisaste una mina por si no quedó claro.\n");
        getchar(); getchar();
        pierdes = 1;
    }
}
 

int registro_minas_a(int seleccion_fila, int seleccion_colum)
{
    int conteo_minas = 0;
     
    if(tablero_comp[seleccion_fila][seleccion_colum] == '*')
    {
        return -1;
    }
    
    if(seleccion_fila < (Terreno - 1) && seleccion_colum < (Terreno - 1))
    {
 
        if(tablero_comp[seleccion_fila + 1][seleccion_colum] == '*')
            conteo_minas++;

        if(tablero_comp[seleccion_fila][seleccion_colum + 1] == '*')
            conteo_minas++;
  
        if(tablero_comp[seleccion_fila + 1][seleccion_colum + 1] == '*')
            conteo_minas++;
 
 
        if(seleccion_colum != 0)
        {
     
            if(tablero_comp[seleccion_fila + 1][seleccion_colum - 1] == '*')
                conteo_minas++;

            if(tablero_comp[seleccion_fila][seleccion_colum - 1] == '*')
                conteo_minas++;
        }
      
        if(seleccion_fila != 0)
        {
       
            if(tablero_comp[seleccion_fila - 1][seleccion_colum] == '*')
                conteo_minas++;
       
            if(tablero_comp[seleccion_fila - 1][seleccion_colum + 1] == '*')
                conteo_minas++;
       
            if(seleccion_colum != 0)
            {
   
                if(tablero_comp[seleccion_fila - 1][seleccion_colum - 1] == '*')
                    conteo_minas++;
            }
        }
    }

    if(seleccion_fila == (Terreno - 1) && seleccion_colum != (Terreno - 1))
    {
   
            if(tablero_comp[seleccion_fila - 1][seleccion_colum] == '*')
                conteo_minas++;

            if(tablero_comp[seleccion_fila - 1][seleccion_colum + 1] == '*')
                conteo_minas++;
    }

    if(seleccion_colum == (Terreno - 1) && seleccion_fila != (Terreno - 1))
    {
 
            if(tablero_comp[seleccion_fila][seleccion_colum - 1] == '*')
                conteo_minas++;

            if(tablero_comp[seleccion_fila + 1][seleccion_colum - 1] == '*')
                conteo_minas++;
    }

    if(seleccion_fila == (Terreno - 1) && seleccion_colum == (Terreno - 1))
    {
            if(tablero_comp[seleccion_fila][seleccion_colum - 1] == '*')
                conteo_minas++;
            if(tablero_comp[seleccion_fila - 1][seleccion_colum - 1] == '*')
                conteo_minas++;
            if(tablero_comp[seleccion_fila - 1][seleccion_colum] == '*')
                conteo_minas++;
    }
 
    return conteo_minas;
}
 
int ganar()
{
    int fil, col;
 
    for(fil = 0; fil < Terreno; fil++)
        for(col = 0; col < Terreno; col++)
        {
            if(terreno_del_juego[fil][col] == 'o' && tablero_comp[fil][col] != '*')
                return FALSE;
        }
 
    return TRUE;
}
void otra_vez()
{
    char res;
 
    printf("\n\n¿Volver a jugar? (y/n) --> ");
    scanf(" %c", &res);
 
    if(toupper(res) == 'Y')
    {
        system("cls");
        Inicio();
    }
 
    else
    {
        printf("\n\nCerrando...");
        (void) getchar();
        exit(EXIT_SUCCESS);
    }
}
void Pantalla()
{
	printf("\n\n\n\n\n\t\t\t\t\t%c--------------------------------------%c\n", 1, 2);
	printf("|\t\t\t\t\t|O0O0O0O0XO0O0O0XO0O0O0XO0O0O0XO0O0O0X0|\n");
	printf("\t\t\t\t\t|--------------------------------------|\n");
    printf("\t\t\t\t\t|Bienvenido al buscaminas de consola   |\n");
    printf("\t\t\t\t\t|------------------------------------- |\n");
    printf("\t\t\t\t\t|O0O0O0O0XO0O0O0XO0O0O0XO0O0O0XO0O0O0X0|");
    printf("\n\t\t\t\t\t%c--------------------------------------%c\n", 2, 1);
    printf("\n");
    printf("\n\n");
}
 
void Inicio()
{
    pierdes = 0; 
    Tablero();
    Tablero_M();
     
    // Inicio
    do
    {
    juego();
    Imprimir_tab();
    } while(pierdes != 1);    // Ciclo mientras el jugador siga jugando sin perder
 
    // Revela las minas
    Tablero_C();
 
    otra_vez();
}
