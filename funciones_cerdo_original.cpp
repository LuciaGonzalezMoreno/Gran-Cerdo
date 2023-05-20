#include <iostream>
#include <string>
using namespace std;
#include <cstdlib> // system()
#include <ctime> // srand/rand
#include <cmath> // ceil
#include "rlutil.h" // libreria lrutil
#include "funciones_cerdo_original.h"

// muestra el MENU al usuario y le pide elegir la opcion que deseada
int mostrar_menu_y_elegir_opcion()
{
    int key, y=0;

    rlutil::hidecursor();
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);

    do
    {
        showItem("EL GRAN CERDO", 13, 5, y==-1); // 13 son los caracteres de EL GRAN CERDO - 5 la posicion en Y
        showItem("---------------------", 21, 6, y==-1);
        showItem("JUGAR", 5, 7, y==0);
        showItem("ESTADÍSTICAS", 12, 8, y==1);
        showItem("CERDITOS",8, 9, y==2);
        showItem("---------------------", 21, 10, y==-1);
        showItem("SALIR",5, 11, y==3);

        rlutil:: locate(35, 15);
        cout << "  ^..^--" << endl;
        rlutil:: locate(35, 16);
        cout << " @_      )~"<< endl;
        rlutil:: locate(35, 17);
        cout << "   `w  w´"<< endl;
        rlutil:: locate(35, 18);
        cout << endl;

        switch (key=rlutil::getkey())
        {
        case 14: // UP
            y--;
            if(y<0)
            {
                y = 0;
            }
            break;
        case 15: // DOWN
            y++;
            if(y>3)
            {
                y = 3;
            }
            break;
        default:
            break;
        }
    }
    while(key==14||key==15||key!=1);

    system ("cls");
    cin.clear();
    return y;
}

// segun las reglas se establece quien empieza el juego
void elegir_quien_empieza(string &jugador1, string &jugador2)
{
    int dado_1, dado_2, dado_3, dado_4;
    string aux;

    rlutil::setBackgroundColor(rlutil::MAGENTA);
    rlutil :: cls ();

    rlutil:: locate(2, 1);
    cout << "GRAN CERDO";
    rlutil:: locate(1, 2);
    cout << "--------------------------------------------------------------------------------";

    cin.sync();
    rlutil::showcursor();
    rlutil:: locate(2, 3);
    cout << "Ingrese el nombre del jugador 1: ";
    getline(cin, jugador1);
    rlutil:: locate(2, 4);
    cout <<"Ingrese el nombre del jugador 2: ";
    getline(cin, jugador2);

    rlutil:: locate(2, 6);
    cout << "ENTER para lanzar dados!!";
    rlutil :: anykey();

    do
    {
        srand(time(NULL));
        rlutil::hidecursor();

        dado_1 = ((rand() %6)+1);
        dado_2 = ((rand() %6)+1);
        rlutil:: locate(2, 6);
        cout << "Dados " << jugador1 << ": " << dado_1 << " " << dado_2 << "                         ";

        dado_3 = ((rand() %6)+1);
        dado_4 = ((rand() %6)+1);
        rlutil:: locate(2, 7);
        cout << "Dados " << jugador2 << ": " << dado_3 << " " << dado_4 << "                         ";

        //si la suma de los dados del 2do jugador es mas alta que la del 1er jugador
        if(dado_1+dado_2<dado_3+dado_4)
        {
            aux = jugador1;
            jugador1 = jugador2;
            jugador2 = aux;
        }
        else
        {
            //si la suma es igual
            if((dado_1+dado_2)==(dado_3+dado_4))
            {
                //si el jugador 2 obtuvo el numero de dado mas alto
                if((dado_3>dado_1&&dado_3>dado_2)||(dado_4>dado_1&&dado_4>dado_2))
                {
                    aux = jugador1;
                    jugador1 = jugador2;
                    jugador2 = aux;
                }
                else
                {
                    //si obtuvieron los mismos dados
                    if((dado_3==dado_1)||(dado_3==dado_2))
                    {
                        aux = "N";
                    }
                }
            }
        }
    }
    while(aux == "N");

    rlutil:: locate(2, 9);
    cout <<"El jugador que empieza es ---------> " << jugador1;

    rlutil:: locate(2, 11);
    cout << "  ^..^--" << endl;
    cout << " @_      )~"<< endl;
    cout << "   `w  w´"<< endl;
    cout << endl;

    rlutil:: locate(2, 16);
    cout <<"ENTER para continuar...";
    rlutil :: anykey();
    system("cls");
}

