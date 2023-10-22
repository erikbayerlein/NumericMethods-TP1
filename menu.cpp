#include <iostream>
#include <iomanip> 
#include <cmath>
#include <thread>
#include <chrono>
#include "menu.h"

using namespace std;

/**Observações:
 * Fluxo 1 >> 2 = Executar NewtonItemA
 *  -> a funcao precisa do d0 para executar = ver linha 99
 * 
 * Dados de saída: quadros resposta (com d e erro para cada a3 e a2 e l e método) e comparativo.
      Isso é pra tabela que esta imprimindo? Precisamos fazer a funcao do calculo do erro 
      relativo das respostas obtidas e adicionara coluna na tabela de saida (?)
 * 
*/

void menu() {
    while (true) {
        cout << "___  ___                  ______     _            _             _  \n";
        cout << "|  \\/  |                  | ___ \\   (_)          (_)           | | \n";
        cout << "| .  . | ___ _ __  _   _  | |_/ / __ _ _ __   ___ _ _ __   __ _| | \n";
        cout << "| |\\/| |/ _ \\ '_ \\| | | | |  __/ '__| | '_ \\ / __| | '_ \\ / _` | | \n";
        cout << "| |  | |  __/ | | | |_| | | |  | |  | | | | | (__| | |_) | (_| | | \n";
        cout << "\\_|  |_|\\___|_| |_|\\__,_| \\_|  |_|  |_|_| |_|\\___|_| .__/ \\__,_|_| \n";
        cout << "                                                   | |             \n";
        cout << "                                                   |_|             \n";
        cout << "Selecione a opcao desejada:\n\n";
        cout << "1: Testar resultado com entrada padrao a3 = 1, a2 = 1, d0 = 0,5, lambda = 0,05, e = 0,001\n\n";
        cout << "2: Testar resultado com N entradas diferentes para Lambda, a2 e a3 e uma precisao e especifica e\n\n";
        cout << "3: Encerrar Programa\n\n";

        int opcao;
        cin >> opcao;

        if (opcao == 1) {
            cout << "Entrada padrao a3 = 1, a2 = 1, d0 = 0,5, lambda = 0,05, e = 0,001\n";
            cout << "Selecione o Metodo:\n\n";
            cout << "1: Metodo Newton Padrao\n";
            cout << "2: Metodo Newton FL\n\n";

            int opcao1;
            cin >> opcao1;

            //definindo entradas padrao
            double a2 = 1, a3 = 1, d0 = 0.5, e = 0.001, lambda = 0.05;
            //SubMenu
            if (opcao1 == 1) {
                cout << "Metodo Newton padrao; Entrada padrao" << endl;
                
                //codigo do item A entrada padrao
                // newton_itemA( a3,  a2,  d0,  epsilon);
                newton_itemA(1, 1, 0.5, 0.001);
                this_thread::sleep_for(chrono::seconds(2));
                
            }
            else if (opcao1 == 2) {
                cout << "Metodo Newton FL; Entrada padrao" << endl;
                //Codigo do item B entrada padrao
                // newton_itemB( a3,  a2,  d0, lambda, epsilon);
                newton_itemB(1, 1, 0.5, 0.05, 0.001);
                this_thread::sleep_for(chrono::seconds(2));
            }
            
        }
        else if (opcao == 2) {
            cout << "N entradas diferentes para Lambda, a2 e a3 e uma precisao e especifica e\n\n";
            cout << "Selecione o Metodo:\n\n";
            cout << "1: Metodo Newton Padrao\n";
            cout << "2: Metodo Newton FL\n\n";

            int opcao1;
            cin >> opcao1;

            int N1;
            double e1, a21, a31, lambda1;
            //SubMenu
            if (opcao1 == 1) {
                cout << "Metodo Newton padrao selecionado. Informe o número (N) de opções para lambda. " << endl;
                cout << "N: "; cin >> N1;
                cout << "e: "; cin >> e1;

                for (int i = 0; i < N1; i++){
                    //a2
                    cout << "a2: " << endl; cin >> a21;
                    //a3
                    cout << "a3: " << endl; cin >> a31;
                    //**********************************************************************
                    //OBS.: o enunciado diz: "Desenvolva um sistema para calcular o valor de d 
                    // de uma oscilação de um determinado balanço." 
                    // Ele não dá o d0.
                    // Escolhemos arbitrariamente d0=0.5 => colocar em discussao
                    
                    //double newton_itemA(double a3, double a2, double d0, double epsilon);
                    newton_itemA(a31, a21, 0.5, e1);
                }
                this_thread::sleep_for(chrono::seconds(2));
                //cout << setw(3) << "k" << " | " << setw(12) << "d" << " | " << setw(12) << "f(d)"<< endl;
            } else if (opcao1 == 2) {
                cout << "Metodo Newton FL; Entrada N";
                //N
                cout << "N: ";
                cin >> N1;
                //e
                cout << "e: ";
                cin >> e1;

                // cout << setw(3) << "k" << " | " << setw(12) << "d" << " | " << setw(12) << "f(d)"<< endl;
                for (int i = 0; i < N1; i++) {
                //lambda
                cout << "lambda: "; cin >> lambda1;
                //a2
                cout << "a2: "; cin >> a21;
                //a3
                cout << "a3: "; cin >> a31;
                // **************  OBS.: O mesmo problema da linha 82 **********
                newton_itemB(a31, a21, 0.5, lambda1, e1);
                }
                this_thread::sleep_for(chrono::seconds(2));
                
            }
        } else if (opcao == 3) {
            cout << "Programa Finalizado" << endl;
            exit(0);
        }
        else {
            cout << "Escolha inválida. Tente novamente.\n";
        }
    }
} 
//Func p pegar as N entradas quando o metodo selecionado for o newton padrao
void EnterNewtonPadrao(int N, double e, double a2, double a3, double lambda){
    //N
    cout << "N: ";
    cin >> N;
    //e
    cout << "e: ";
    cin >> e;

    //N a2, a3 e lambda
    for (int i = 0; i < N; i++) {
        //lambda
        cout << "lambda: "; cin >> lambda;
        //a2
        cout << "a2: "; cin >> a2;
        //a3
        cout << "a3: "; cin >> a3;
        
        //Codigo do metodo selecionado para lambda, a2 e a3 da interação (Newton Padrao)(codigo do item A)
        }
};

//Func pra pegar as entradas quando o metodos selecionado for o newton FL
void EnterNewtonFL(int N, double e, double a2, double a3, double lambda){
    //N
    cout << "N: ";
    cin >> N;
    //e
    cout << "e: ";
    cin >> e;

    //N a2, a3 e lambda
    for (int i = 0; i < N; i++) {
        //lambda
        cout << "lambda: "; cin >> lambda;
        //a2
        cout << "a2: "; cin >> a2;
        //a3
        cout << "a3: "; cin >> a3;
        
        //Codigo do metodo selecionado para lambda, a2 e a3 da interação (FL)(Codigo do item B)
        }
};

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
    
    cout << "Erro! f'(d0) < lambda " << endl;
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
    while(abs(funcao_d(d0, a3, a2)) >= epsilon || abs(d1-d0) >= epsilon){
        d0 = d1;
        d1 = d0 - (funcao_d(d0, a3, a2)/derivada_diferenca_finita(d0, a3, a2, funcao_d, h));
    }

    return d1;

}


// MUDAR MENU
int main(){
    menu();
    return 0;
}
