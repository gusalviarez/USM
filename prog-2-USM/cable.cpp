#include <iostream>
#include <math.h>
using namespace std;

int
main() {
    double CM = 0, CT = 0;
    double X, X_aux;
    double BD, BD_aux;
    double Costo, Costo_aux;

    cout << "Ingrese el costo en ($) del tendido de (KM) de Cable maritimo = ";
    cin >> CM;
    cin.ignore();

    cout << "Ingrese el costo en ($) del tendido de (KM) de Cable terrestre ";
    cin >> CT;
    cin.ignore();
	
    X = 0;
    BD = sqrt(pow(20, 2) + pow(14, 2));
    Costo = CT * X + CM * BD;

    X_aux = 0.01;
    while (X_aux < 20) {
        BD_aux = sqrt(pow(20 - X_aux, 2) + pow(14, 2));
        Costo_aux = CT * X_aux + CM * BD_aux;
        if (Costo_aux < Costo) {
            Costo = Costo_aux;
            X = X_aux;
            BD = BD_aux;
        }
        X_aux = X_aux + 0.01;
    }

    Costo_aux = CT * 20 + CM * 14;
    if (Costo_aux < Costo) {
        Costo = Costo_aux;
        X = 20;
        BD = 14;
    }

    cout << endl
         << "La cantidad de cable Marítimo requerido es (KM) =" << BD << endl;
    cout << "La cantidad de cable Terrestre requerido es (KM) = " << X << endl;
    cout << "El Costo del tendido es = " << Costo << " $" << endl;

    return 0;
}