//turno actual
string turno_act(string jugador1, string jugador2, int vuelta)
{
    if(vuelta==1)
    {
        return jugador1;
    }
    else
    {
        return jugador2;
    }
}

//pregunta si quiere seguir tirando y valida la respuesta
char preguntar_si_quiere_seguir_tirando(char s_n, int pos_X, int pos_Y)
{
    do
    {
        rlutil:: locate(pos_X, pos_Y);
        rlutil::showcursor();
        cout << "¿Continuar lanzando? (S/N): ";
        cin >> s_n;
        rlutil::hidecursor();
    }
    while(s_n!='s' && s_n!='S' && s_n!='n' && s_n!='N');

    return s_n;
}

//tira con 2 o 3 dados
int con_cuantos_dados_tira (int vec[2][5], bool barro, bool &trufas_50)
{
    if(((vec[0][0] + vec[0][1] <=50) || (vec[1][0] + vec[1][1]<=50)) && barro==false && trufas_50==false)
    {
        return 2;
    }
    else
    {
        trufas_50 = true;
        return 3;
    }
}

//TIRA CON DOS DADOS
void tira_con_dos_dados (int vec[2][5], bool &barro, char &s_n, int Tactual, int pos_X, int pos_Y)
{
    int dado_1, dado_2;

    dado_1 = tirar_dado();
    dado_2 = tirar_dado();

    rlutil:: locate(pos_X, pos_Y);
    cout << dado_1 << " " << dado_2;

    pos_Y+=2;

    //si las caras son distintas entre si, y ninguna es 1
    //acumula la suma de las caras
    if((dado_1!=dado_2) && dado_1!=1 && dado_2!=1)
    {
        if(Tactual == 1)
        {
            vec[0][1]+= dado_1+dado_2; // trufas ronda
            rlutil:: locate(pos_X, pos_Y);
            cout << "Sumaste " << dado_1+dado_2 << " trufas!";
        }
        else
        {
            vec[1][1]+= dado_1+dado_2; // trufas ronda
            rlutil:: locate(40, pos_Y);
            cout << "Sumaste " << dado_1+dado_2 << " trufas!";
        }
    }
    else
    {
        //si las caras son iguales entre si, y ninguna es 1
        //hizo un OINK y acumula el doble de la suma de las caras
        //esta obligado a volver a tirar
        if((dado_1==dado_2) && dado_1!=1)
        {
            if(Tactual == 1)
            {
                vec[0][2] ++; //oink
                vec[0][1] += ((dado_1+dado_2)*2); // trufas ronda
                s_n = 's';
                rlutil:: locate(pos_X, pos_Y);
                cout << "Sumaste " << (dado_1+dado_2)*2 << " trufas!";
                rlutil:: locate(pos_X, pos_Y++);
                cout << "¡HICISTE UN OINK Y VUELVES A TIRAR!!" ;
                rlutil :: anykey();
            }
            else
            {
                vec[1][2] ++; //oink
                vec[1][1] += ((dado_1+dado_2)*2);  // trufas ronda
                s_n = 's';
                rlutil:: locate(40, pos_Y);
                cout << "Sumaste " << (dado_1+dado_2)*2 << " trufas!";
                rlutil:: locate(40, pos_Y++);
                cout << "¡HICISTE UN OINK Y VUELVES A TIRAR!!" ;
                rlutil :: anykey();
            }
        }
        else
        {
            //si las caras son distintas entre si, y una es 1
            //pierde todas las trufas acumuladas de la ronda y cede el turno
            if((dado_1!=dado_2) && (dado_2==1||dado_1==1 ))
            {
                if(Tactual == 1)
                {
                    vec[0][1] = 0; // trufas ronda
                    s_n = 'N';
                    rlutil:: locate(pos_X, pos_Y);
                    cout << "¡Pierdes tus trufas :(!";
                    rlutil :: anykey();
                }
                else
                {
                    vec[1][1] = 0; // trufas ronda
                    s_n = 'N';
                    rlutil:: locate(40, pos_Y);
                    cout << "¡Pierdes tus trufas :(!";
                    rlutil :: anykey();
                }
            }
            else
            {
                //si las caras son iguales entre si, y ambas son 1
                //se hunde en el barro
                //pierde todas las trufas acumuladas de la ronda y las acumuladas, y cede el turno
                if((dado_1==dado_2) && dado_1==1 )
                {
                    if(Tactual == 1)
                    {
                        vec[0][0] = 0; // trufas acumuladas
                        vec[0][1] = 0; // trufas ronda
                        barro = true;
                        s_n = 'N';
                        rlutil:: locate(pos_X, pos_Y);
                        cout << "¡Perdiste todas las trufas y el turno!";
                        rlutil :: anykey();
                    }
                    else
                    {
                        vec[1][0] = 0; // trufas acumuladas
                        vec[1][1] = 0; // trufas ronda
                        barro = true;
                        s_n = 'N';
                        rlutil:: locate(40, pos_Y);
                        cout << "¡Perdiste todas las trufas y el turno!";
                        rlutil :: anykey();
                    }
                }
            }
        }
    }
}

