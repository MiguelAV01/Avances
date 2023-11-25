#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <sstream>
#include <stdio.h>
#include <istream>
using namespace std;

// Estructura para almacenar la informacion de un ticket
struct Ticket {
    string razonSocial;
    int numeroTicket;
    string vendedor;
    string fecha;
    vector<string> articulos;
    vector<double> precios;
    vector<int> cantidades;
    double precioUnitarioTotal;
    double descuentos;
    double propina;
    double impuesto;
    double total;
    bool cancelado; // Nuevo miembro para indicar si el ticket está cancelado
};
string obtenerFechaActual() {
    time_t now = time(0);
    tm timeinfo;
    if (localtime_s(&timeinfo, &now) != 0) {
        cerr << "Error al obtener la fecha actual." << endl;
        return "";
    }

    stringstream ss;
    ss << 1900 + timeinfo.tm_year << "-"
        << 1 + timeinfo.tm_mon << "-"
        << timeinfo.tm_mday;

    return ss.str();
}
// Funcion para agregar un artículo a un ticket
void agregarArticulo(Ticket* ticket, string articulo, double precio, int cantidad) {
    ticket->articulos.push_back(articulo);
    ticket->precios.push_back(precio);
    ticket->cantidades.push_back(cantidad);
    ticket->precioUnitarioTotal += precio * cantidad;
}

// Funcion para calcular el total de un ticket
void calcularTotal(Ticket* ticket) {
    ticket->precioUnitarioTotal = 0; // Reiniciar el total antes de recalcularlo

    for (int i = 0; i < ticket->articulos.size(); i++) {
        ticket->precioUnitarioTotal += ticket->precios[i] * ticket->cantidades[i];
    }

    ticket->total = ticket->precioUnitarioTotal - (ticket->precioUnitarioTotal * (ticket->descuentos / 100)) +
        (ticket->precioUnitarioTotal * (ticket->propina / 100)) + (ticket->precioUnitarioTotal * (ticket->impuesto / 100));
}


// Funcion para mostrar la información de un ticket
void mostrarTicket(const Ticket* ticket) {
    cout << "Numero de Ticket: " << ticket->numeroTicket << endl;
    if (ticket->cancelado) {
        cout << "Estado: Cancelado" << endl;
    }
    cout << "Razon Social: " << ticket->razonSocial << endl;
    cout << "Vendedor: " << ticket->vendedor << endl;
    cout << "Fecha: " << ticket->fecha << endl;
    cout << "Articulos: " << endl;
    for (int i = 0; i < ticket->articulos.size(); i++) {
        cout << ticket->articulos[i] << " - Precio: $" << ticket->precios[i] << " - Cantidad: " << ticket->cantidades[i] << endl;
    }
    cout << "Precio Unitario Total: $" << ticket->precioUnitarioTotal << endl;
    cout << "Descuentos/Promociones (%): " << ticket->descuentos << endl;
    cout << "Propina (10%, 15%, 20%): " << ticket->propina << endl;
    cout << "Impuesto (%): " << ticket->impuesto << endl;
    cout << "Total: $" << ticket->total << endl;

   

    cout << "------------------------------" << endl;
}

