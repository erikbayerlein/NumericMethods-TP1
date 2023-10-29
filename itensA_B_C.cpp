#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <list>
#include <array>
#include <string>

#include "itensA_B_C.h"

using namespace std;

// retorna uma lista com os chutes iniciais a serem feitos
list<double> chutes_iniciais(double raio, double a3, double a2) {

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


//f(d) = a3d3 – 9a2 == 3a3d² - 9a2
double derivada_f(double d, double a3, double a2){
    return (3*a3*(pow(d,2))-9*a2);
}

//f(d) = a3d3 – 9a2d + 3
double funcao_d(double d, double a3, double a2){
    return (a3*(pow(d,3)) - 9*a2*d + 3);
}

array <double,2> raiz_derivada(double a3, double a2){
    double delta = (- 4*3*a3*(-9));

    double x1 = (0 + sqrt(delta))/(2*3*a3);
    double x2 = (0 - sqrt(delta))/(2*3*a3);

    array<double, 2> raiz = {x1, x2};

    return raiz;

}

double raio_raizes(double a3, double a2){

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

void desenhar_tabela(int k, float d, float fd, TextRaiz t) {
    std::string s;
    if (t == CONTINUAR){
        s = "absoluto(f(d)) maior ou igual a epsilon. Continuar!";
    }
    else {
        if (t == PARAR){
            s = "absoluto(f(d)) menor que epsilon. Parar!";
        }
    }

    cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
    cout << "|" << setw(4) << k << "  | " << setw(11) << d << " | " << setw(12) << fd << " | " << setw(52) << s << "|" << endl;
}


// Conclusão: raiz calculada foi tal, em K passos, o erro obtido é E e pra esse valor o 
// balanço quebra ou nao.
void conclusao(double d, int k, double fd){
    cout << "" << endl; 
    if (d > 0.3){
        cout << "CONCLUSAO: A raiz calculada e " << d << ", foi obtida em " << k
            << " passos,\no erro que faz o metodo parar e " << fd  << " e o balanco pode quebrar.\n" << endl;
    } else{
        cout << "CONCLUSAO: A raiz calculada e " << d << ", foi obtida em " << k
            << " passos,\no erro que faz o metodo parar e " << fd  << " e o balanco nao quebra.\n" << endl;
    }
    cout << "#" << setfill('-') << setw(31) << "-" << "#  ITERACOES FINALIZADAS  #" << setw(31) << "-" << setfill(' ') << "#\n\n\n" << endl;

}

// Calculo da derivada pelo método da diferença finita
double derivada_diferenca_finita(double d, double a3, double a2, double (*func)(double, double, double), double h){
    return (func(d + h, a3, a2) - func(d, a3, a2)) / h;
}

double newton_itemA(double a3, double a2, double d0, double epsilon){
    if (abs(funcao_d(d0, a3, a2)) < epsilon){
        return d0;
    }

    double fd = funcao_d(d0, a3, a2);
    double d1 = d0 - fd/derivada_f(d0, a3, a2);
    int k = 0;
    cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
    std::cout << setw(4) << "|   k" << "  | " << setw(11) << "d" << " | " <<
    setw(14) << "f(d) |" << setw(54) << "Analise |" << endl;

    while(abs(funcao_d(d0, a3, a2)) >= epsilon){
        desenhar_tabela(k, d0, fd, CONTINUAR);
        d0 = d1;
        fd = funcao_d(d0, a3, a2);
        d1 = d0 - (fd/derivada_f(d0, a3, a2));
        k+=1;
    }

    desenhar_tabela(k, d0, fd, PARAR);
    cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
    conclusao(d0, k, funcao_d(d0, a3, a2));
    return d1; 

}

void newton_itemA2_raphson(double a3, double a2, double epsilon){

    cout << "\n- Funcao de entrada: f(d) = " << a3 << " * d^3 " << (-1) * 9*a2 << " * d + 3" << endl;
    cout << "- Epsilon: " << epsilon << "\n" << endl;
    double raio = raio_raizes(a3, a2);

    list<double> d0s = chutes_iniciais(raio, a3, a2);

    list<double>::iterator d0;
    int n = 1;
    for (d0 = d0s.begin(); d0 != d0s.end(); d0++) {

        cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
        std::cout << "#" << setw(57) << "Calculo para a raiz numero " << n << setw(32)  << "#" << endl;

        if (*d0 <= 1) {

            double d0Aux = *d0;

            if (abs(funcao_d(d0Aux, a3, a2)) < epsilon) {
                cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
                cout << "\nf(" << d0Aux << ") = " << funcao_d(d0Aux, a3, a2) <<" já é menor que epsilon" << endl;
                return;
            }

            double fd = funcao_d(d0Aux, a3, a2);
            double d1 = d0Aux - fd / derivada_f(d0Aux, a3, a2);
            int k = 0;
            cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
            std::cout << setw(4) << "|   k" << "  | " << setw(11) << "d" << " | " <<
            setw(14) << "f(d) |" << setw(54) << "Analise |" << endl;

            while (abs(funcao_d(d0Aux, a3, a2)) >= epsilon) {
                desenhar_tabela(k, d0Aux, fd, CONTINUAR);
                d0Aux = d1;
                fd = funcao_d(d0Aux, a3, a2);
                d1 = d0Aux - (fd / derivada_f(d0Aux, a3, a2));
                k += 1;
            }

            desenhar_tabela(k, d0Aux, fd, PARAR);
            cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
            conclusao(d0Aux, k, funcao_d(d0Aux, a3, a2));
        } else {

            double d0Aux = *d0;

            if (abs(funcao_d(d0Aux, a3, a2)) < epsilon) {
                cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
                cout << "\nf(" << d0Aux << ") = " << funcao_d(d0Aux, a3, a2) <<" já é menor que epsilon" << endl;
                return;
            }

            cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
            double fd = funcao_d(d0Aux, a3, a2);
            double d1 = d0Aux - fd / derivada_f(d0Aux, a3, a2);
            int k = 0;

            while (abs(funcao_d(d0Aux, a3, a2)) >= epsilon) {
                d0Aux = d1;
                fd = funcao_d(d0Aux, a3, a2);
                d1 = d0Aux - (fd / derivada_f(d0Aux, a3, a2));
                k += 1;
            }

            conclusao(d0Aux, k, funcao_d(d0Aux, a3, a2));
        }

        n++;
    }
}



void newton_itemB_entrada_padrao(double a3, double a2, double d0, double lambda, double epsilon){

    if (abs(funcao_d(d0, a3, a2)) < epsilon){
        return;
    }

    if (abs(derivada_f(d0, a3, a2)) >= lambda){

        double fd = funcao_d(d0, a3, a2);
        double d1 = d0 - (fd/derivada_f(d0, a3, a2));
        double derivada = derivada_f(d0, a3, a2);
        int k = 0;
        // cabeçalho da tabela
        cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
        std::cout << setw(4) << "|   k" << "  | " << setw(11) << "d" << " | " <<
        setw(14) << "f(d) |" << setw(54) << "Analise |" << endl;

        while(abs(funcao_d(d0, a3, a2)) >= epsilon){
            desenhar_tabela(k, d0, fd, CONTINUAR);
            d0 = d1;
            fd = funcao_d(d0, a3, a2);

            if (abs(derivada_f(d0, a3, a2)) > lambda){
                derivada = derivada_f(d0, a3, a2);
                d1 = d0 - (fd/derivada);
                k +=1;
            } else {
                d1 = d0 - (fd/derivada);
                k +=1;
            }
        }

        desenhar_tabela(k, d0, funcao_d(d0, a3, a2), PARAR);
        cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
        conclusao(d0, k, funcao_d(d0, a3, a2));
        return;
    }

    std::cout << "Erro! f'(d0) < lambda: "<< endl;
    return;

}

void newton_itemB(double a3, double a2, double lambda, double epsilon){

    cout << "\n- Funcao de entrada: f(d) = " << a3 << " * d^3 " << (-1) * 9*a2 << " * d + 3" << endl;
    cout << "- Epsilon: " << epsilon << endl;
    cout << "- Lambda: " << lambda << "\n" << endl;

    double raio = raio_raizes(a3, a2);

    list<double> d0s = chutes_iniciais(raio, a3, a2);
    list<double>::iterator d0;

    int n = 0;
    for (d0 = d0s.begin(); d0 != d0s.end(); d0++) {
        n++;
        cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
        std::cout << "#" << setw(57) << "Calculo para a raiz numero " << n << setw(32)  << "#" << endl;

        if (*d0 <= 1) {
            double d0Aux = *d0;

            if (abs(funcao_d(d0Aux, a3, a2)) < epsilon){
                cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
                cout << "\nf(" << d0Aux << ") = " << funcao_d(d0Aux, a3, a2) <<" já é menor que epsilon" << endl;
                continue;
            }
    
            if (abs(derivada_f(d0Aux, a3, a2)) >= lambda){

                double fd = funcao_d(d0Aux, a3, a2);
                double d1 = d0Aux - (fd/derivada_f(d0Aux, a3, a2));
                double derivada = derivada_f(d0Aux, a3, a2);
                int k = 0;
                // cabeçalho da tabela
                cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
                std::cout << setw(4) << "|   k" << "  | " << setw(11) << "d" << " | " <<
                setw(14) << "f(d) |" << setw(54) << "Analise |" << endl;

                while(abs(funcao_d(d0Aux, a3, a2)) >= epsilon){
                    desenhar_tabela(k, d0Aux, fd, CONTINUAR);
                    d0Aux = d1;
                    fd = funcao_d(d0Aux, a3, a2);

                    if (abs(derivada_f(d0Aux, a3, a2)) > lambda){
                        derivada = derivada_f(d0Aux, a3, a2);
                        d1 = d0Aux - (fd/derivada);
                        k +=1;
                    } else {
                        d1 = d0Aux - (fd/derivada);
                        k +=1;
                    }
                }

                desenhar_tabela(k, d0Aux, funcao_d(d0Aux, a3, a2), PARAR);
                cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
                conclusao(d0Aux, k, funcao_d(d0Aux, a3, a2));
                continue;
            }

            std::cout << "Erro! f'(d0) < lambda: "<< endl;
            continue;
        } else {
            double d0Aux = *d0;

            if (abs(funcao_d(d0Aux, a3, a2)) < epsilon){
                cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
                cout << "\nf(" << d0Aux << ") = " << funcao_d(d0Aux, a3, a2) <<" já é menor que epsilon" << endl;
                continue;
            }

            if (abs(derivada_f(d0Aux, a3, a2)) >= lambda){

                cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
                double fd = funcao_d(d0Aux, a3, a2);
                double d1 = d0Aux - (fd/derivada_f(d0Aux, a3, a2));
                double derivada = derivada_f(d0Aux, a3, a2);
                int k = 0;

                while(abs(funcao_d(d0Aux, a3, a2)) >= epsilon){
                    d0Aux = d1;
                    fd = funcao_d(d0Aux, a3, a2);

                    if (abs(derivada_f(d0Aux, a3, a2)) > lambda){
                        derivada = derivada_f(d0Aux, a3, a2);
                        d1 = d0Aux - (fd/derivada);
                        k +=1;
                    } else {
                        d1 = d0Aux - (fd/derivada);
                        k +=1;
                    }
                }

                conclusao(d0Aux, k, funcao_d(d0Aux, a3, a2));
                continue;
            }

            std::cout << "Erro! f'(d0) < lambda: "<< endl;
            continue;
        }
    }
}


// Implementação do Item C
double newton_itemC_entrada_padrao(double a3, double a2, double d0, double epsilon, double h){
    if (abs(funcao_d(d0, a3, a2)) < epsilon){
        return d0;
    }

    double fd = funcao_d(d0, a3, a2);
    double d1 = d0 - (fd/derivada_diferenca_finita(d0, a3, a2, funcao_d, h));
    int k = 0;
    cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
    std::cout << setw(4) << "|   k" << "  | " << setw(11) << "d" << " | " <<
    setw(14) << "f(d) |" << setw(54) << "Analise |" << endl;

    while(abs(funcao_d(d0, a3, a2)) >= epsilon){
        desenhar_tabela(k, d0, fd, CONTINUAR);
        d0 = d1;
        fd = funcao_d(d0, a3, a2);
        d1 = d0 - (funcao_d(d0, a3, a2)/derivada_diferenca_finita(d0, a3, a2, funcao_d, h));
        k +=1;
    }

    desenhar_tabela(k, d0, fd, PARAR);
    cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
    conclusao(d0, k, funcao_d(d0, a3, a2));
    return d1;

}

void newton_itemC(double a3, double a2, double epsilon, double h){
    double raio = raio_raizes(a3, a2);

    list<double> d0s = chutes_iniciais(raio, a3, a2);
    list<double>::iterator d0;

    int n = 0;

    for(d0 = d0s.begin(); d0 != d0s.end(); d0++) {
        n++;
        double d0Aux = *d0;

        cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
        std::cout << "#" << setw(57) << "Calculo para a raiz numero " << n << setw(32)  << "#" << endl;

        if (abs(funcao_d(d0Aux, a3, a2)) < epsilon){
            cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
            cout << "\nf(" << d0Aux << ") = " << funcao_d(d0Aux, a3, a2) <<" já é menor que epsilon" << endl;
            continue;
        }

        double fd = funcao_d(d0Aux, a3, a2);
        double d1 = d0Aux - (fd/derivada_diferenca_finita(d0Aux, a3, a2, funcao_d, h));
        int k = 0;

        cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
        std::cout << setw(4) << "|   k" << "  | " << setw(11) << "d" << " | " <<
                 setw(14) << "f(d) |" << setw(54) << "Analise |" << endl;

        while(abs(funcao_d(d0Aux, a3, a2)) >= epsilon){
            desenhar_tabela(k, d0Aux, fd, CONTINUAR);
            d0Aux = d1;
            fd = funcao_d(d0Aux, a3, a2);
            d1 = d0Aux - (funcao_d(d0Aux, a3, a2)/derivada_diferenca_finita(d0Aux, a3, a2, funcao_d, h));
            k +=1;
        }

        desenhar_tabela(k, d0Aux, fd, PARAR);
        cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
        conclusao(d0Aux, k, funcao_d(d0Aux, a3, a2));
    }
/*
    double fd = funcao_d(d0, a3, a2);
    double d1 = d0 - (fd/derivada_diferenca_finita(d0, a3, a2, funcao_d, h));
    int k = 0;
    cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
    std::cout << setw(4) << "|   k" << "  | " << setw(11) << "d" << " | " <<
              setw(14) << "f(d) |" << setw(54) << "Analise |" << endl;

    while(abs(funcao_d(d0, a3, a2)) >= epsilon){
        desenhar_tabela(k, d0, fd, CONTINUAR);
        d0 = d1;
        fd = funcao_d(d0, a3, a2);
        d1 = d0 - (funcao_d(d0, a3, a2)/derivada_diferenca_finita(d0, a3, a2, funcao_d, h));
        k +=1;
    }

    desenhar_tabela(k, d0, fd, PARAR);
    cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
    conclusao(d0, k, funcao_d(d0, a3, a2));
    continue;
*/
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