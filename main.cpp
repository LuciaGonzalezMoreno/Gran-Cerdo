#include <iostream>
#include <string>
#include <cstdlib> // system()
using namespace std;
#include "rlutil.h" // libreria lrutil
#include <windows.h> // tamaño consola
#include "funciones_cerdo_original.h"

int main()
{
    setlocale(LC_CTYPE, "Spanish"); // CARACTERES EN ESPAÑOL

    HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 80, 20};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

    int opcion_elegida;
    string ranking_max[3]; // ranking estadisticas NOMBRES
    int ranking_max_puntos[3] = {0}; // ranking estadisticas PUNTOS

    cargar_ranking(ranking_max); // inicializarlo en VACIO

    do
    {
        opcion_elegida = mostrar_menu_y_elegir_opcion();

        // eleccion segun menu
        switch (opcion_elegida)
        {
        case 0:
        {
            string nombre_jugador_1, nombre_jugador_2;
            bool barro=false;
            bool truf=false;

            elegir_quien_empieza(nombre_jugador_1, nombre_jugador_2);

            int vec_trufas_oink_lanz [2][5] = {0}; //TRUF ACU(0), TRUFAS RONDA(1), OINK(2), LANZ(3), LANZ MAX(4)

            // ARRANCA EL JUEGO
            for(int x=1; x<=5; x++) //5 rondas
            {
                for(int i=1; i<=2; i++) // 1 turno cada jugador en cada ronda
                {
                    vec_trufas_oink_lanz [0][1] =0; // trufas ronda en 0
                    vec_trufas_oink_lanz [0][3] =0; // lanzamientos en 0
                    vec_trufas_oink_lanz [1][1] =0; // trufas ronda en 0
                    vec_trufas_oink_lanz [1][3] =0; // lanzamientos en 0

                    jugar(vec_trufas_oink_lanz, nombre_jugador_1, nombre_jugador_2, i, x, barro, truf);
                }
                system ("cls");
            }

            int vec_hitos [2][5] = {0}; //mas trufas en total(0), cada 50 trufas (1), Oinks(2), Cerdo codicioso(3), Total(4)

            hitos(vec_hitos, vec_trufas_oink_lanz); // calcula los hitos (PDV)

            mostrar_hitos(nombre_jugador_1, nombre_jugador_2, vec_hitos, vec_trufas_oink_lanz, ranking_max, ranking_max_puntos);
        }
        break;

        case 1:
            mostrar_estadisticas(ranking_max, ranking_max_puntos);
            break;

        case 2:

            mostrar_creditos();
            break;

        case 3:
            char eleccion;
            rlutil::showcursor();
            rlutil:: locate((centrar_en_X("¿Esta seguro que quiere salir de juego? (S/N): ")), 10);
            cout << "¿Esta seguro que quiere salir de juego? (S/N): ";
            cin >> eleccion;
            rlutil::hidecursor();

            if(eleccion == 'N'  || eleccion == 'n' )
            {
                opcion_elegida = 0;
            }
            break;
        }
        system ("cls");
    }
    while(opcion_elegida!=3);

    return 0;
}
