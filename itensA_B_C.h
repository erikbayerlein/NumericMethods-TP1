#ifndef itensA_B_C_H
#define itensA_B_C_H

#include <list>

using namespace std;

enum TextRaiz {
    CONTINUAR,
    PARAR
};

void desenhar_tabela(int k, float d, float fd, TextRaiz t);

double newton_itemA(double a3, double a2, double d0, double epsilon);

double derivada_f(double d, double a3, double a2);

double funcao_d(double d, double a3, double a2);

void newton_itemB_entrada_padrao(double a3, double a2, double d0, double lambda, double epsilon);

void newton_itemB(double a3, double a2, double lambda, double epsilon);

double derivada_diferenca_finita(double d, double a3, double a2, double (*func)(double, double, double), double h);

double newton_itemC(double a3, double a2, double d0, double epsilon, double h);

list<double> chutes_iniciais(double raio, double a3, double a2);

void newton_itemA2_raphson(double a3, double a2, double epsilon);

double raio_raizes(double a3, double a2);

bool diverge(double x, double fx);


#endif //itensA_B_C_H
