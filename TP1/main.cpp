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


    //FUNCIONES
void Cargar_producto(Producto*& prod){
    ifstream archilec;
    archilec.open("producto.bin",ios::binary);

    if(!archilec){
        cout << "No se a podido abrir el archivo" << endl;
        return 1;
    }

    Producto p;
    while(archilec.read(reinterpret_cast<char*>(&p), sizeof(Producto))){ // lo encontre en el material del profe

    }archilec.close();
}

void Cargar_reparaciones(Reparacion*& rep){
    ifstream archilec;
    archilec.open("reparaciones.bin",ios::binary);

    if(!archilec){
        cout << "No se a podido abrir el archivo" << endl;
        return 1;
    }

    Reparacion r;
    while(archilec.read(reinterpret_cast<char*>(&r), sizeof(Reparacion))){

    }archilec.close();
}

void Ordenar(){


}

void MostrarCliente(){

}


//MAIN
main(){
Producto* prod = new Producto;
Reparacion* rep = new Reparacion; 
char NomCliente[15];

Cargar_producto(prod);
Cargar_reparaciones(rep);//Lectura y cargar datos 

Ordenar(); //<Reparacion>(rep, cantReparaciones, criterioReparacion); es para ordenar reparaciones

 cout << "Ingresar el nombre del cliente (o EOF para finalizar): ";
cin >> NomCliente; 

    //o también así: cout << "Ingresar el nombre del cliente (EOF para terminar): ";
    //while (cin >> NomCliente) { 
    //MostrarCliente(rep, cantReparaciones, NomCliente, prod);
        //cout << "Ingresar el nombre del cliente (EOF para terminar): ";
    //}

while(strcmp(NomCliente, "EOF") != 0){ // lo encontre en el material del profe (comparar variables tipo char)

MostrarCliente();
}

    

    //Odenar 
    //Buscar rep cliente
    //Calcular ganacia
    //Mostrar 

return 0;}










//esto lo pongo acá para no tosquear el código que hiciste, agregué poco

// VARIABLES GLOBALES
const int MAX_PROD = 10;
int cantReparaciones = 0; // cantidad total de reparaciones cargadas

// FUNCIONES (mantengo lo que pusiste)
void Cargar_producto(Producto*& prod) {
    ifstream archilec("producto.bin", ios::binary);
    if (!archilec) {
        cout << "No se ha podido abrir producto.bin" << endl;
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
        cout << "No se ha podido abrir reparaciones.bin" << endl;
        return 1;
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

// Función de para ordenar ahora
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

void MostrarCliente(Reparacion* rep, Producto* prod, const char* nombre) {
    bool hayReparaciones = false;
    float totalGanancia = 0;

    for (int i = 0; i < cantReparaciones; i++) {
        if (strcmp(rep[i].Cliente, nombre) == 0) {
            hayReparaciones = true;

            int pos = BuscarProducto(prod, rep[i].SKU);
            if (pos == -1) {
                cout << "Producto no encontrado para SKU: " << rep[i].SKU << endl;
                continue;
            }

            //aca van los condicionales de electronico, mecanico, mecatronico
            
    }

    if (!hayReparaciones) {
        cout << "No se encontraron reparaciones para el cliente: " << nombre << endl;
    } else {
        cout << "Ganancia total: " << totalGanancia << endl;
    }
}





