#ifndef FUNCIONES_CERDO_ORIGINAL_H_INCLUDED
#define FUNCIONES_CERDO_ORIGINAL_H_INCLUDED

int mostrar_menu_y_elegir_opcion();
void elegir_quien_empieza(string &jugador_1, string &jugador_2);
string turno_act(string jugador1, string jugador2, int i);
char preguntar_si_quiere_seguir_tirando(char s_n, int pos_X, int pos_Y);
int con_cuantos_dados_tira (int vec[2][5], bool barro, bool &tres_dados);
void tira_con_dos_dados (int vec[2][5], bool &barro, char &s_n, int Tactual, int pos_X, int pos_Y);
void tira_con_tres_dados (int vec[2][5], bool &barro, char &s_n, int Tactual, int pos_X, int pos_Y);
int tirar_dado ();
void hitos(int vector_hitos[2][5], int vector_trufas[2][5]);
void ganador(string jugador1, string jugador2, int vec_H[2][5], string vec_rank_max[3], int vec_rank_puntos_max[3]);
void cargar_ranking(string vec_rank_max[3]);
void mostrar_estadisticas(string vec_rank_max[3], int vec_rank_puntos_max[3]);
void guardar_max_estadistica(string vec_rank_max[3], int vec_rank_puntos_max[3], string ganador, int puntos_ganador);
int centrar_en_X(string texto);
void showItem(const char* text, int tam_texto, int posy, bool selected);
void dibujar_rectangulo(int pos_X, int pos_Y);
void jugar(int vector_trufas_oink_lanz[2][5], string jugador_1, string jugador_2, int var_i, int var_x, bool &barro, bool &truf_mas_50);
void mostrar_hitos(string jugador_1, string jugador_2, int vector_hitos[2][5], int vector_trufas_oink_lanz[2][5], string Ranking_max[3], int Ranking_max_puntos[3]);
void mostrar_creditos();

#endif // FUNCIONES_CERDO_ORIGINAL_H_INCLUDED