//TIRA CON TRES DADOS
void tira_con_tres_dados (int vec[2][5], bool &barro, char &s_n, int Tactual, int pos_X, int pos_Y)
{
    int dado_1, dado_2, dado_3;

    dado_1 = tirar_dado();
    dado_2 = tirar_dado();
    dado_3 = tirar_dado();

    rlutil:: locate(pos_X, pos_Y);
    cout << dado_1 << " " << dado_2 <<  " " << dado_3 << endl;

    pos_Y+=2;

    //si las caras son distintas a 1 y no son las 3 iguales (no importa que haya 2 iguales)
    //acumula la suma de las caras
    if((dado_1!=dado_2 || dado_1!=dado_3) && (dado_1!=1 && dado_2!=1 && dado_3!=1))
    {
        if(Tactual == 1)
        {
            vec[0][1]+= (dado_1+dado_2+dado_3); // trufas ronda
            rlutil:: locate(pos_X, pos_Y);
            cout << "Sumaste " << dado_1+dado_2+dado_3 << " trufas!";
        }
        else
        {
            vec[1][1]+= (dado_1+dado_2+dado_3); // trufas ronda
            rlutil:: locate(40, pos_Y);
            cout << "Sumaste " << dado_1+dado_2+dado_3 << " trufas!";
        }
    }
    else
    {
        //si las caras son iguales entre si, y ninguna es 1
        //hizo un OINK y acumula el doble de la suma de las caras
        //esta obligado a volver a tirar
        if((dado_1==dado_2 && dado_1==dado_3) && (dado_1!=1 ))
        {
            if(Tactual == 1)
            {
                vec[0][2] ++; //oink
                vec[0][1] += (dado_1+dado_2+dado_3)*2; // trufas ronda
                s_n = 's';
                rlutil:: locate(pos_X, pos_Y);
                cout << "Sumaste " << (dado_1+dado_2+dado_3)*2 << " trufas!";
                rlutil:: locate(pos_X, pos_Y++);
                cout << "¡HICISTE UN OINK Y VUELVES A TIRAR!!" ;
                rlutil :: anykey();
            }
            else
            {
                vec[1][2] ++; //oink
                vec[1][1] += (dado_1+dado_2+dado_3)*2; // trufas ronda
                s_n = 's';
                rlutil:: locate(40, pos_Y);
                cout << "Sumaste " << (dado_1+dado_2+dado_3)*2 << " trufas!";
                rlutil:: locate(40, pos_Y++);
                cout << "¡HICISTE UN OINK Y VUELVES A TIRAR!!" ;
                rlutil :: anykey();
            }
        }
        else
        {
            //si una o dos de las caras son 1 (no las 3)
            //pierde todas las trufas acumuladas de la ronda y cede el turno
            if((dado_1!=1 && (dado_2==1 || dado_3==1)) || ((dado_1==1 || dado_3==1) && dado_2!=1) || ((dado_1==1 || dado_2==1) && dado_3!=1))
            {
                if(Tactual == 1)
                {
                    vec[0][1] = 0; // trufas ronda
                    s_n = 'N';
                    rlutil:: locate(pos_X, pos_Y);
                    cout << "¡Pierdes tus trufas :(!";
                    rlutil :: anykey();
                }
                else
                {
                    vec[1][1] = 0; // trufas ronda
                    s_n = 'N';
                    rlutil:: locate(40, pos_Y);
                    cout << "¡Pierdes tus trufas :(!";
                    rlutil :: anykey();
                }
            }
            else
            {
                //si las caras son iguales entre si, y las tres son 1
                //se hunde en el barro
                //pierde todas las trufas acumuladas de la ronda y las acumuladas, y cede el turno
                if((dado_1==dado_2 && dado_2==dado_3) && (dado_1==1))
                {
                    if(Tactual == 1)
                    {
                        vec[1][0] += vec[0][0] ; // suma al jugador 2 las trufas acumuladas del jugador 1
                        vec[0][0] = 0; // trufas acumuladas
                        vec[0][1] = 0; // trufas ronda
                        barro = true;
                        s_n = 'N';
                        rlutil:: locate(pos_X, pos_Y);
                        cout << "¡PERDISTE  TODAS LAS TRUFAS!";
                        rlutil:: locate(pos_X, pos_Y++);
                        cout << "¡Ya no puedes seguir tirando!";
                        rlutil :: anykey();
                    }
                    else
                    {
                        vec[0][0] += vec[1][0] ; // suma al jugador 1 las trufas acumuladas del jugador 2
                        vec[1][0] = 0; // trufas acumuladas
                        vec[1][1] = 0; // trufas ronda
                        barro = true;
                        s_n = 'N';
                        rlutil:: locate(40, pos_Y);
                        cout << "¡PERDISTE  TODAS LAS TRUFAS!";
                        rlutil:: locate(40, pos_Y++);
                        cout << "¡Ya no puedes seguir tirando!";
                        rlutil :: anykey();
                    }
                }
            }
        }
    }
}

