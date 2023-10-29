#include <iostream>
#include <iomanip> 
#include <cmath>
#include <thread>
#include <chrono>
#include "itensA_B_C.h"

using namespace std;

/**Observações:
 * compilação:
 * g++ -o <nome_do_executavel> menu.cpp itensA_B_C.cpp
 * 
 * executar ./<nome_do_executavel>
 * 
*/

void menu() {
    cout << fixed << setprecision(8);
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
        cout << "1: Testar resultado com entrada padrao a3 = 1, a2 = 1, d0 = 0,5, lambda = 0,05, e = 0,001\n";
        cout << "2: Testar resultado com N entradas diferentes para Lambda, a2 e a3 e uma precisao 'e' especifica\n";
        cout << "3: Encerrar Programa\n\n";

        int opcao;
        cout << "Opcao:"; cin >> opcao;

        if (opcao == 1) {
            cout << "\nEntrada padrao a3 = 1, a2 = 1, d0 = 0,5, lambda = 0,05, e = 0,001 selecionada.\n";
            cout << "Selecione o Metodo:\n\n";
            cout << "1: Metodo Newton Padrao\n";
            cout << "2: Metodo Newton FL\n";
            cout << "3: Metodo Newton Padrao - Derivada pelo metodo da diferenca finita\n\n";
            int opcao1;
            cout << "Opcao:"; cin >> opcao1;

            //definindo entradas padrao
            double a2 = 1, a3 = 1, d0 = 0.5, e = 0.001, lambda = 0.05;
            //SubMenu
            if (opcao1 == 1) {
                cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
                cout << "#" << setw(26) << " " << "Metodo Newton padrao - Entrada padrao" << setw(26) << " " << "#" <<endl;
                
                //codigo do item A entrada padrao
                // newton_itemA( a3,  a2,  d0,  epsilon);
                newton_itemA(1, 1, 0.5, 0.001);
                this_thread::sleep_for(chrono::seconds(2));
                    
            }
            else if (opcao1 == 2) {
                cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
                cout << "#" << setw(28) << " " << "Metodo Newton FL - Entrada padrao" << setw(28) << " " << "#" <<endl;

                //Codigo do item B entrada padrao
                // newton_itemB( a3,  a2,  d0, lambda, epsilon);
                newton_itemB_entrada_padrao(1, 1, 0.5, 0.05, 0.001);
                this_thread::sleep_for(chrono::seconds(2));
            }
            else if (opcao1 == 3){
                cout << setfill('-') << setw(91) << "-" << setfill(' ') << endl;
                cout << "#" << setw(5) << " " << "Metodo Newton padrao - Derivada pelo metodo da Diferenca finita - Entrada padrao" << setw(4) << " " << "#" <<endl;
                newton_itemC(1, 1, 0.5, 0.001, 0.00001);
                this_thread::sleep_for(chrono::seconds(2));
            }
            
        }
        else if (opcao == 2) {
            cout << "N entradas diferentes para Lambda, a2 e a3 e uma precisao 'e' especifica\n\n";
            cout << "Selecione o Metodo:\n\n";
            cout << "1: Metodo Newton Padrao\n";
            cout << "2: Metodo Newton FL\n";
            cout << "3: Metodo Newton Padrao - Derivada pelo metodo da diferenca finita\n\n";

            int opcao1;
            cout << "Opcao: "; cin >> opcao1;

            int N1;
            double e1, a21, a31, lambda1;
            //SubMenu
            if (opcao1 == 1) {
                cout << "Metodo Newton padrao selecionado. Informe o numero (N) de opcoes:\n" << endl;
                cout << "N: "; cin >> N1;
                cout << "e: "; cin >> e1;

                for (int i = 0; i < N1; i++){
                    cout << "Valores para a opcao " << i+1 << ":" <<endl;
                    //a2
                    cout << "a2: " << endl; cin >> a21;
                    //a3
                    cout << "a3: " << endl; cin >> a31;
                    newton_itemA2_raphson(a31, a21, e1);
                }
                this_thread::sleep_for(chrono::seconds(2));
                //cout << setw(3) << "k" << " | " << setw(12) << "d" << " | " << setw(12) << "f(d)"<< endl;
            } else if (opcao1 == 2) {
                cout << "Metodo Newton FL selecionado. Informe o numero (N) de opcoes:\n" << endl;
                //N
                cout << "N: ";cin >> N1;
                //e
                cout << "e: ";cin >> e1;

                for (int i = 0; i < N1; i++) {
                    cout << "Valores para a opcao " << i+1 << ":" <<endl;
                    //lambda
                    cout << "lambda: "; cin >> lambda1;
                    //a2
                    cout << "a2: "; cin >> a21;
                    //a3
                    cout << "a3: "; cin >> a31;
                    newton_itemB(a31, a21, lambda1, e1);
                }
                this_thread::sleep_for(chrono::seconds(2));
            } else if (opcao1 == 3) {
                cout << "Metodo Newton padrao selecionado. Informe o numero (N) de opcoes.\n" << endl;
                cout << "N: "; cin >> N1;
                cout << "e: "; cin >> e1;

                for (int i = 0; i < N1; i++){
                    cout << "Valores para a opcao " << i+1 << ":" <<endl;
                    //a2
                    cout << "a2: " << endl; cin >> a21;
                    //a3
                    cout << "a3: " << endl; cin >> a31;

                    newton_itemC(a31, a21, 0.5, e1, 0.00001);
                }
                this_thread::sleep_for(chrono::seconds(2));
            }

            else {
                cout << "Escolha invalida. Tente novamente.\n";
            }

        } else if (opcao == 3) {
            cout << "Programa Finalizado" << endl;
            exit(0);
        }
        else {
            cout << "Escolha invalida. Tente novamente.\n";
        }

    }
}

// MUDAR MENU
int main(){
    menu();
    return 0;
}
