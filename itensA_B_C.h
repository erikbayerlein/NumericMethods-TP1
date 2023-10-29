#ifndef itensA_B_C_H
#define itensA_B_C_H

#include <list>

void desenhar_tabela(int k, float d, float fd);

void newton_itemA(double a3, double a2, double d0, double epsilon);

void newton_itemB_entrada_padrao(double a3, double a2, double d0, double lambda, double epsilon);

void newton_itemB(double a3, double a2, double lambda, double epsilon);

void newton_itemA2_raphson(double a3, double a2, double epsilon);

double derivada_f(double d, double a3, double a2);

double funcao_d(double d, double a3, double a2);

double derivada_diferenca_finita(double d, double a3, double a2, double (*func)(double, double, double), double h);

void newton_itemC(double a3, double a2, double d0, double lambda, double epsilon, double h);

double raio_raizes(double a3, double a2);

bool diverge(double x, double fx);

std::list<double> chutes_iniciais(double raio, double a3, double a2);

bool diverge(double x, double fx);


#endif //itensA_B_C_H