int tirar_dado ()
{
    //srand (time(0));
    return ((rand() %6)+1);
}

void hitos(int vector_hitos[2][5], int vector_trufas[2][5])
{
    if(vector_trufas[0][0] > vector_trufas[1][0])
    {
        vector_hitos[0][0] = 5;
    }
    else
    {
        if(vector_trufas[0][0] < vector_trufas[1][0])
        {
            vector_hitos[1][0] = 5;
        }
        else
        {
            vector_hitos[0][0] = 5;
            vector_hitos[1][0] = 5;
        }
    }

    vector_hitos[0][1] = ceil(vector_trufas[0][0]/50); //1 PDV cada 50 trufas
    vector_hitos[1][1] = ceil(vector_trufas[1][0]/50);

    vector_hitos[0][2] = vector_trufas[0][2]*2; // 2 PDV por cada OINK
    vector_hitos[1][2] = vector_trufas[1][2]*2;

    if(vector_trufas[0][4] > vector_trufas[1][4]) // mayor cant de lanzamientos
    {
        vector_hitos[0][3] = 3;
    }
    else
    {
        if(vector_trufas[0][4] < vector_trufas[1][4])
        {
            vector_hitos[1][3] = 3;
        }
        else
        {
            vector_hitos[0][3] = 3;
            vector_hitos[1][3] = 3;
        }
    }

    for(int i=0; i<2; i++)
    {
        for(int x=0; x<4; x++)
        {
            vector_hitos[i][4]+=vector_hitos[i][x];
        }
    }
}

