//GRUPO 3
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring> // libreria para usar el strcmp 
using namespace std;

#pragma pack(1) // Quito los espacios de relleno (alineacion de 1 byte)

//ESTRUCTURAS
struct producto {
    char SKU [11];         //"codigo"
    char descripcion [21]; //descripcion del producto(nombre)
    float costoFijo;
    };

struct reparacion {
    char Cliente[16];   // 15
    int tipo;           // 4
    char SKU[11];       // 10
    float costoDirecto; // 4
    float presu;        // 4
};
#pragma pack()
 
// VARIABLES GLOBALES
const int MAX_pROD = 10;
int cantproductos = 0;
int cantReparaciones = 0; 

// Funciones Auxiliares

// Convierte tipo de producto a texto
const char* TipoToStr(int tipo) {
    switch (tipo) {
        case 0: return "Electronico";
        case 1: return "Mecanico";
        case 2: return "Mecatronico";
        default: return "Desconocido";
    }
}

// Funcion para eliminar espacios en blanco al final de una cadena
string trim(const char* str) {
    string s(str); // Convierte el const char* a std::string
    size_t end = s.find_last_not_of(' '); // Busca el último caracter que NO sea espacio
    if (end != string::npos)
        s = s.substr(0, end + 1); // Corta la cadena hasta ese caracter (incluyéndolo)
    else
        s = ""; // Si todos eran espacios, devuelve cadena vacía
    return s;
}


// FUNCIONES DE CARGA
void cargar_producto(producto*& prod) {
    ifstream archilec("productos.bin", ios::binary);
    if (!archilec) {
        cout << "[!] No se ha podido abrir productos.bin" << endl;
        return;
    }

    archilec.seekg(0, ios::end);
    long tam = archilec.tellg();
    cantproductos = tam / sizeof(producto);
    archilec.seekg(0, ios::beg);

    prod = new producto[cantproductos];
    for (int i = 0; i < cantproductos; i++) {
        archilec.read(reinterpret_cast<char*>(&prod[i]), sizeof(producto));
        prod[i].SKU[10] = '\0';           // asegurar terminación
        prod[i].descripcion[20] = '\0';  // idem
    }

    archilec.close();
}


void cargar_reparaciones(reparacion*& rep) {
    ifstream archilec("reparaciones.bin", ios::binary);
    if (!archilec) {
        cout << "[!] No se ha podido abrir reparaciones.bin" << endl;
        return;
    }

    // Calcular cantidad de registros en el archivo
    archilec.seekg(0, ios::end);
    long tam = archilec.tellg();
    cantReparaciones = tam / sizeof(reparacion);
    archilec.seekg(0, ios::beg);

    // Reservar memoria
    rep = new reparacion[cantReparaciones];

    // Leer cada registro de una sola vez
    for (int i = 0; i < cantReparaciones; i++) {
        archilec.read(reinterpret_cast<char*>(&rep[i]), sizeof(reparacion));
        rep[i].SKU[10] = '\0';
    }

    archilec.close();
}



// Función de para o y buscar
void ordenar(reparacion* rep) {
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
                reparacion temp = rep[j];
                rep[j] = rep[j + 1];
                rep[j + 1] = temp;
            }
        }
    }
}

// Buscar producto por SKU (retorna índice)
int Buscarproducto(producto* prod, const char* sku) {
    string buscado = trim(sku); 
    for (int i = 0; i < cantproductos; i++) {
        string actual = trim(prod[i].SKU);
        if (actual == buscado) {
            return i;
        }
    }
    return -1;
}

// Mostrar Reparaciones del Cliente
void mostrarCliente(reparacion* rep, producto* prod, const char* nombre) {
    bool hayReparaciones = false;
    float totalGanancia = 0;

    string buscado = trim(nombre);

    for (int i = 0; i < cantReparaciones; i++) {
        string cliente = trim(rep[i].Cliente);

        if (cliente == buscado) { 
            hayReparaciones = true;

            int pos = Buscarproducto(prod, trim(rep[i].SKU).c_str());
            if (pos == -1) {
                cout << "[!] Producto no encontrado para SKU: " << rep[i].SKU << endl;
                continue;
            }

            cout << "-----------------------------" << endl;
            cout << "Cliente: " << cliente << endl;
            cout << "Tipo de producto: " << TipoToStr(rep[i].tipo) << endl;
            cout << "SKU: " << trim(rep[i].SKU) << endl;
            cout << "Producto: " << trim(prod[pos].descripcion) << endl;
            cout << "Costo fijo: $" << prod[pos].costoFijo << endl;
            cout << "Costo directo: $" << rep[i].costoDirecto << endl;
            cout << "Presupuestado: $" << rep[i].presu << endl;

            float ganancia = rep[i].presu - (prod[pos].costoFijo + rep[i].costoDirecto);
            totalGanancia += ganancia;
            cout << "Ganancia en esta reparacion: $" << ganancia << endl;
        }
    }

    if (!hayReparaciones) {
        cout << "[!] No se encontraron reparaciones para el cliente: " << nombre << endl;
    } else {
        cout << "\n[+] Ganancia total: $" << totalGanancia << "\n"<< endl;
    }
}

//MAIN
int main(){
producto* prod = nullptr;
reparacion* rep = nullptr; 
char nomCliente[16];

cargar_producto(prod);
cargar_reparaciones(rep);//Lectura y cargar datos 

ordenar(rep); //<reparacion>(rep, cantReparaciones, criterioReparacion); es para ordenar reparaciones

// Loop de consulta
cout << "Ingresar el nombre del cliente (EOF para terminar): ";
while (cin.getline(nomCliente, 16)) {
    mostrarCliente(rep, prod, nomCliente);
    cout << "Ingresar el nombre del cliente (EOF para terminar): ";
}

// Liberar memoria
delete[] prod;
delete[] rep;

    
return 0;
}
