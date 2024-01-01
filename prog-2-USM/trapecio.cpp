#include <iostream>
#include <locale.h>
#include <math.h>

double ancho;
double base1, base2, x;
double h;
double area_rec, area_trap, area_tapa;
double Q, Q_rad;
double volumen;
double funcion_optimizada = 100;
using namespace std;

main()

{
    setlocale(LC_ALL, "spanish");   // seteamos el lenguaje en español

    cout << "Ingrese el ancho de la lámina.  (1.5 a 2.5 mts) = ";
    cin >> ancho;
    cin.ignore();

    /*Elaboramos un ciclo que determine el ángulo donde la ecuación de
    optimización se hace cero en el rango de 0.001 a 90 grados*/

    while (funcion_optimizada < -0.001 or funcion_optimizada > 0.001) {
        Q = Q + 0.001;
        Q_rad = Q * M_PI / 180;
        funcion_optimizada = cos(Q_rad) + pow(cos(Q_rad), 2) -
                             pow(sin(Q_rad), 2) - 2 * sin(Q_rad);
    }

    base1 = ancho / 5;
    x = ancho / 5 * cos(Q_rad);
    base2 = base1 + 2 * x;
    h = ancho / 5 * sin(Q_rad);

    area_trap = (base1 + base2) * h / 2;
    area_rec = (ancho / 5 + 2 * x) * ancho / 5;
    area_tapa = area_rec + area_trap;

    volumen = area_tapa * 3;

    cout << "El angulo es = " << Q << endl;
    cout << "El volumen total es = " << volumen << endl;
}