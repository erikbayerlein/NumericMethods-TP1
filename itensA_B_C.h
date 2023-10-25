#ifndef itensA_B_C_H
#define itensA_B_C_H

#include <list>

void desenhar_tabela(int k, float d, float fd);

double newton_itemA(double a3, double a2, double d0, double epsilon);

double derivada_f(double d, double a3, double a2);

double funcao_d(double d, double a3, double a2);

double newton_itemB(double a3, double a2, double d0, double lambda, double epsilon);

double derivada_diferenca_finita(double d, double a3, double a2, double (*func)(double, double, double), double h);

double newton_itemC(double a3, double a2, double d0, double lambda, double epsilon, double h);

double isolamento_intervalo(double a3, double a2);

double newton_itemA2_raphson(double a3, double a2, double epsilon);

std::list<double> intervalos_raizes(double raio, double a3, double a2);


#endif //itensA_B_C_H
