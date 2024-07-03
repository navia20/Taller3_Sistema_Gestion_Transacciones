#include "Transaccion.h"
#include <iostream>
using namespace std;
// Constructor
Transaccion::Transaccion(int id, string cuentaOrigen, string cuentaDestino, int monto, string ubicacion, string fechayHora) {
    this->id = id;
    this->cuentaOrigen = cuentaOrigen;
    this->cuentaDestino = cuentaDestino;
    this->monto = monto;
    this->ubicacion = ubicacion;
    this->fechayHora = fechayHora;
}

// Setters
void Transaccion::setId(int id) {
    this->id = id;
}

void Transaccion::setCuentaOrigen(string cuentaOrigen) {
    this->cuentaOrigen = cuentaOrigen;
}

void Transaccion::setCuentaDestino(string cuentaDestino) {
    this->cuentaDestino = cuentaDestino;
}

void Transaccion::setMonto(int monto) {
    this->monto = monto;
}

void Transaccion::setUbicacion(string ubicacion) {
    this->ubicacion = ubicacion;
}

void Transaccion::setFechayHora(string fechayHora) {
    this->fechayHora = fechayHora;
}
void Transaccion::setEtiqueta(string etiqueta) {
    this->etiqueta = etiqueta;
}
// Getters
int Transaccion::getId() {
    return id;
}

string Transaccion::getCuentaOrigen() {
    return cuentaOrigen;
}

string Transaccion::getCuentaDestino() {
    return cuentaDestino;
}

int Transaccion::getMonto() {
    return monto;
}

string Transaccion::getUbicacion() {
    return ubicacion;
}

string Transaccion::getFechayHora() {
    return fechayHora;
}
string Transaccion::getEtiqueta() {
    return etiqueta;
}
void Transaccion::imprimir(){
    cout << " " << endl;
    cout << "Cuenta Origen: " << cuentaOrigen << endl;
    cout << "Cuenta Destino: " << cuentaDestino << endl;
    cout << "Monto: " << monto << endl;
    cout << "Ubicacion: " << ubicacion << endl;
    cout << "Hora y Fecha : " << fechayHora << endl; 
    cout << "Etiqueta : " << etiqueta << endl;
    
}
void Transaccion::catalogo(){
    cout <<  id << " " << cuentaOrigen << " " <<  cuentaDestino << " " << monto << " " << ubicacion << " " << fechayHora << " " << etiqueta <<  endl;
    
}