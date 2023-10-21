#include <iostream>

using namespace std;

void EnterNewtonPadrao(int N, double e, double a2, double a3, double lambda);
void EnterNewtonFL(int N, double e, double a2, double a3, double lambda);

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
                cout << "Metodo Newton padrao; Entrada padrao";
                //codigo do item A entrada padrao
            }
            else if (opcao1 == 2) {
                cout << "Metodo Newton FL; Entrada padrao";
                //Codigo do item B entrada padrao
            }
            return;
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
                cout << "Metodo Newton padrao; Entrada N:";
                EnterNewtonPadrao(N1, e1, a21, a31, lambda1);
            }
            else if (opcao1 == 2) {
                cout << "Metodo Newton FL; Entrada N";
                EnterNewtonFL(N1, e1, a21, a31, lambda1);
            }
            return;
        }
        else if (opcao == 3) {
            cout << "Programa Finalizado";
            return;
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

// MUDAR MENU
int main(){
    menu();
    return 0;
}
