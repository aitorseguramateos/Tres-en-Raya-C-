//librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constantes
#define FIL 3 //definicion de la dimensión de las filas
#define COL 3 //definición de la dimensión de las columnas
#define error_nombre 5

//variables globales
char table[FIL][COL];
int fila;
int columna;
char nombre1[20] ; //variable para acumular el nombre de la funcion nombres_x
char nombre2[20] ;//variable para acumular el nombre de la funcion nombres_o
char nombre[20] = "\0";

void pedir_jugador(char *valor){
	printf("%s : ", valor);
	fgets(nombre, 20, stdin);
	nombre[strlen(nombre) - 1] = '\0';  // Eliminamos salto de linea de fgets
	fflush(stdin);
}


// Pide nombre de los jugadores y los valida
void pedir_nombres(){
    char valor[50];
    int error;
	error = error_nombre;					// inicializamos con error
	// pedimos nombre del primer jugador
	while (error == error_nombre){	    // Mientras haya error
		strcpy(valor, "Introduce el nombre del primer jugador, que juega con X");
		pedir_jugador (valor);		// pedimos nombre de jugador 1 y se valida
		if (nombre[0] == '\0' || nombre[0] == '\r' || nombre[0] == '\n' ){
			error = error_nombre;
			printf("\n\nEl nombre del jugador no puede estar vacÃ­o.\n\n");
		}else{
			strcpy(nombre1,nombre);		// guardamos en nombre1
			error = 0;		// reset del error
		}
	}
	// pedimos nombre del segundo jugador
	error = error_nombre;
	while (error == error_nombre)  {
		strcpy(valor, "Introduce el nombre del  jugador, que juega con O");
		pedir_jugador (valor);
		if (nombre[0] == '\0' || nombre[0] == '\r' || nombre[0] == '\n' ){
			error = error_nombre;
			printf("\n\nEl nombre del jugador no puede estar vacÃ­o.\n\n");
		}else{
			strcpy(nombre2,nombre);
			error = 0;
		}
	}
}

//funcion para relllenar
void rellenar(){
    char contador;

    //inizialización de variables
    contador = '0';

    for (fila=0;fila<FIL;fila++){
        for (columna=0;columna<COL;columna++){
            ++contador;
            table[fila][columna] = contador;
        }
    }

}

//funcion para la creación del tablero
void tablero(){

    for (fila=0; fila<FIL;fila++){
        printf("\n          +---+---+---+\n");
        printf("          |");

        for (columna=0;columna<COL;columna++){
            printf(" %c |",table[fila][columna]);
        }
    }
    printf("\n          +---+---+---+\n\n");
}

//funcion para pedir posiciones
int pedirposicion(char jugador){
    int posicion; //variable para asignar la posicion al usuario
    char pfinal;
    char tirada[1];

    do{
        printf("Elija una posicion para marcar %c: ",jugador);
        fflush(stdin);
        //posicion = getchar();

        scanf("%d",&posicion);
        pfinal = posicion;
        fflush(stdin);
        if (pfinal > 9){
            printf("Error: Posicion incorrecta\n");
            printf("Posibles valores: '1', '2', '3', '4', '5', '6', '7', '8', '9'.\n");
        }
    }while(pfinal>9 || pfinal<0);
    return pfinal;
}


//funcion para substituir x por los numeros segun elija el usuario
int substituir(int posicion,char jugador){
    char tirada[1];
    int fila;
    int columna;
    int encontrado;

    //inizialización de variables
    encontrado = 0;

    sprintf(tirada,"%d",posicion);

    for (fila = 0; fila < FIL; fila++){
        for (columna = 0; columna < COL; columna++){
            if (table[fila][columna]==tirada[0]){
                table[fila][columna] = jugador;
                encontrado = 1;
            }
        }
    }
    return encontrado;
}

int comprobarlleno(){
    int lleno;
    int posicion;
    int fila;
    int columna;

    //inizialización de variables
    lleno= 1;
    fila = 0;
    columna = 0;

    for (fila = 0; fila < FIL; fila++){
        for (columna = 0; columna < COL; columna++){
            if (table[fila][columna]!='X' && table[fila][columna]!='O'){
                lleno=0;
            }
        }
    }
    return lleno;
}

