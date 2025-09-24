//GRUPO 3
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring> // libreria para usar el strcmp 
using namespace std;

    //ESTRUCTURAS
struct Producto{
    char SKU [10];//"codigo"
    char Descripcion [20];//descripcion del producto(nombre)
    float CostoFijo;
    };

struct Reparacion{
    char Cliente[15];
    char SKU [10];     //"codigo"
    int tipo ; //0: Electrónico    1: Mecánico   2: Mecatrónico
    float CostoDirecto; 
    float Presu; // presupusto
    };

/*Producto es la descripcion y itpo de producto depednedel codiho, electro, mecan,...*/

    //FUNCIONES
void Cargar_producto(Producto*& prod){
    ifstream archilec;
    archilec.open("producto.bin",ios::binary);

    if(!archilec){
        cout << "No se a podido abrir el archivo" << endl;
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

Ordenar();

 cout << "Ingresar el nombre del cliente (o EOF para finalizar): ";
cin >> NomCliente; 

while(strcmp(NomCliente, "EOF") != 0){ // lo encontre en el material del profe (comparar variables tipo char)

MostrarCliente();
}

    

    //Odenar 
    //Buscar rep cliente
    //Calcular ganacia
    //Mostrar 

return 0;}
