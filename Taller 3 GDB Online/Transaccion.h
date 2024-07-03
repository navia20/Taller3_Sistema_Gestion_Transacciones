#pragma once
#include <string>
using namespace std;

class Transaccion {
private:
    int id;
    string cuentaOrigen;
    string cuentaDestino;
    int monto;
    string ubicacion;
    string fechayHora;
    string etiqueta;

public:
    // Constructor
    Transaccion(int id, string cuentaOrigen, string cuentaDestino, int monto, string ubicacion, string fechayHora);
    
    // Setters
    void setId(int id);
    void setCuentaOrigen(string cuentaOrigen);
    void setCuentaDestino(string cuentaDestino);
    void setMonto(int monto);
    void setUbicacion(string ubicacion);
    void setFechayHora(string fechayHora);
    void setEtiqueta(string etiqueta);

    // Getters
    int getId();
    string getCuentaOrigen();
    string getCuentaDestino();
    int getMonto();
    string getUbicacion();
    string getFechayHora();
    string getEtiqueta();
    void imprimir();
    void catalogo();
};

