#include <iostream>
#include <locale.h>
#include <math.h>
using namespace std;
double volumen = 0, radio = 0, largo = 0, material = 0, mat_anterior;

int
main() {
    setlocale(LC_ALL, "spanish");
    cout << "Favor ingrese el volumen del tanque (mts3)= ";
    cin >> volumen;

    // inicializar variable a recorrer (r)
    radio = 0.01;
    // ecuacion del maximo despejada con respecto a r
    material = 4 * M_PI * pow(radio, 2) / 3 + 2 * volumen / radio;
    // ciclo para encontrar el mínimo de material
    mat_anterior = material;
    while (mat_anterior >= material) {
        mat_anterior = material;
        radio = radio + 0.0000001;
        material = 4 * M_PI * pow(radio, 2) / 3 + 2 * volumen / radio;
    }

    cout << endl
         << endl
         << "El radio donde se obtiene un tanque de volumen= " << volumen
         << " mt3 con el mínimo material corresponde a =" << radio << " mts";
    cout << endl
         << "El largo para obtener obtener ese tanque es de = " << largo
         << " mts";
    cout << endl
         << "La cantidad de material requerido (mínimo) corresponde a ="
         << material << " mts2";

    return 0;
}