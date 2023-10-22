#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "itensA_B_C.h"

using namespace std;

//teste para A, B e C

// int main(){
//     cout << fixed << setprecision(8);

//     // Item A - Cálculo da raiz de f(d) = a3d3 – 9a2d + 3 por Newton-Raphson normal
//     double raizA = newton_itemA(1, 1, 0.5, 0.001);
//     cout << "A) Raiz: " << raizA << endl;

//     // Item B - Cálculo da raiz de f(d) = a3d3 – 9a2d + 3 por Newton-Raphson modificado
//     cout << "B) ";
//     double raizB = newton_itemB(1, 1, 0.5, 0.05, 0.001);
//     cout << raizB << endl;

//     // Item C - Cálculo da raiz de f(d) = a3d3 – 9a2d + 3 por Newton-Raphson
//     // com derivada calculada pelo método da diferença finita
//     double raizC = newton_itemC(1, 1, 0.5, 0.05, 0.001, 0.0001);
//     cout << "C) Raiz: " << raizC << endl;

// }

void desenhar_tabela(int k, float d, float fd) {
    cout << setfill('-') << setw(34) << "-" << setfill(' ') << endl;
    cout << setw(3) << k << " | " << setw(12) << d << " | " << setw(12) << fd << endl;
}


double newton_itemA(double a3, double a2, double d0, double epsilon){
    if (abs(funcao_d(d0, a3, a2)) < epsilon){
        return d0;
    }
    double d1 = d0 - (funcao_d(d0, a3, a2)/derivada_f(d0, a3, a2));
    int k = 0;
    cout << setw(3) << "k" << " | " << setw(12) << "d" << " | " << setw(12) << "f(d)"<< endl;
    while(abs(funcao_d(d0, a3, a2) >= epsilon || abs(d1-d0) >= epsilon)){    
        d0 = d1; 
        d1 = d0 - (funcao_d(d0, a3, a2)/derivada_f(d0, a3, a2));
        double fx = funcao_d(d0, a3, a2);
        desenhar_tabela(k, d0, fx);
        k+=1;

    }

    return d1; 

}


//f(d) = a3d3 – 9a2 == 3a3d² - 9a2
double derivada_f(double d, double a3, double a2){
    return (3*a3*(pow(d,2))-9*a2);
}

//f(d) = a3d3 – 9a2d + 3
double funcao_d(double d, double a3, double a2){
    return (a3*(pow(d,3)) - 9*a2*d + 3);
}

double newton_itemB(double a3, double a2, double d0, double lambda, double epsilon){
    if (abs(funcao_d(d0, a3, a2)) < epsilon){
        return d0;
    }
    
    if (derivada_f(d0, a3, a2) >= lambda){

        double d1 = d0 - (funcao_d(d0, a3, a2)/derivada_f(d0, a3, a2));  
        double derivada = derivada_f(d0, a3, a2);
        int k =0;
        // cabeçalho da tabela
        cout << setw(3) << "k" << " | " << setw(12) << "d" << " | " << setw(12) << "f(d)"<< endl;
        while(abs(funcao_d(d0, a3, a2)) >= epsilon || abs(d1-d0) >= epsilon){
            d0 = d1;
            double fd = funcao_d(d0, a3, a2);
        
            if (derivada_f(d0, a3, a2) <= lambda){
                d1 = d0 - (funcao_d(d0, a3, a2)/derivada);
                desenhar_tabela(k, d0, fd);
                k +=1;
            } else {
                derivada = derivada_f(d0, a3, a2);
                d1 = d0 - (funcao_d(d0, a3, a2)/derivada);
                desenhar_tabela(k, d0, fd);
                k +=1;
            }
            
        }

        return d1;
    }
    
    cout << "Erro! f'(d0) < lambda: ";
    return derivada_f(d0, a3, a2);
}

// Calculo da derivada pelo método da diferença finita
double derivada_diferenca_finita(double d, double a3, double a2, double (*func)(double, double, double), double h){
    return (func(d + h, a3, a2) - func(d, a3, a2)) / h;
}

// Implementação do Item C
double newton_itemC(double a3, double a2, double d0, double lambda, double epsilon, double h){
    if (abs(funcao_d(d0, a3, a2)) < epsilon){
        return d0;
    }

    double d1 = d0 - (funcao_d(d0, a3, a2)/derivada_diferenca_finita(d0, a3, a2, funcao_d, h));
    int k = 0;
    while(abs(funcao_d(d0, a3, a2)) >= epsilon || abs(d1-d0) >= epsilon){
        d0 = d1;
        d1 = d0 - (funcao_d(d0, a3, a2)/derivada_diferenca_finita(d0, a3, a2, funcao_d, h));
        double fd = funcao_d(d0, a3, a2);
        desenhar_tabela(k, d0, fd);
        k +=1;
    }

    return d1;

}