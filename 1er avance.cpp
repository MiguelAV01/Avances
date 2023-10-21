#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct Alumno {
    string matricula;
    string nombreCompleto;
    double calificacion1;
    double calificacion2;
    double calificacion3;
    double calificacionFinal;
};

const int MAX_ALUMNOS = 5; // Tamaño máximo del arreglo de alumnos
Alumno alumnos[MAX_ALUMNOS]; // Arreglo de alumnos

int numAlumnos = 0; // Variable para rastrear la cantidad de alumnos registrados

void altaAlumno() {
    system("cls");
    if (numAlumnos < MAX_ALUMNOS) {
        Alumno nuevoAlumno;
        cout << "ALTA DE ALUMNO" << endl;
        cout << "Ingrese la matricula del alumno: ";
        cin >> nuevoAlumno.matricula;
        cout << "Ingrese el nombre completo del alumno: ";
        cin.ignore();
        getline(cin, nuevoAlumno.nombreCompleto);
        cout << "Ingrese la calificacion 1: ";
        cin >> nuevoAlumno.calificacion1;
        cout << "Ingrese la calificacion 2: ";
        cin >> nuevoAlumno.calificacion2;
        cout << "Ingrese la calificacion 3: ";
        cin >> nuevoAlumno.calificacion3;
        nuevoAlumno.calificacionFinal = (nuevoAlumno.calificacion1 + nuevoAlumno.calificacion2 + nuevoAlumno.calificacion3) / 3;
        alumnos[numAlumnos] = nuevoAlumno;
        numAlumnos++;
        cout << "Alumno registrado exitosamente." << endl;
    }
    else {
        cout << "Se ha alcanzado el limite de alumnos registrados." << endl;
    }
    system("pause");
}

void bajaAlumno() {
    system("cls");
    if (numAlumnos > 0) {
        cout << "BAJA DE ALUMNO" << endl;
        int indice;
        cout << "Ingrese el indice del alumno a dar de baja (0-" << numAlumnos - 1 << "): ";
        cin >> indice;
        if (indice >= 0 && indice < numAlumnos) {
            for (int i = indice; i < numAlumnos - 1; i++) {
                alumnos[i] = alumnos[i + 1];
            }
            numAlumnos--;
            cout << "Alumno dado de baja exitosamente." << endl;
        }
        else {
            cout << "Indice no valido." << endl;
        }
    }
    else {
        cout << "No hay alumnos registrados." << endl;
    }
    system("pause");
}

void listarAlumnos() {
    system("cls");
    cout << "LISTA DE ALUMNOS" << endl;
    if (numAlumnos > 0) {
        for (int i = 0; i < numAlumnos; i++) {
            cout << "Alumno " << i + 1 << ":" << endl;
            cout << "Matricula: " << alumnos[i].matricula << endl;
            cout << "Nombre Completo: " << alumnos[i].nombreCompleto << endl;
            cout << "Calificacion 1: " << alumnos[i].calificacion1 << endl;
            cout << "Calificacion 2: " << alumnos[i].calificacion2 << endl;
            cout << "Calificacion 3: " << alumnos[i].calificacion3 << endl;
            cout << "Calificacion Final: " << alumnos[i].calificacionFinal << endl;
            cout << "---------------------------------------------" << endl;
        }
    }
    else {
        cout << "No hay alumnos registrados." << endl;
    }
    system("pause");
}
void modificarAlumno() {
    system("cls");
    if (numAlumnos > 0) {
        cout << "MODIFICAR ALUMNO" << endl;
        string matriculaBuscada;
        cout << "Ingrese la matricula del alumno a modificar: ";
        cin >> matriculaBuscada;

        int indice = -1; // Variable para rastrear el índice del alumno a modificar

        // Buscar al alumno por matrícula
        for (int i = 0; i < numAlumnos; i++) {
            if (alumnos[i].matricula == matriculaBuscada) {
                indice = i;
                break;
            }
        }

        if (indice != -1) {
            // Alumno encontrado
            cout << "Alumno encontrado. Realice las modificaciones:" << endl;
            cout << "Nuevo nombre completo: ";
            cin.ignore();
            getline(cin, alumnos[indice].nombreCompleto);
            cout << "Nuevas calificaciones:" << endl;
            cout << "Calificacion 1: ";
            cin >> alumnos[indice].calificacion1;
            cout << "Calificacion 2: ";
            cin >> alumnos[indice].calificacion2;
            cout << "Calificacion 3: ";
            cin >> alumnos[indice].calificacion3;
            alumnos[indice].calificacionFinal = (alumnos[indice].calificacion1 + alumnos[indice].calificacion2 + alumnos[indice].calificacion3) / 3;
            cout << "Datos modificados exitosamente." << endl;
        }
        else {
            cout << "Alumno no encontrado." << endl;
        }
    }
    else {
        cout << "No hay alumnos registrados." << endl;
    }
    system("pause");
}

int main() {
    int opcion;
    do {
        system("cls");
        cout << "MENU DE OPCIONES" << endl;
        cout << "1. Alta" << endl;
        cout << "2. Baja" << endl;
        cout << "3. Lista de Alumnos" << endl;
        cout << "4. Modificar" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            altaAlumno();
            break;
        case 2:
            bajaAlumno();
            break;
        case 3:
            listarAlumnos();
            break;
        case 4:
            modificarAlumno();
            break;
        case 5:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente nuevamente." << endl;
            system("pause");
        }
    } while (opcion != 5); // Actualiza el numero para salir

    return 0;
}