void ganador(string jugador1, string jugador2, int vec_H[2][5], string vec_rank_max[3], int vec_rank_puntos_max[3])
{
    string ganador, AUX = " - ";
    int puntos_ganador;

    if(vec_H[0][4] > vec_H[1][4] ) // en el indice 4 se guardar los PVD TOTALES ganados
    {
        ganador = jugador1;
        puntos_ganador = vec_H[0][4];

        cout << "GANADOR: " << jugador1 << " con " << vec_H[0][4] << " de puntos de victoria!" << endl;
    }
    else
    {
        if(vec_H[0][4] < vec_H[1][4] )
        {
            ganador = jugador2;
            puntos_ganador = vec_H[1][4];

            cout << "GANADOR: " << jugador2 << " con " << vec_H[1][4] << " de puntos de victoria!" << endl;
        }
        else
        {
            ganador = jugador1 += AUX += jugador2;
            puntos_ganador = vec_H[0][4];

            cout << "GANADOR: " << "EMPATE, ambos con " << vec_H[0][4] << " puntos de victoria!" << endl;
        }
    }

    guardar_max_estadistica(vec_rank_max, vec_rank_puntos_max, ganador, puntos_ganador);
}

void cargar_ranking(string vec_rank_max[3])
{
    for(int x=0; x<3; x++)
    {
        vec_rank_max[x] = "VACIO";
    }
}

void mostrar_estadisticas(string vec_rank_max[3], int vec_rank_puntos_max[3])
{
    int posy = 5, tam ;

    rlutil:: locate((centrar_en_X("ESTADISTICAS")), posy++);
    rlutil::setBackgroundColor(rlutil::MAGENTA);
    cout << "ESTADISTICAS";

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil:: locate((centrar_en_X("---------------------")), posy++);
    cout << "---------------------";


    for(int x=0; x<3; x++)
    {
        tam=0;

        tam+=vec_rank_max[x].size();

        if(vec_rank_puntos_max[x] < 9)
        {
            tam+=(9+1); // 9 son los caracteres de PUNTOS y " - "
        }
        else
        {
            if(vec_rank_puntos_max[x] < 99)
            {
                tam+=(9+2);
            }
            else
            {
                tam+=(9+3);
            }
        }
        tam = rlutil::tcols() /2 - tam / 2;
        rlutil:: locate(tam, posy);
        rlutil::setBackgroundColor(rlutil::BLACK);
        cout << vec_rank_max[x] << " - " << vec_rank_puntos_max[x] << " PDV";
        posy++;
    }
    rlutil:: locate((centrar_en_X("---------------------")), posy++);
    cout << "---------------------";
    rlutil:: locate((centrar_en_X("ENTER para volver al MENU")), posy+2);
    cout << "ENTER para volver al MENU";
    rlutil :: anykey();
    system ("cls");
}

void guardar_max_estadistica(string vec_rank_max[3], int vec_rank_puntos_max[3], string ganador, int puntos_ganador)
{
    if(puntos_ganador > vec_rank_puntos_max[0])
    {
        vec_rank_puntos_max[2] = vec_rank_puntos_max[1];
        vec_rank_puntos_max[1] = vec_rank_puntos_max[0];
        vec_rank_puntos_max[0] = puntos_ganador;
        vec_rank_max[2] = vec_rank_max[1];
        vec_rank_max[1] = vec_rank_max[0];
        vec_rank_max[0] =ganador;
    }
    else
    {
        if(puntos_ganador > vec_rank_puntos_max[1])
        {
            vec_rank_puntos_max[2] = vec_rank_puntos_max[1];
            vec_rank_puntos_max[1] = puntos_ganador;
            vec_rank_max[2] = vec_rank_max[1];
            vec_rank_max[1] = ganador;
        }
        else
        {
            if(puntos_ganador > vec_rank_puntos_max[2])
            {
                vec_rank_puntos_max[2] = puntos_ganador;
                vec_rank_max[2] = ganador;
            }
        }
    }
}

int centrar_en_X(string texto)
{
    int posx;
    return posx = rlutil::tcols() /2 - texto.size() / 2;
}

