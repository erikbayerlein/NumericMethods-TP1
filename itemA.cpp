#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

double newton_rapshon(double a3, double a2, double d0, double lambda, double epsilon);
double derivada_f(double d, double a3, double a2);
double funcao_d(double d, double a3, double a2); 
double newton_B(double a3, double a2, double d0, double lambda, double epsilon);

int main(){

    double raiz = newton_itemB(1, 1, 1.5, 0.05, 0.001);
    cout << raiz << endl;

}

double newton_itemA(double a3, double a2, double d0, double lambda, double epsilon){
    if (abs(funcao_d(d0, a3, a2)) < epsilon){
        return d0;
    }
    

    double d1 = d0 - (funcao_d(d0, a3, a2)/derivada_f(d0, a3, a2));    
    while(abs(funcao_d(d0, a3, a2) >= epsilon || abs(d1-d0) >= epsilon)){    
        d0 = d1; 
        d1 = d0 - (funcao_d(d0, a3, a2)/derivada_f(d0, a3, a2));
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
        while(abs(funcao_d(d0, a3, a2) >= epsilon || abs(d1-d0) >= epsilon)){    
            d0 = d1;
            cout << derivada << endl;
        
            if (derivada_f(d0, a3, a2) <= lambda){
                d1 = d0 - (funcao_d(d0, a3, a2)/derivada);
            } else {
                derivada = derivada_f(d0, a3, a2);
                d1 = d0 - (funcao_d(d0, a3, a2)/derivada);
            }
            
        }

        return d1;
    }
    
    cout << "nao deu bom" << endl;
    return 0.0;


}