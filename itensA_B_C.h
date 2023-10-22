#ifndef itensA_B_C_H
#define itensA_B_C_H


static void desenhar_tabela(int k, float d, float fd);

static double newton_itemA(double a3, double a2, double d0, double epsilon);

static double derivada_f(double d, double a3, double a2);

static double funcao_d(double d, double a3, double a2);

static double newton_itemB(double a3, double a2, double d0, double lambda, double epsilon);

static double derivada_diferenca_finita(double d, double a3, double a2, double (*func)(double, double, double), double h);

static double newton_itemC(double a3, double a2, double d0, double lambda, double epsilon, double h);


#endif //itensA_B_C_H
