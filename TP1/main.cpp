//GRUPO 3
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring> // libreria para usar el strcmp 
using namespace std;

    //ESTRUCTURAS
struct Producto {
    char SKU [10];         //"codigo"
    char Descripcion [20]; //descripcion del producto(nombre)
    float CostoFijo;
    };

struct Reparacion{
    char Cliente[15];
    char SKU [10];     //"codigo"
    int tipo ;         //0: Electrónico    1: Mecánico   2: Mecatrónico
    float CostoDirecto; 
    float Presu;       // presupuesto
    };

/*Producto es la descripcion y itpo de producto depednedel codiho, electro, mecan,...*/

// VARIABLES GLOBALES
const int MAX_PROD = 10;
int cantReparaciones = 0; // cantidad total de reparaciones cargadas

// Funciones Auxiliares
// Convierte tipo de producto a texto
const char* TipoToStr(int tipo) {
    switch (tipo) {
        case 0: return "Electrónico";
        case 1: return "Mecánico";
        case 2: return "Mecatrónico";
        default: return "Desconocido";
    }
}

// FUNCIONES DE CARGA
void Cargar_producto(Producto*& prod) {
    ifstream archilec("productos.bin", ios::binary);
    if (!archilec) {
        cout << "[!] No se ha podido abrir productos.bin" << endl;
        return;
    }

    prod = new Producto[MAX_PROD];   
    for (int i = 0; i < MAX_PROD; i++) {
        archilec.read(reinterpret_cast<char*>(&prod[i]), sizeof(Producto));
    }
    archilec.close();
}

void Cargar_reparaciones(Reparacion*& rep) {
    ifstream archilec("reparaciones.bin", ios::binary);
    if (!archilec) {
        cout << "[!] No se ha podido abrir reparaciones.bin" << endl;
        return;
    }

    // Contar reparaciones
    Reparacion aux;
    while (archilec.read(reinterpret_cast<char*>(&aux), sizeof(Reparacion))) {
        cantReparaciones++;
    }

    rep = new Reparacion[cantReparaciones];
    archilec.clear();
    archilec.seekg(0);

    for (int i = 0; i < cantReparaciones; i++) {
        archilec.read(reinterpret_cast<char*>(&rep[i]), sizeof(Reparacion));
    }

    archilec.close();
}

// Función de para ordenar y buscar
void Ordenar(Reparacion* rep) {
    for (int i = 0; i < cantReparaciones - 1; i++) {
        for (int j = 0; j < cantReparaciones - 1 - i; j++) {
            bool cambio = false;

            if (strcmp(rep[j].Cliente, rep[j + 1].Cliente) > 0) cambio = true;
            else if (strcmp(rep[j].Cliente, rep[j + 1].Cliente) == 0) {
                if (rep[j].tipo > rep[j + 1].tipo) cambio = true;
                else if (rep[j].tipo == rep[j + 1].tipo) {
                    if (strcmp(rep[j].SKU, rep[j + 1].SKU) > 0) cambio = true;
                }
            }

            if (cambio) {
                Reparacion temp = rep[j];
                rep[j] = rep[j + 1];
                rep[j + 1] = temp;
            }
        }
    }
}

// Buscar producto por SKU (retorna índice)
int BuscarProducto(Producto* prod, const char* sku) {
    for (int i = 0; i < MAX_PROD; i++) {
        if (strncmp(prod[i].SKU, sku, 10) == 0) {
            return i;
        }
    }
    return -1;
}

// Mostrar Reparaciones del Cliente
void MostrarCliente(Reparacion* rep, Producto* prod, const char* nombre) {
    bool hayReparaciones = false;
    float totalGanancia = 0;

    for (int i = 0; i < cantReparaciones; i++) {
        if (strcmp(rep[i].Cliente, nombre) == 0) {
            hayReparaciones = true;

            int pos = BuscarProducto(prod, rep[i].SKU);
            if (pos == -1) {
                cout << "[!] Producto no encontrado para SKU: " << rep[i].SKU << endl;
                continue;
            }

            // Mostrar datos de la reparación
            cout << "-----------------------------" << endl;
            cout << "Cliente: " << rep[i].Cliente << endl;
            cout << "Tipo de producto: " << TipoToStr(rep[i].tipo) << endl;
            cout << "SKU: " << rep[i].SKU << endl;
            cout << "Producto: " << prod[pos].Descripcion << endl;
            cout << "Costo fijo: " << prod[pos].CostoFijo << endl;
            cout << "Costo directo: " << rep[i].CostoDirecto << endl;
            cout << "Presupuestado: " << rep[i].Presu << endl;

            // Calcular ganancia
            float ganancia = rep[i].Presu - (prod[pos].CostoFijo + rep[i].CostoDirecto);
            totalGanancia += ganancia;
            cout << "Ganancia en esta reparación: " << ganancia << endl;
        }
    }
    
    if (!hayReparaciones) {
        cout << "[!] No se encontraron reparaciones para el cliente: " << nombre << endl;
    } else {
        cout << "[+] Ganancia total: " << totalGanancia << endl;
    }
}

//MAIN
int main(){
Producto* prod = nullptr;
Reparacion* rep = nullptr; 
char NomCliente[15];

Cargar_producto(prod);
Cargar_reparaciones(rep);//Lectura y cargar datos 

Ordenar(rep); //<Reparacion>(rep, cantReparaciones, criterioReparacion); es para ordenar reparaciones

// Loop de consulta
cout << "Ingresar el nombre del cliente (EOF para terminar): ";
cin.getline(NomCliente, 15);
while (!cin.eof()) {
    MostrarCliente(rep, prod, NomCliente);
    cout << "Ingresar el nombre del cliente (EOF para terminar): ";
    cin.getline(NomCliente, 15);
}

// Liberar memoria
delete[] prod;
delete[] rep;

    
return 0;
}






