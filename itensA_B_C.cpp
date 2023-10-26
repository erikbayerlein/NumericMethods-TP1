#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <list>
#include <array>

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

// retorna uma lista com os chutes iniciais a serem feitos
list<double> intervalos_raizes(double raio, double a3, double a2) {

    list<double> d0s;
    int sinal;
    double aux;

    if (funcao_d(-raio, a3, a2) < 0) {
        sinal = -1;
    } else {
        sinal = 1;
    }

    for(double i = -raio; i<=raio; i++) {
        if (funcao_d(i, a3, a2) < 0 && sinal > 0) {
            sinal = -1;
            aux = (i-1 + i)/2;
            d0s.push_back(aux);
        } else if (funcao_d(i, a3, a2) > 0 && sinal < 0) {
            sinal = 1;
            aux = (i-1 + i)/2;
            d0s.push_back(aux);
        }
    }

    return d0s;
}


double isolamento_intervalo(double a3, double a2){

    double a2new = -9*a2;
    double a0 = 3;

    double x = a2new/a3;
    double x1 = a0/a3;

    double raio;

    if (max({x, x1}) < 0) {
        return 1;
    };

    raio = 1 + max({x, x1});

    return raio;
}

void desenhar_tabela(int k, double d, double fd) {
    std::cout << setfill('-') << setw(34) << "-" << setfill(' ') << endl;
    std::cout << setw(3) << k << " | " << setw(12) << d << " | " << setw(12) << fd << endl;
}


// Conclusão: raiz calculada foi tal, em K passos, o erro obtido é E e pra esse valor o 
// balanço quebra ou nao.
void conclusao(double d, int k, double fd){
    cout << "" << endl; 
    if (d>0.3){
        cout << "Conclusão: A raiz calculada é " << d << ", foi obtida em " << k 
            << " passos, o erro que faz o método parar é " << fd  << " e o balanço pode quebrar"<< endl;
    } else{
        cout << "Conclusão: A raiz calculada é " << d << ", foi obtida em " << k 
            << " passos, o erro que faz o método parar é " << fd  << " e o balanço nao quebra"<< endl;
    }

}


double newton_itemA(double a3, double a2, double d0, double epsilon){
    if (abs(funcao_d(d0, a3, a2)) < epsilon){
        return d0;
    }
    double d1 = d0 - (funcao_d(d0, a3, a2)/derivada_f(d0, a3, a2));
    int k = 1;
    std::cout << setw(3) << "k" << " | " << setw(12) << "d" << " | " << setw(12) << "f(d)"<< endl;
    desenhar_tabela(0, d0, funcao_d(d0, a3, a2));
    while(abs(funcao_d(d0, a3, a2) >= epsilon)){    
        d0 = d1; 
        d1 = d0 - (funcao_d(d0, a3, a2)/derivada_f(d0, a3, a2));
        double fx = funcao_d(d0, a3, a2);
        desenhar_tabela(k, d0, fx);
        k+=1;
    }

    conclusao(d0, (k-1), funcao_d(d0, a3, a2));

    return d1; 

}

double newton_itemA2_raphson(double a3, double a2, double epsilon){
    double d0 = isolamento_intervalo(a3, a2)/2;

    if (abs(funcao_d(d0, a3, a2)) < epsilon){
        return d0;
    }
    double d1 = d0 - (funcao_d(d0, a3, a2)/derivada_f(d0, a3, a2));
    int k = 1;
    std::cout << setw(3) << "k" << " | " << setw(12) << "d" << " | " << setw(12) << "f(d)"<< endl;
    desenhar_tabela(0, d0, funcao_d(d0, a3, a2));
    while(abs(funcao_d(d0, a3, a2) >= epsilon)){
        d0 = d1;
        d1 = d0 - (funcao_d(d0, a3, a2)/derivada_f(d0, a3, a2));
        double fx = funcao_d(d0, a3, a2);
        desenhar_tabela(k, d0, fx);
        k+=1;

    }

    conclusao(d0, (k-1), funcao_d(d0, a3, a2));
    return d1;

}

array <double,2> raiz_derivada(double a3, double a2){
    double delta = (- 4*3*a3*(-9));

    double x1 = (0 + sqrt(delta))/(2*3*a3);
    double x2 = (0 - sqrt(delta))/(2*3*a3);

    array<double, 2> raiz = {x1, x2};

    return raiz;

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
    
    if (abs(derivada_f(d0, a3, a2)) >= lambda){

        double d1 = d0 - (funcao_d(d0, a3, a2)/derivada_f(d0, a3, a2));  
        double derivada = derivada_f(d0, a3, a2);
        int k =1;
        // cabeçalho da tabela
        std::cout << setw(3) << "k" << " | " << setw(12) << "d" << " | " << setw(12) << "f(d)"<< endl;
        desenhar_tabela(0, d0, funcao_d(d0, a3, a2));
        while(abs(funcao_d(d0, a3, a2)) >= epsilon){
            d0 = d1;
            double fd = funcao_d(d0, a3, a2);
        
            if (abs(derivada_f(d0, a3, a2)) > lambda){
                derivada = derivada_f(d0, a3, a2);
                d1 = d0 - (funcao_d(d0, a3, a2)/derivada);
                desenhar_tabela(k, d0, fd);
                k +=1;
            } else {
                d1 = d0 - (funcao_d(d0, a3, a2)/derivada);
                desenhar_tabela(k, d0, fd);
                k +=1;
            }            
        }

        conclusao(d0, (k-1), funcao_d(d0, a3, a2));
        return d1;
    }
    
    std::cout << "Erro! f'(d0) < lambda: "<< endl;
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
    int k = 1;
    std::cout << setw(3) << "k" << " | " << setw(12) << "d" << " | " << setw(12) << "f(d)"<< endl;
    desenhar_tabela(0, d0, funcao_d(d0, a3, a2));
    while(abs(funcao_d(d0, a3, a2)) >= epsilon){
        d0 = d1;
        d1 = d0 - (funcao_d(d0, a3, a2)/derivada_diferenca_finita(d0, a3, a2, funcao_d, h));
        double fd = funcao_d(d0, a3, a2);
        desenhar_tabela(k, d0, fd);
        k +=1;
    }

    conclusao(d0, (k-1), funcao_d(d0, a3, a2));
    return d1;

}

bool diverge(double x, double fx){
    if(!isfinite(x) || !isfinite(fx)){
                                    std::cout << "   _____          __             .___           .___.__                          .__        \n";
            std::cout << "  /     \\   _____/  |_  ____   __| _/____     __| _/|__|__  __ ___________  ____ |__|__ __  \n";
            std::cout << " /  \\ /  \\_/ __ \\   __\\/  _ \\ / __ |/  _ \\   / __ | |  \\  \\/ // __ \\_  __ \\/ ___\\|  |  |  \\ \n";
            std::cout << "/    Y    \\  ___/|  | (  <_> ) /_/ (  <_> ) / /_/ | |  |\\   /\\  ___/|  | \\/ /_/  >  |  |  / \n";
            std::cout << "\\____|__  /\\___  >__|  \\____/\\____ |\\____/  \\____ | |__| \\_/  \\___  >__|  \\___  /|__|____/  \n";
            std::cout << "        \\/     \\/                 \\/             \\/               \\/     /_____/           \n";
        return true;
    }
    return false;
}