//aqui esta el primer avance bien hecho, fui yo el que le hablo ayer de la equivocacion jaja, pero ya esta
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdio.h>
using namespace std;

class Orden {
public:
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

    Orden() {
        numeroTicket = 0;
        razonSocial = "";
        vendedor = "";
        fecha = "";
        precioUnitarioTotal = 0;
        descuentos = 0;
        propina = 0;
        impuesto = 0;
        total = 0;
    }
    void agregarArticulo(string articulo, double precio, int cantidad) {
        articulos.push_back(articulo);
        precios.push_back(precio);
        cantidades.push_back(cantidad);
        precioUnitarioTotal += precio * cantidad;
    }

    void calcularTotal() {
        total = precioUnitarioTotal - (precioUnitarioTotal * (descuentos / 100)) +
            (precioUnitarioTotal * (propina / 100)) + (precioUnitarioTotal * (impuesto / 100));
    }

    void mostrarOrden() {
        cout << "Numero de Ticket: " << numeroTicket << endl;
        cout << "Razon Social: " << razonSocial << endl;
        cout << "Vendedor: " << vendedor << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "Artículos: " << endl;
        for (int i = 0; i < articulos.size(); i++) {
            cout << articulos[i] << " - Precio: $" << precios[i] << " - Cantidad: " << cantidades[i] << endl;
        }
        cout << "Precio Unitario Total: $" << precioUnitarioTotal << endl;
        cout << "Descuentos/Promociones (%): " << descuentos << endl;
        cout << "Propina (10%, 15%, 20%): " << propina << endl;
        cout << "Impuesto (%): " << impuesto << endl;
        cout << "Total: $" << total << endl;
    }
};

int main() {
    vector<Orden> ordenes;
    int numeroTicketActual = 1;
    const int MAX_TICKETS = 3; // limite

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
        case 1: //alta de orden
        {
            if (numeroTicketActual <= MAX_TICKETS) {
                Orden nuevaOrden;
                nuevaOrden.numeroTicket = numeroTicketActual;

                cin.ignore();
                cout << "Razon Social del Restaurante: ";
                getline(cin, nuevaOrden.razonSocial);

                cout << "Nombre del Vendedor: ";
                getline(cin, nuevaOrden.vendedor);

                cout << "Fecha: ";
                getline(cin, nuevaOrden.fecha);

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

                    nuevaOrden.agregarArticulo(articulo, precio, cantidad);
                }

                cout << "Descuentos o Promociones (%): ";
                cin >> nuevaOrden.descuentos;

                cout << "Propina (10%, 15%, 20%): ";
                cin >> nuevaOrden.propina;

                cout << "Impuesto (%): ";
                cin >> nuevaOrden.impuesto;

                nuevaOrden.calcularTotal();
                ordenes.push_back(nuevaOrden);

                cout << "¡Orden agregada con exito!" << endl;

                numeroTicketActual++;
            }
            else {
                cout << "Maximo de tickets alcanzados" << endl;
            }
           
            break;
        }
        
        case 2: // Modificar Orden
        {
            cout << "Opcion no disponible en este momento." << endl;

            break; }
        
        case 3: // Eliminar o Cancelar Orden
        {
            cout << "Opcion no disponible en este momento." << endl;
            break;
        }
        case 4: // Lista de Ordenes
        {
            cout << "Lista de Ordenes:" << endl;
            for (Orden orden : ordenes) {
                orden.mostrarOrden();
                cout << endl;
            }
                break;
            
        }
        case 5: // Limpiar Pantalla
        {
            cout << "Opcion no valida. Por favor, selecciona una opcion valida." << endl;
            break;
        }
        case 6: // Salir
        {
            return 0;
        default:
            cout << "Opcion no valida. Por favor, selecciona una opción valida." << endl;
            break;
        }
        }
        }

        return 0;
    }
