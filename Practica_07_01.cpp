#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct structEquiposLPFB
{
    char nombreEquipo[50];
    char colorCamiseta[50];
    char departamento[30];
    int anioCreacion;
};

struct structResultadosLPFB
{
    char nombreEquipoLocal[50];
    char nombreEquipoVisitante[50];
    int golesEquipoLocal;
    int golesEquipoVisitante;
    char fechaPartido[10];
};

void ingresarEquipos()
{
    ofstream archivoEquipos("EquiposLPFB.bin", ios::binary | ios::app);

    structEquiposLPFB equipo;

    cout << "Ingrese el nombre del equipo: ";
    cin.ignore();
    cin.getline(equipo.nombreEquipo, 50);

    // Verificar si el equipo ya existe
    ifstream verificarEquipos("EquiposLPFB.bin", ios::binary);
    bool equipoExistente = false;
    while (verificarEquipos.read(reinterpret_cast<char*>(&equipo), sizeof(structEquiposLPFB)))
    {
        if (strcmp(equipo.nombreEquipo, equipo.nombreEquipo) == 0)
        {
            equipoExistente = true;
            break;
        }
    }
    verificarEquipos.close();

    if (equipoExistente)
    {
        cout << "¡Error! El equipo ya existe." << endl;
        return;
    }

    cout << "Ingrese el color de la camiseta: ";
    cin.getline(equipo.colorCamiseta, 50);

    cout << "Ingrese el departamento: ";
    cin.getline(equipo.departamento, 30);

    cout << "Ingrese el año de creacion: ";
    cin >> equipo.anioCreacion;

    archivoEquipos.write(reinterpret_cast<const char*>(&equipo), sizeof(structEquiposLPFB));

    cout << "Equipo ingresado correctamente." << endl;

    archivoEquipos.close();
}

void ingresarResultados()
{
    ifstream archivoEquipos("EquiposLPFB.bin", ios::binary);

    if (!archivoEquipos)
    {
        cout << "¡Error! Primero debe ingresar los equipos." << endl;
        return;
    }

    ofstream archivoResultados("ResultadosLPFB.bin", ios::binary | ios::app);

    structResultadosLPFB resultado;

    cout << "Ingrese el nombre del equipo local: ";
    cin.ignore();
    cin.getline(resultado.nombreEquipoLocal, 50);

    // Verificar si el equipo local existe
    archivoEquipos.seekg(0, ios::beg);
    bool equipoLocalExistente = false;
    while (archivoEquipos.read(reinterpret_cast<char*>(&resultado), sizeof(structEquiposLPFB)))
    {
        if (strcmp(resultado.nombreEquipoLocal, resultado.nombreEquipoLocal) == 0)
        {
            equipoLocalExistente = true;
            break;
        }
    }

    if (!equipoLocalExistente)
    {
        cout << "¡Error! El equipo local no existe." << endl;
        return;
    }

    cout << "Ingrese el nombre del equipo visitante: ";
    cin.getline(resultado.nombreEquipoVisitante, 50);

    // Verificar si el equipo visitante existe
    archivoEquipos.seekg(0, ios::beg);
    bool equipoVisitanteExistente = false;
    while (archivoEquipos.read(reinterpret_cast<char*>(&resultado), sizeof(structEquiposLPFB)))
    {
        if (strcmp(resultado.nombreEquipoVisitante, resultado.nombreEquipoVisitante) == 0)
        {
            equipoVisitanteExistente = true;
            break;
        }
    }

    if (!equipoVisitanteExistente)
    {
        cout << "¡Error! El equipo visitante no existe." << endl;
        return;
    }

    cout << "Ingrese los goles del equipo local: ";
    cin >> resultado.golesEquipoLocal;

    cout << "Ingrese los goles del equipo visitante: ";
    cin >> resultado.golesEquipoVisitante;

    cout << "Ingrese la fecha del partido: ";
    cin.ignore();
    cin.getline(resultado.fechaPartido, 10);

    archivoResultados.write(reinterpret_cast<const char*>(&resultado), sizeof(structResultadosLPFB));

    cout << "Resultado ingresado correctamente." << endl;

    archivoEquipos.close();
    archivoResultados.close();
}

void mostrarTablaPosiciones()
{
    ifstream archivoEquipos("EquiposLPFB.bin", ios::binary);

    if (!archivoEquipos)
    {
        cout << "¡Error! Primero debe ingresar los equipos." << endl;
        return;
    }

    ifstream archivoResultados("ResultadosLPFB.bin", ios::binary);

    if (!archivoResultados)
    {
        cout << "¡Error! Primero debe ingresar los resultados." << endl;
        return;
    }

    structEquiposLPFB equipo;
    structResultadosLPFB resultado;

    // Leer equipos
    while (archivoEquipos.read(reinterpret_cast<char*>(&equipo), sizeof(structEquiposLPFB)))
    {
        int puntos = 0;

        // Leer resultados
        archivoResultados.clear();
        archivoResultados.seekg(0, ios::beg);
        while (archivoResultados.read(reinterpret_cast<char*>(&resultado), sizeof(structResultadosLPFB)))
        {
            if (strcmp(equipo.nombreEquipo, resultado.nombreEquipoLocal) == 0)
            {
                if (resultado.golesEquipoLocal > resultado.golesEquipoVisitante)
                    puntos += 3;
                else if (resultado.golesEquipoLocal == resultado.golesEquipoVisitante)
                    puntos += 1;
            }
            else if (strcmp(equipo.nombreEquipo, resultado.nombreEquipoVisitante) == 0)
            {
                if (resultado.golesEquipoVisitante > resultado.golesEquipoLocal)
                    puntos += 3;
                else if (resultado.golesEquipoVisitante == resultado.golesEquipoLocal)
                    puntos += 1;
            }
        }

        cout << "Equipo: " << equipo.nombreEquipo << "\t Puntos: " << puntos << endl;
    }

    archivoEquipos.close();
    archivoResultados.close();
}

int main()
{
    int opcion;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Ingreso de datos de los equipos de la LPFB.\n";
        cout << "2. Ingreso de los resultados de los partidos.\n";
        cout << "3. Reporte de la tabla de posiciones.\n";
        cout << "4. Salir.\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            ingresarEquipos();
            break;

        case 2:
            ingresarResultados();
            break;

        case 3:
            mostrarTablaPosiciones();
            break;

        case 4:
            cout << "Saliendo del programa. Hasta luego.\n";
            break;

        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
        }

    } while (opcion != 4);

    return 0;
}
