/*
Programa que simula el funcionamiento de 3 bombas de etileno, tomando como inputs el tiempo de rotacion
y estado de las valvulas para conseguir el estado de las bombas, la presion de las mismas y
la cantidad de galones de etileno enviados

Autores:
> Gustavo Alviarez 	- 28.484.121
> Luis Hernández 	- 29.642.345
> Guillermo Navarro - 30.330.371

Rev. 0

*/
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <conio.h> 

using namespace std;

HANDLE output_handle = GetStdHandle(STD_OUTPUT_HANDLE);

string estado_bomba_01 = "APAGADO";
string estado_bomba_02 = "APAGADO";
string estado_bomba_03 = "APAGADO";

string estado_switch_01 = "NORMAL";
string estado_switch_02 = "NORMAL";
string estado_switch_03 = "NORMAL";

// pointers para cada estado switch
string *p_estado_switch_01 = &estado_switch_01;
string *p_estado_switch_02 = &estado_switch_02;
string *p_estado_switch_03 = &estado_switch_03;

// pointers para cada estado bomba
string *p_estado_bomba_01 = &estado_bomba_01;
string *p_estado_bomba_02 = &estado_bomba_02;
string *p_estado_bomba_03 = &estado_bomba_03;

int presion_bomba_01 = 0;
int presion_bomba_02 = 0;
int presion_bomba_03 = 0;

// pointers para cada presion bomba
int *p_presion_bomba_01 = &presion_bomba_01;
int *p_presion_bomba_02 = &presion_bomba_02;
int *p_presion_bomba_03 = &presion_bomba_03;

int tiempo_bomba_01 = 0;
int tiempo_bomba_02 = 0;
int tiempo_bomba_03 = 0;

// pointers para cada tiempo bomba
int *p_tiempo_bomba_01 = &tiempo_bomba_01;
int *p_tiempo_bomba_02 = &tiempo_bomba_02;
int *p_tiempo_bomba_03 = &tiempo_bomba_03;

int tiempo_de_rotacion;
int prioridad_de_rotacion = 1;

double galones_totales = 0.0000;

// variables para extraer datos del txt
string columnas[7];
string linea;

string cambiar_a_mayuscula(string texto)
{
    for (int i = 0; i < texto.length(); i++)
    {
        texto[i] = toupper(texto[i]);
    }
    return texto;
}

void simular_bomba(string *p_estado_bomba, string estado_v1, string estado_v2, int tiempo_de_rotacion, int *p_tiempo_bomba, int *p_presion, double *p_galones_por_segundo, string *p_estado_switch)
{
    *p_estado_switch = "NORMAL";
    if (*p_estado_bomba == "ENCENDIDO" or *p_estado_bomba == "APAGADO")
    {
        if (estado_v1 == "ABIERTO" && estado_v2 == "ABIERTO")
        {
            if (*p_estado_bomba == "ENCENDIDO")
            {
                if (*p_presion >= 20)
                {
                    *p_tiempo_bomba += 1;
                    *p_galones_por_segundo += 0.6666;
                }
                if (*p_presion > 33)
                {
                    *p_presion -= 1;
                }
                if (*p_presion < 33)
                {
                    *p_presion += 1;
                }
            }
            if (*p_estado_bomba == "APAGADO" && *p_presion < 20)
            {
                if (*p_presion < 20)
                {
                    *p_tiempo_bomba = 0;
                    *p_presion += 1;
                }
                if (*p_presion >= 20)
                {
                    *p_tiempo_bomba = 0;
                    *p_estado_bomba = "ENCENDIDO";
                }
            }
        }

        if (estado_v1 == "ABIERTO" && estado_v2 == "CERRADO")
        {
            if (*p_presion < 50)
            {
                *p_presion += 1;
                *p_tiempo_bomba += 1;
            }
            else
            {
                *p_estado_bomba = "APAGADO";
            }
        }

        if (estado_v1 == "CERRADO" && estado_v2 == "ABIERTO")
        {
            if (*p_presion > 0)
            {
                *p_presion -= 1;
                *p_tiempo_bomba += 1;
            }
            else
            {

                *p_estado_bomba = "APAGADO";
            }
            *p_estado_switch = "ALARMA";
        }

        if (estado_v1 == "CERRADO" && estado_v2 == "CERRADO" && *p_estado_bomba == "ENCENDIDO")
        {
            if (*p_presion <= 0)
            {
                *p_estado_bomba = "APAGADO";
            }
        }
    }

    if (*p_estado_bomba == "APAGADO_POR_TIEMPO")
    {
        if (*p_tiempo_bomba >= tiempo_de_rotacion - 1)
        {
            if (estado_v1 == "ABIERTO" && estado_v2 == "ABIERTO")
            {
                *p_estado_bomba = "ENCENDIDO";
            }
            else
            {
                *p_estado_bomba = "APAGADO";
            }
        }
        else
        {
            *p_tiempo_bomba += 1;
        }
    }
}