//funcion para mostrar el menu
void menu(){
    printf(" ####### ######  #######  #####     ####### #     #    ######     #    #     #    #    \n");
    printf("    #    #     # #       #     #    #       ##    #    #     #   # #    #   #    # #   \n");
    printf("    #    #     # #       #          #       # #   #    #     #  #   #    # #    #   #  \n");
    printf("    #    ######  #####    #####     #####   #  #  #    ######  #     #    #    #     # \n");
    printf("    #    #   #   #             #    #       #   # #    #   #   #######    #    ####### \n");
    printf("    #    #    #  #       #     #    #       #    ##    #    #  #     #    #    #     # \n");
    printf("    #    #     # #######  #####     ####### #     #    #     # #     #    #    #     # \n\n");
    printf("*** TRES EN RAYA (Fase 3) ***\n");
    printf("Autor: Aitor Segura.\n\n");
}

int ganador(){
    char ganador;
    int i;
    int j;
    int enviar;
    char posicion_anterior;

    enviar = 0;

    for (i = 0; i < FIL; i++){
        if(table[i][0] == table[i][1] && table[i][1] == table[i][2]){
            ganador = table[i][0];
        }
    }

    for (j = 0; j < COL; j++){
        if(table[0][j] == table[1][j] && table[1][j] == table[2][j]){
            ganador = table[0][j];
        }
    }

    if (table[0][0] == table[1][1] && table[1][1] == table[2][2]){
        ganador = table[1][1];
    }
    if (table[0][2] == table[1][1] && table[1][1] == table[2][0]){
        ganador = table[1][1];
    }

    if (ganador == 'X'){
        enviar = 1;
    }
    if (ganador == 'O'){
        enviar = 2;
    }
    return enviar;
}

//Esqueleto del código
int main(){
    char table[FIL][COL]; //declaración del array
    char contador; //variable contador para el interior de las celdas
    char jugador; //variable para asignar la posicion al jugador
    int comprobar; //variable para comprobar si esta lleno
    int encontrado; //variable para ver substiuir
    int recorrido; //variable para controlar la ejecucion del tablero
    int posicion;
    char *mensaje;
    int gan;

    //inizialización de variables
    fila = 0;
    columna = 0;
    recorrido = 0;
    encontrado = 1;

    menu();
    rellenar(); //llamada a la funcion rellanar
    pedir_nombres();
    system("cls");
    do{
        menu();
        printf("Elija otra posicion diferente.\n");

        if (encontrado == 0){
            printf("ERROR: La casilla %d ocupada!\n",posicion);
        }



        printf("\n");
        tablero(); //llamada a la funcion de creación del tablero

        if (recorrido % 2 == 0){
            jugador = 'X';
            printf("Turno de %s: Jugador %c.\n",nombre1,jugador);
        }
        else{
            jugador = 'O';
            printf("Turno de %s: Jugador %c.\n",nombre2,jugador);
        }

        posicion = pedirposicion(jugador); //llamada a la funcion para pedir posiciones del tablero
        comprobar = comprobarlleno();
        encontrado = substituir(posicion,jugador); //llamada a la funcion para añadir x al tablero
        gan = ganador();

        if (posicion==0){
            mensaje = "Juego finalizado anticipadamente.\n";
        }

        if (encontrado==1){
            recorrido++;
        }

        if (recorrido == 9){
            mensaje = "El tablero está lleno!\n";
        }

        if (gan==1){
            jugador = 'X';
            mensaje = nombre1;
        }
        else if (gan==2){
            jugador = 'O';
            mensaje = nombre2;
        }

        system("cls");
    }while (recorrido < 9 && posicion != 0 && gan == 0);
    menu();
    if (gan==1 || gan==2){
        printf("El ganador es => %s (jugador %c)\n",mensaje,jugador);
    }
    else{
        printf("%s",mensaje);
    }
    tablero();
    printf("*** FIN JUEGO ***\n");
    return 0;
}
