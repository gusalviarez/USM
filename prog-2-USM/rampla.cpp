// Programa para el calculo de la longitud L de la rampa para utilizar un MINIMO
// de Material - Según enunciado y grafica (USM Prog II) Elaborado por el
// profesor Carlos Ferrer - Rev Sep 2023

// Librerias requeridas

#include <iostream>
#include <math.h>

using namespace std;
int
main()

{
    double l = 0, x = 0, y = 0, Q = 0, Q1 = 0, b, pi = 3.141592654;

    cout << "introduzca la longitud de la base de apoyo (mts): ";
    cin >> b;

    Q = atan(cbrt(b));
    l = (b + tan(Q)) / sin(Q);
    x = l * cos(Q);
    y = l * sin(Q);

    Q1 = (Q * 180) / pi;

    cout << endl
         << "Longitud de la rampa con minima utilización de material (mts):"
         << l << endl;
    cout << "Altura de la construcción en donde se apoyara la rampa (mts):" << y
         << endl;
    cout << "Distancia desde la construcción hasta el punto en donde se "
            "apoyara la rampa en el suelo (mts): "
         << x << endl;
    cout << "El angulo de elevación de la rampa es: " << Q << " Rad o " << Q1
         << " Deg" << endl
         << endl;

    system("pause");
}