int main()

{
    cout << endl
         << "	--- PROGRAMA DE SIMULACION Y CONTROL DE PLASTIGALOS.INC ---" << endl
         << endl
         << endl;

    cout << "> Planos:" << endl;

    {
        char T1 = 186, T2 = 205, T3 = 204, T4 = 187, T5 = 188, T6 = 208, T7 = 210, F1 = 175, F2 = 174;

        cout << "		" << T1 << endl
             << "		" << T1 << endl
             << "		" << T3 << T2 << T2 << T2 << T2 << "(o)" << T2 << T2 << T2 << "[B" << F1 << "]" << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T4 << endl;
        cout << "		" << T3 << T2 << T2 << T2 << T2 << "(o)" << T2 << T2 << T2 << "[B" << F1 << "]" << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T4 << T1 << endl;
        cout << "		" << T3 << T2 << T2 << T2 << T2 << "(o)" << T2 << T2 << T2 << "[B" << F1 << "]" << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T4 << T1 << T1 << endl;
        cout << "		" << T6 << "			 " << T1 << T1 << T1 << endl
             << "		"
             << "			 " << T1 << T1 << T1 << endl
             << "		"
             << "			 " << T1 << T1 << T1 << endl
             << "		"
             << "    " << T7 << "			 " << T1 << T1 << T1 << endl;
        cout << "		"
             << "    " << T3 << T2 << T2 << T2 << T2 << "(o)" << T2 << T2 << T2 << "[" << F2 << "P]" << T2 << T2 << T2 << T2 << T2 << T2 << T5 << T1 << T1 << endl;
        cout << "		"
             << "    " << T3 << T2 << T2 << T2 << T2 << "(o)" << T2 << T2 << T2 << "[" << F2 << "P]" << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T5 << T1 << endl;
        cout << "		"
             << "    " << T3 << T2 << T2 << T2 << T2 << "(o)" << T2 << T2 << T2 << "[" << F2 << "P]" << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T5;
        cout << "		" << endl
             << " 	 	    " << T1 << endl
             << "   	  	    " << T1 << endl
             << "  		    " << T1 << endl
             << endl;
    }
    cout << "> Por favor abrir el archivo de control" << endl
         << endl;

    system("pause");
    system("cls");
// ---------------------- Inicio del programa ---------------------- //
inicio:

    ifstream archivo("parcial3.txt");

    if (archivo.fail() == true)
    {
        cout << "El archivo no pudo abrirse, por favor comprobar la direccion" << endl
             << endl;
        return (0);
    }

    // recorre las 7 lineas del txt y extrae los estados de las bombas y el tiempo de rotacion
    for (int i = 0; i < 7; i++)
    {
        archivo >> linea >> columnas[i];
        if (i == 6)
        {
            archivo >> linea >> linea >> tiempo_de_rotacion;
        }
    }

    string v101_estado = cambiar_a_mayuscula(columnas[0]);
    string v201_estado = cambiar_a_mayuscula(columnas[1]);
    string v102_estado = cambiar_a_mayuscula(columnas[2]);
    string v202_estado = cambiar_a_mayuscula(columnas[3]);
    string v103_estado = cambiar_a_mayuscula(columnas[4]);
    string v203_estado = cambiar_a_mayuscula(columnas[5]);

    double galones_por_segundo = 0.0000;
    double *p_galones_por_segundo = &galones_por_segundo;

    simular_bomba(p_estado_bomba_01, v101_estado, v201_estado, tiempo_de_rotacion, p_tiempo_bomba_01, p_presion_bomba_01, p_galones_por_segundo, p_estado_switch_01);
    simular_bomba(p_estado_bomba_02, v102_estado, v202_estado, tiempo_de_rotacion, p_tiempo_bomba_02, p_presion_bomba_02, p_galones_por_segundo, p_estado_switch_02);
    simular_bomba(p_estado_bomba_03, v103_estado, v203_estado, tiempo_de_rotacion, p_tiempo_bomba_03, p_presion_bomba_03, p_galones_por_segundo, p_estado_switch_03);

    galones_totales += galones_por_segundo;

    if (prioridad_de_rotacion == 1)
    {
        if (tiempo_bomba_01 >= tiempo_de_rotacion && estado_bomba_01 == "ENCENDIDO")
        {
            if (estado_bomba_02 == "APAGADO" && estado_bomba_03 == "APAGADO")
            {
                if (v101_estado == "ABIERTO" && v201_estado == "ABIERTO")
                {
                    estado_bomba_01 = "ENCENDIDO";
                }
                else
                {
                    estado_bomba_01 = "APAGADO";
                }
            }
            else
            {
                estado_bomba_01 = "APAGADO_POR_TIEMPO";
            }
            tiempo_bomba_01 = 0;
            tiempo_bomba_02 = 0;
            tiempo_bomba_03 = 0;
            prioridad_de_rotacion += 1;
        }

        if (tiempo_bomba_02 >= tiempo_de_rotacion && estado_bomba_02 == "ENCENDIDO")
        {
            if (estado_bomba_01 == "APAGADO" && estado_bomba_03 == "APAGADO")
            {
                if (v102_estado == "ABIERTO" && v202_estado == "ABIERTO")
                {
                    estado_bomba_02 = "ENCENDIDO";
                }
                else
                {
                    estado_bomba_02 = "APAGADO";
                }
            }
            else
            {
                estado_bomba_02 = "APAGADO_POR_TIEMPO";
            }
            tiempo_bomba_01 = 0;
            tiempo_bomba_02 = 0;
            tiempo_bomba_03 = 0;
            prioridad_de_rotacion += 1;
        }

        if (tiempo_bomba_03 >= tiempo_de_rotacion && estado_bomba_03 == "ENCENDIDO")
        {
            if (estado_bomba_01 == "APAGADO" && estado_bomba_02 == "APAGADO")
            {
                if (v103_estado == "ABIERTO" && v203_estado == "ABIERTO")
                {
                    estado_bomba_03 = "ENCENDIDO";
                }
                else
                {
                    estado_bomba_03 = "APAGADO";
                }
            }
            else
            {
                estado_bomba_03 = "APAGADO_POR_TIEMPO";
            }
            tiempo_bomba_01 = 0;
            tiempo_bomba_02 = 0;
            tiempo_bomba_03 = 0;
            prioridad_de_rotacion += 1;
        }
    }

    if (prioridad_de_rotacion == 2)
    {

        if (tiempo_bomba_02 >= tiempo_de_rotacion && estado_bomba_02 == "ENCENDIDO")
        {
            if (estado_bomba_01 == "APAGADO" && estado_bomba_03 == "APAGADO")
            {
                if (v102_estado == "ABIERTO" && v202_estado == "ABIERTO")
                {
                    estado_bomba_02 = "ENCENDIDO";
                }
                else
                {
                    estado_bomba_02 = "APAGADO";
                }
            }
            else
            {
                estado_bomba_02 = "APAGADO_POR_TIEMPO";
            }
            tiempo_bomba_01 = 0;
            tiempo_bomba_02 = 0;
            tiempo_bomba_03 = 0;
            prioridad_de_rotacion += 1;
        }

        if (tiempo_bomba_03 >= tiempo_de_rotacion && estado_bomba_03 == "ENCENDIDO")
        {
            if (estado_bomba_01 == "APAGADO" && estado_bomba_02 == "APAGADO")
            {
                if (v103_estado == "ABIERTO" && v203_estado == "ABIERTO")
                {
                    estado_bomba_03 = "ENCENDIDO";
                }
                else
                {
                    estado_bomba_03 = "APAGADO";
                }
            }
            else
            {
                estado_bomba_03 = "APAGADO_POR_TIEMPO";
            }
            tiempo_bomba_01 = 0;
            tiempo_bomba_02 = 0;
            tiempo_bomba_03 = 0;
            prioridad_de_rotacion += 1;
        }

        if (tiempo_bomba_02 >= tiempo_de_rotacion && estado_bomba_02 == "ENCENDIDO")
        {
            if (estado_bomba_01 == "APAGADO" && estado_bomba_03 == "APAGADO")
            {
                if (v102_estado == "ABIERTO" && v202_estado == "ABIERTO")
                {
                    estado_bomba_02 = "ENCENDIDO";
                }
                else
                {
                    estado_bomba_02 = "APAGADO";
                }
            }
            else
            {
                estado_bomba_02 = "APAGADO_POR_TIEMPO";
            }
            tiempo_bomba_01 = 0;
            tiempo_bomba_02 = 0;
            tiempo_bomba_03 = 0;
            prioridad_de_rotacion += 1;
        }

        if (tiempo_bomba_01 >= tiempo_de_rotacion && estado_bomba_01 == "ENCENDIDO")
        {
            if (estado_bomba_02 == "APAGADO" && estado_bomba_03 == "APAGADO")
            {
                if (v101_estado == "ABIERTO" && v201_estado == "ABIERTO")
                {
                    estado_bomba_01 = "ENCENDIDO";
                }
                else
                {
                    estado_bomba_01 = "APAGADO";
                }
            }
            else
            {
                estado_bomba_01 = "APAGADO_POR_TIEMPO";
            }
            tiempo_bomba_01 = 0;
            tiempo_bomba_02 = 0;
            tiempo_bomba_03 = 0;
            prioridad_de_rotacion += 1;
        }
    }

    if (prioridad_de_rotacion == 3)
    {

        if (tiempo_bomba_03 >= tiempo_de_rotacion && estado_bomba_03 == "ENCENDIDO")
        {
            if (estado_bomba_01 == "APAGADO" && estado_bomba_02 == "APAGADO")
            {
                if (v103_estado == "ABIERTO" && v203_estado == "ABIERTO")
                {
                    estado_bomba_03 = "ENCENDIDO";
                }
                else
                {
                    estado_bomba_03 = "APAGADO";
                }
            }
            else
            {
                estado_bomba_03 = "APAGADO_POR_TIEMPO";
            }
            tiempo_bomba_01 = 0;
            tiempo_bomba_02 = 0;
            tiempo_bomba_03 = 0;
            prioridad_de_rotacion -= 2;
        }

        if (tiempo_bomba_02 >= tiempo_de_rotacion && estado_bomba_02 == "ENCENDIDO")
        {
            if (estado_bomba_01 == "APAGADO" && estado_bomba_03 == "APAGADO")
            {
                if (v102_estado == "ABIERTO" && v202_estado == "ABIERTO")
                {
                    estado_bomba_02 = "ENCENDIDO";
                }
                else
                {
                    estado_bomba_02 = "APAGADO";
                }
            }
            else
            {
                estado_bomba_02 = "APAGADO_POR_TIEMPO";
            }
            tiempo_bomba_01 = 0;
            tiempo_bomba_02 = 0;
            tiempo_bomba_03 = 0;
            prioridad_de_rotacion -= 2;
        }

        if (tiempo_bomba_01 >= tiempo_de_rotacion && estado_bomba_01 == "ENCENDIDO")
        {
            if (estado_bomba_02 == "APAGADO" && estado_bomba_03 == "APAGADO")
            {
                if (v101_estado == "ABIERTO" && v201_estado == "ABIERTO")
                {
                    estado_bomba_01 = "ENCENDIDO";
                }
                else
                {
                    estado_bomba_01 = "APAGADO";
                }
            }
            else
            {
                estado_bomba_01 = "APAGADO_POR_TIEMPO";
            }
            tiempo_bomba_01 = 0;
            tiempo_bomba_02 = 0;
            tiempo_bomba_03 = 0;
            prioridad_de_rotacion -= 2;
        }
    }

    // pantalla que muestra los estados

    system("cls");

    int switchscreen;
    if (kbhit() != 0)
    {
        switchscreen = getch();
    }
    if (switchscreen != 's')
    {

        // mostramos los estados de las bombas, si esta "ENCENDIDO" o "APAGADO" y los tiempos de cada bomba y el de rotacion

        // BOMBA 01
        cout << endl
             << "BOMBA 01" << endl;
        cout << endl
             << "Estado: " << *p_estado_bomba_01;
        cout << endl
             << "Estado switch de flujo: " << *p_estado_switch_01;
        cout << endl
             << "Tiempo de trabajo: ";
        *p_estado_bomba_01 == "APAGADO_POR_TIEMPO" ? cout << "0" : cout << tiempo_bomba_01;
        cout << endl
             << "Presion: " << presion_bomba_01;

        // BOMBA 02
        cout << endl
             << endl
             << "BOMBA 02" << endl;
        cout << endl
             << "Estado: " << *p_estado_bomba_02;
        cout << endl
             << "Estado switch de flujo: " << *p_estado_switch_02;
        cout << endl
             << "Tiempo de trabajo: ";
        *p_estado_bomba_02 == "APAGADO_POR_TIEMPO" ? cout << "0" : cout << tiempo_bomba_02;
        cout << endl
             << "Presion: " << presion_bomba_02;

        // BOMBA 03
        cout << endl
             << endl
             << "BOMBA 03" << endl;
        cout << endl
             << "Estado: " << *p_estado_bomba_03;
        cout << endl
             << "Estado switch de flujo: " << *p_estado_switch_03;
        cout << endl
             << "Tiempo de trabajo: ";
        *p_estado_bomba_03 == "APAGADO_POR_TIEMPO" ? cout << "0" : cout << tiempo_bomba_03;
        cout << endl
             << "Presion: " << presion_bomba_03 << endl;
        cout << endl
             << "Tiempo de rotacion (segundos): " << tiempo_de_rotacion;
        cout << endl
             << endl
             << "galones enviados por segundo: " << galones_por_segundo;
        cout << endl
             << "galones totales: " << galones_totales;

        // Todo lo que hay a continuacion es la pantalla alterna del grafico, capaz se puede hacer mas corto pero no se 	att:Guillermo XD

        cout << endl
             << endl
             << "Presionar 'S' para cambiar de modo" << endl;
    }

    // Pantalla que muestra el diagrama
    else if (switchscreen == 's' or switchscreen == 'S')
    {
        char T1 = 186, T2 = 205, T3 = 204, T4 = 187, T5 = 188, T6 = 208, T7 = 210, F1 = 175, F2 = 174; // lo declare de nuevo pero es que aun me da miedo tocar tus vainas, si quieres ordenalo como gustes att:Guillermo XD

        cout << "> Planos graficos a tiempo real:" << endl
             << endl;

        cout << "		" << T1 << endl
             << "		" << T1 << endl
             << "		" << T3 << T2 << T2 << T2 << T2;

        if (v101_estado == "ABIERTO")
        {
            cout << "(o)";
        }
        else if (v101_estado == "CERRADO")
        {
            cout << "(X)";
        }

        cout << T2 << T2 << T2 << "[B" << F1 << "]" << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T4 << endl;
        cout << "		" << T3 << T2 << T2 << T2 << T2;

        if (v102_estado == "ABIERTO")
        {
            cout << "(o)";
        }
        else if (v102_estado == "CERRADO")
        {
            cout << "(X)";
        }

        cout << T2 << T2 << T2 << "[B" << F1 << "]" << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T4 << T1 << endl;
        cout << "		" << T3 << T2 << T2 << T2 << T2;

        if (v103_estado == "ABIERTO")
        {
            cout << "(o)";
        }
        else if (v103_estado == "CERRADO")
        {
            cout << "(X)";
        }

        cout << T2 << T2 << T2 << "[B" << F1 << "]" << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T4 << T1 << T1 << endl;
        cout << "		" << T6 << "			 " << T1 << T1 << T1 << endl
             << "		"
             << "			 " << T1 << T1 << T1 << endl
             << "		"
             << "			 " << T1 << T1 << T1 << endl
             << "		"
             << "    " << T7 << "			 " << T1 << T1 << T1 << endl;
        cout << "		"
             << "    " << T3 << T2 << T2 << T2 << T2;

        if (v201_estado == "ABIERTO")
        {
            cout << "(o)";
        }
        else if (v201_estado == "CERRADO")
        {
            cout << "(X)";
        }

        cout << T2 << T2 << T2 << "[" << F2 << "P]" << T2 << T2 << T2 << T2 << T2 << T2 << T5 << T1 << T1 << endl;
        cout << "		"
             << "    " << T3 << T2 << T2 << T2 << T2;

        if (v202_estado == "ABIERTO")
        {
            cout << "(o)";
        }
        else if (v202_estado == "CERRADO")
        {
            cout << "(X)";
        }

        cout << T2 << T2 << T2 << "[" << F2 << "P]" << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T5 << T1 << endl;
        cout << "		"
             << "    " << T3 << T2 << T2 << T2 << T2;

        if (v203_estado == "ABIERTO")
        {
            cout << "(o)";
        }
        else if (v203_estado == "CERRADO")
        {
            cout << "(X)";
        }

        cout << T2 << T2 << T2 << "[" << F2 << "P]" << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T2 << T5;
        cout << "		" << endl
             << " 	 	    " << T1 << endl
             << "   	  	    " << T1 << endl
             << "  		    " << T1 << endl
             << endl;

        cout << "Presionar cualquier tecla para cambiar de modo" << endl;
    }

    Sleep(900);

    goto inicio;
}