// Funcion para guardar los tickets en un archivo de texto
void guardarEnArchivo(const vector<Ticket*>& ordenes, const string& Las_GodBurguesas) {
    string nombreArchivo = Las_GodBurguesas + "-" + obtenerFechaActual() + ".txt";

    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (const Ticket* ticket : ordenes) {
            archivo << "Numero de Ticket: " << ticket->numeroTicket << endl;
            archivo << "Razon Social: " << ticket->razonSocial << endl;
            archivo << "Vendedor: " << ticket->vendedor << endl;
            archivo << "Fecha: " << ticket->fecha << endl;

            archivo << "Articulos: " << endl;
            for (int i = 0; i < ticket->articulos.size(); i++) {
                archivo << ticket->articulos[i] << " - Precio: $" << ticket->precios[i] << " - Cantidad: " << ticket->cantidades[i] << endl;
            }
            archivo << "Precio Unitario Total: $" << ticket->precioUnitarioTotal << endl;
            archivo << "Descuentos/Promociones (%): " << ticket->descuentos << endl;
            archivo << "Propina (10%, 15%, 20%): " << ticket->propina << endl;
            archivo << "Impuesto (%): " << ticket->impuesto << endl;
            archivo << "Total: $" << ticket->total << endl;

            if (ticket->cancelado) {
                archivo << "Estado: Cancelado" << endl;
            }

            archivo << "------------------------------" << endl;
        }
        archivo.close();
        cout << "Tickets guardados en el archivo " << nombreArchivo << endl;
    }
    else {
        cout << "Error al abrir el archivo " << nombreArchivo << " para escribir." << endl;
    }
}
//Funcion para modificar articulos
void modificarArticulo(Ticket* ticket, int numeroArticulo) {
    if (numeroArticulo < 1 || numeroArticulo > ticket->articulos.size()) {
        cout << "Numero de articulo no valido." << endl;
        return;
    }

    // Obtener el índice correspondiente al número de artículo
    int indice = numeroArticulo - 1;

    // Modificar la información del artículo
    string nuevoArticulo;
    double nuevoPrecio;
    int nuevaCantidad;

    cin.ignore();
    cout << "Nuevo nombre del Articulo " << numeroArticulo << ": ";
    getline(cin, nuevoArticulo);

    cout << "Nuevo precio del Articulo " << numeroArticulo << ": ";
    cin >> nuevoPrecio;

    cout << "Nueva cantidad del Articulo " << numeroArticulo << ": ";
    cin >> nuevaCantidad;

    // Modificar los datos en el ticket
    ticket->articulos[indice] = nuevoArticulo;
    ticket->precios[indice] = nuevoPrecio;
    ticket->cantidades[indice] = nuevaCantidad;

    calcularTotal(ticket);

    cout << "Articulo modificado exitosamente." << endl;
}


