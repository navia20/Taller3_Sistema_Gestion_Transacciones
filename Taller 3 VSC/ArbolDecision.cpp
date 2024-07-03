#include "ArbolDecision.h"
#include <iostream>
#include <string>

using namespace std;

ArbolDecision::ArbolDecision() 
    : raiz(nullptr), montoLimite(100000), ubicacionSospechosa("CHILE"), horaInicio(0), horaFin(6) {}

void ArbolDecision::actualizarCriterios(int monto, const string& ubicacion, int hInicio, int hFin) {
    montoLimite = monto;
    ubicacionSospechosa = ubicacion;
    horaInicio = hInicio;
    horaFin = hFin;
}

int ArbolDecision::getMontoLimite() const {
    return montoLimite;
}

string ArbolDecision::getUbicacionSospechosa() const {
    return ubicacionSospechosa;
}

int ArbolDecision::getHoraInicio() const {
    return horaInicio;
}

int ArbolDecision::getHoraFin() const {
    return horaFin;
}


void ArbolDecision::construirArbol() {
    raiz = new NodoD(nullptr, std::to_string(montoLimite));
    raiz->hizq = new NodoD(nullptr, ubicacionSospechosa);
    raiz->hder = new NodoD(nullptr, ubicacionSospechosa);
    raiz->hizq->hizq = new NodoD(nullptr, "No Sospechoso");
    raiz->hizq->hder= new NodoD(nullptr, "Sospechoso (Ubicacion)");
    raiz->hder->hizq= new NodoD(nullptr, "Sospechoso (Monto)");
    raiz->hder->hder= new NodoD(nullptr, "Sospechoso (Ubicacion, Monto)");
}

void ArbolDecision::evaluarTransaccion(Transaccion* trans) {
    NodoD* nodoActual = raiz;

    if (trans->getMonto() < montoLimite) {
        nodoActual = nodoActual->hizq;
    } else {
        nodoActual = nodoActual->hder;
    }
    if (trans->getUbicacion() == nodoActual->criterio) {
        nodoActual = nodoActual->hizq;
    } else {
        nodoActual = nodoActual->hder;
    }
    if (nodoActual->hizq == nullptr && nodoActual->hder == nullptr) {
        trans->setEtiqueta(nodoActual->criterio);

        if (verificarHoraEnRango(trans->getFechayHora())) {
            if (trans->getEtiqueta() == "No Sospechoso") {
                trans->setEtiqueta("Sospechoso (Hora)");
            } else if (trans->getEtiqueta() == "Sospechoso (Ubicacion)") {
                trans->setEtiqueta("Sospechoso (Ubicacion, Hora)");
            } else if (trans->getEtiqueta() == "Sospechoso (Monto)") {
                trans->setEtiqueta("Sospechoso (Monto, Hora)");
            } else if (trans->getEtiqueta() == "Sospechoso (Ubicacion, Monto)") {
                trans->setEtiqueta("Sospechoso (Ubicacion, Monto, Hora)");
            }
        }
    }
}

bool ArbolDecision::verificarHoraEnRango(const string& hora) {
    int hora_inicio = 0;    
    int hora_fin = 6;      
    size_t pos_inicio = hora.find("[") + 1;   
    size_t pos_fin = hora.find(":");         
    string hora_str = hora.substr(pos_inicio, pos_fin - pos_inicio);
    int hora_actual = stoi(hora_str);
    if (hora_actual >= hora_inicio && hora_actual <= hora_fin) {
        return true;
    } else {
        return false;
    }
}