void showItem(const char* text, int tam_texto, int posy, bool selected)
{
    int posx=0;
    if (selected)
    {
        rlutil::setBackgroundColor(rlutil::MAGENTA);
        posx = (rlutil::tcols() /2 - tam_texto/ 2);
        rlutil::locate(posx-3, posy);
        cout << " " << "»" << " " << text << " " << "«" << " ";
        rlutil::setBackgroundColor(rlutil::BLACK);
    }
    else
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        posx = (rlutil::tcols() /2 - tam_texto/ 2);
        rlutil::locate(posx-3, posy);
        cout << "   " << text << "   ";
        rlutil::setBackgroundColor(rlutil::BLACK);
    }
}

void dibujar_rectangulo(int pos_X, int pos_Y)
{
    rlutil::locate(pos_X, pos_Y++);
    cout << "+-------------------------+";
    rlutil::locate(pos_X, pos_Y++);
    cout << "|                         |";
    rlutil::locate(pos_X, pos_Y++);
    cout << "|                         |";
    rlutil::locate(pos_X, pos_Y++);
    cout << "|                         |";
    rlutil::locate(pos_X, pos_Y++);
    cout << "+-------------------------+";
}

void jugar(int vector_trufas_oink_lanz[2][5], string jugador_1, string jugador_2, int var_i, int var_x, bool &barro, bool &truf_mas_50)
{
    string tur_actual;
    char s_n; //si sigue tirando o no (S o N)

    do
    {
        int cant_dados=0, ubic_en_X;

        s_n = 'S';

        rlutil:: locate(2, 1);
        cout << "GRAN CERDO";
        rlutil:: locate(2, 2);
        cout << "-----------------------------------------------------------------------------";
        rlutil:: locate(2, 3);
        cout << jugador_1 << ": " << vector_trufas_oink_lanz [0][0] << " trufas acumuladas";
        rlutil:: locate(40, 3);
        cout << jugador_2 << ": " << vector_trufas_oink_lanz [1][0] << " trufas acumuladas";
        cout << endl;

        tur_actual = turno_act(jugador_1, jugador_2, var_i);
        if(tur_actual==jugador_1)
        {
            ubic_en_X=2;
        }
        else
        {
            ubic_en_X=40;
        }

        rlutil:: locate(ubic_en_X, 5);
        cout << "TURNO DE " << tur_actual;

        dibujar_rectangulo(ubic_en_X, 6);

        rlutil:: locate(ubic_en_X+2, 7);
        cout << "RONDA #" << var_x;
        rlutil:: locate(ubic_en_X+2, 8);
        cout << "TRUFAS DE LA RONDA: " << vector_trufas_oink_lanz [var_i-1][1];
        rlutil:: locate(ubic_en_X+2, 9);
        cout << "LANZAMIENTOS: " << vector_trufas_oink_lanz [var_i-1][3];

        rlutil:: locate(ubic_en_X, 12);
        cout << "ENTER para lanzar dados!!";
        rlutil :: anykey();

        vector_trufas_oink_lanz [var_i-1][3] ++; // suma lanzamiento

        rlutil:: locate(ubic_en_X, 12);
        cout << "LANZAMIENTO # " << vector_trufas_oink_lanz [var_i-1][3] << "             ";

        cant_dados = con_cuantos_dados_tira (vector_trufas_oink_lanz, barro, truf_mas_50);

        if(cant_dados==2)
        {
            tira_con_dos_dados (vector_trufas_oink_lanz, barro, s_n, var_i, ubic_en_X, 13); // 13 es la posicion en y
        }
        else
        {
            tira_con_tres_dados (vector_trufas_oink_lanz, barro, s_n, var_i, ubic_en_X, 13);
        }

        if(s_n == 'S')
        {
            s_n = preguntar_si_quiere_seguir_tirando(s_n, ubic_en_X, 16);
        }
        system ("cls");
    }
    while(s_n =='s' || s_n =='S');

    if(vector_trufas_oink_lanz [var_i-1][3] > vector_trufas_oink_lanz [var_i-1][4]) // si los lanzamientos de la ronda son mayores que los max, los acumula en max
    {
        vector_trufas_oink_lanz [var_i-1][4] = vector_trufas_oink_lanz [var_i-1][3];
    }
    vector_trufas_oink_lanz [0][0] += vector_trufas_oink_lanz [0][1] ; //suma las trufas de la ronda en las acumuladas
    vector_trufas_oink_lanz [1][0] += vector_trufas_oink_lanz [1][1] ; //suma las trufas de la ronda en las acumuladas
}