int main() {

    vector<Ticket*> ordenes;
    int numeroTicketActual = 1;

    while (true) {
        cout << "Menu de Opciones:" << endl;
        cout << "1. Alta de Ordenes" << endl;
        cout << "2. Modificar Orden" << endl;
        cout << "3. Eliminar o Cancelar Orden" << endl;
        cout << "4. Lista de Ordenes" << endl;
        cout << "5. Limpiar Pantalla" << endl;
        cout << "6. Salir" << endl;

        int opcion;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: // Alta de orden
        {
            Ticket* nuevoTicket = new Ticket();
            nuevoTicket->numeroTicket = numeroTicketActual;

            cin.ignore();
            cout << "Razon Social del Restaurante: ";
            getline(cin, nuevoTicket->razonSocial);

            cout << "Nombre del Vendedor: ";
            getline(cin, nuevoTicket->vendedor);

            cout << "Fecha: ";
            getline(cin, nuevoTicket->fecha);

            int numArticulos;
            cout << "Numero de Articulos: ";
            cin >> numArticulos;

            for (int i = 0; i < numArticulos; i++) {
                string articulo;
                double precio;
                int cantidad;

                cin.ignore();
                cout << "Nombre del Articulo " << (i + 1) << ": ";
                getline(cin, articulo);

                cout << "Precio del Articulo " << (i + 1) << ": ";
                cin >> precio;

                cout << "Cantidad del Articulo " << (i + 1) << ": ";
                cin >> cantidad;

                agregarArticulo(nuevoTicket, articulo, precio, cantidad);
            }

            cout << "Descuentos o Promociones (%): ";
            cin >> nuevoTicket->descuentos;

            cout << "Propina (10%, 15%, 20%): ";
            cin >> nuevoTicket->propina;

            cout << "Impuesto (%): ";
            cin >> nuevoTicket->impuesto;

            calcularTotal(nuevoTicket);
            ordenes.push_back(nuevoTicket);

            cout << "¡Orden agregada con exito!" << endl;

            numeroTicketActual++;

            break;
        }
        case 2: // Modificar Orden
        {
            if (ordenes.empty()) {
                cout << "No hay ordenes para modificar." << endl;
                break;
            }

            int numeroTicketModificar;
            cout << "Ingrese el numero de ticket a modificar: ";
            cin >> numeroTicketModificar;

            bool encontrado = false;
            for (Ticket* ticket : ordenes) {
                if (ticket->numeroTicket == numeroTicketModificar) {
                    int opcionModificar;
                    cout << "Seleccione el aspecto a modificar:" << endl;
                    cout << "1. Razon Social" << endl;
                    cout << "2. Vendedor" << endl;
                    cout << "3. Fecha" << endl;
                    cout << "4. Articulos" << endl;

                    cout << "Selecciona una opcion: ";
                    cin >> opcionModificar;

                    switch (opcionModificar) {
                    case 1:
                        cin.ignore();
                        cout << "Nueva Razon Social: ";
                        getline(cin, ticket->razonSocial);
                        cout << "Razon Social modificada exitosamente." << endl;
                        break;

                    case 2:
                        cin.ignore();
                        cout << "Nuevo Vendedor: ";
                        getline(cin, ticket->vendedor);
                        cout << "Vendedor modificado exitosamente." << endl;
                        break;

                    case 3:
                        cin.ignore();
                        cout << "Nueva Fecha: ";
                        getline(cin, ticket->fecha);
                        cout << "Fecha modificada exitosamente." << endl;
                        break;

                    case 4:
                        int numeroArticuloModificar;
                        cout << "Ingrese el numero de articulo a modificar: ";
                        cin >> numeroArticuloModificar;
                        modificarArticulo(ticket, numeroArticuloModificar);
                        break;

                    default:
                        cout << "Opcion no válida." << endl;
                        break;
                    }

                    encontrado = true;
                    break;
                }
            }

            if (!encontrado) {
                cout << "No se encontro la orden con el numero de ticket especificado." << endl;
            }
            break;
        }

        case 3: // Eliminar o Cancelar Orden
        {
            if (ordenes.empty()) {
                cout << "No hay ordenes para eliminar o cancelar." << endl;
                break;
            }

            int numeroTicketEliminar;
            cout << "Ingrese el numero de ticket a eliminar o cancelar: ";
            cin >> numeroTicketEliminar;

            bool encontrado = false;
            for (Ticket* ticket : ordenes) {
                if (ticket->numeroTicket == numeroTicketEliminar) {
                    char opcionEliminarCancelar;
                    cout << "Seleccione una opcion (E para Eliminar, C para Cancelar): ";
                    cin >> opcionEliminarCancelar;
                    if (opcionEliminarCancelar == 'E' || opcionEliminarCancelar == 'e') {
                        // Eliminar el ticket
                        auto iter = find(ordenes.begin(), ordenes.end(), ticket);
                        ordenes.erase(iter);
                        delete ticket; // Liberar memoria del ticket
                        cout << "Orden eliminada exitosamente." << endl;
                    }
                    else if (opcionEliminarCancelar == 'C' || opcionEliminarCancelar == 'c') {
                        // Marcar como cancelado
                        ticket->cancelado = true;
                        cout << "Orden cancelada exitosamente." << endl;
                    }
                    else {
                        cout << "Opcion no valida. No se realizo ninguna accion." << endl;
                    }
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "No se encontro la orden con el numero de ticket especificado." << endl;
            }
            break;
        }
        case 4: // Lista de Ordenes
        {
            if (ordenes.empty()) {
                cout << "No hay ordenes para mostrar." << endl;
            }
            else {
                cout << "Lista de Ordenes:" << endl;
                cout << "1. Mostrar Todas las Ordenes" << endl;
                cout << "2. Filtrar por Numero de Ticket" << endl;

                int opcionFiltro;
                cout << "Selecciona una opcion: ";
                cin >> opcionFiltro;
                if (opcionFiltro == 1) {
                    for (const Ticket* ticket : ordenes) {
                        mostrarTicket(ticket);
                    }
                }
                else if (opcionFiltro == 2) {
                    int numeroTicketFiltrar;
                    cout << "Ingrese el numero de ticket a mostrar: ";
                    cin >> numeroTicketFiltrar;

                    bool encontrado = false;
                    for (const Ticket* ticket : ordenes) {
                        if (ticket->numeroTicket == numeroTicketFiltrar) {
                            mostrarTicket(ticket);
                            encontrado = true;
                            break;
                        }
                    }

                    if (!encontrado) {
                        cout << "No se encontro la orden con el numero de ticket especificado." << endl;
                    }
                }
                else {
                    cout << "Opcion no valida." << endl;
                }
            }
            break;
        }

        case 5: // Limpiar Pantalla
        {
            system("cls");
            break;
        }
        case 6: // Salir
        {
            guardarEnArchivo(ordenes, "Las_GodBurguesas");
            cout << "Operacion completada. Tickets guardados en el archivo." << endl;
            return 0;
        }
        default:
            cout << "Opcion no valida. Por favor, selecciona una opcion valida." << endl;
            break;
        }
    }

    return 0;
}
        