void mostrar_hitos(string jugador_1, string jugador_2, int vector_hitos[2][5], int vector_trufas_oink_lanz[2][5], string Ranking_max[3], int Ranking_max_puntos[3])
{
    int ubic_en_X=2;

    rlutil:: locate(ubic_en_X, 1);
    cout << "GRAN CERDO";
    rlutil:: locate(ubic_en_X, 2);
    cout << "-----------------------------------------------------------------------------";

    rlutil:: locate(ubic_en_X, 4);
    cout << "HITO" << endl;
    rlutil:: locate(ubic_en_X, 5);
    cout << "-----------------------------------------------------------------------------";
    rlutil:: locate(ubic_en_X, 6);
    cout << "Mas trufas en total ";
    rlutil:: locate(ubic_en_X, 7);
    cout << "Cada 50 trufas ";
    rlutil:: locate(ubic_en_X, 8);
    cout << "Oinks";
    rlutil:: locate(ubic_en_X, 9);
    cout << "Cerdo codicioso ";
    rlutil:: locate(ubic_en_X, 10);
    cout << "-----------------------------------------------------------------------------";
    rlutil:: locate(ubic_en_X, 11);
    cout << "TOTAL ";

    ubic_en_X+= 25; // segunda columna

    for(int x=0; x<2; x++)
    {
        rlutil:: locate(ubic_en_X, 4);
        if(x==0)
        {
            cout << jugador_1 << endl;
        }
        else
        {
            cout << jugador_2 << endl;
        }

        rlutil:: locate(ubic_en_X, 6);
        cout << vector_hitos[x][0] << " PDV (" << vector_trufas_oink_lanz[x][0] << " trufas)";
        rlutil:: locate(ubic_en_X, 7);
        cout <<  vector_hitos[x][1] << " PDV ("<< (vector_hitos[x][1] *50) << " trufas)";
        rlutil:: locate(ubic_en_X, 8);
        cout << vector_hitos[x][2] << " PDV (" << (vector_hitos[x][2] /2) << " Oinks)" << endl;
        rlutil:: locate(ubic_en_X, 9);
        cout << vector_hitos[x][3] << " PDV (" << vector_trufas_oink_lanz[x][4] << " lanzamientos)" << endl;
        cout << "-----------------------------------------------------------------------------";
        rlutil:: locate(ubic_en_X, 11);
        cout << vector_hitos[x][4] << " PDV" << endl;

        ubic_en_X+=25;
    }

    rlutil:: locate(2, 13);
    ganador(jugador_1, jugador_2, vector_hitos, Ranking_max, Ranking_max_puntos);

    rlutil:: locate(2, 15);
    cout << "ENTER para volver al MENU!!";
    rlutil :: anykey();
    rlutil::setBackgroundColor(rlutil::BLACK);
    system ("cls");
}

void mostrar_creditos()
{
    int posy=5;

    rlutil:: locate((centrar_en_X("CERDITOS")), posy++);
    rlutil::setBackgroundColor(rlutil::MAGENTA);
    cout << "CERDITOS";

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil:: locate((centrar_en_X("---------------------")), posy++);
    cout << "---------------------";

    rlutil:: locate((centrar_en_X("Maria Lucia Gonzalez Moreno - Legajo 25945")), posy++);
    cout << "Maria Lucia Gonzalez Moreno - Legajo 25945";

    rlutil:: locate((centrar_en_X("---------------------")), posy++);
    cout << "---------------------";

    rlutil:: locate((centrar_en_X("ENTER para volver al MENU")), posy+2);
    cout << "ENTER para volver al MENU";

    rlutil::anykey();
    system ("cls");
}
