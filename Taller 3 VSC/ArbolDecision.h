#include "AVL.cpp"
#include <iostream>
#include <string>
#pragma once
using namespace std;

struct NodoD {
    Transaccion* trans;
    string criterio;
    NodoD* hder;
    NodoD* hizq;

    /**
     * Constructor de NodoD.
     * @param tra Puntero a la transacción asociada al nodo.
     * @param criterio Criterio asociado al nodo.
     */
    NodoD(Transaccion* tra, string criterio)
        : trans(tra), criterio(criterio), hder(nullptr), hizq(nullptr) {}
};

class ArbolDecision {
private:
    NodoD* raiz;
    int montoLimite;
    string ubicacionSospechosa;
    int horaInicio;
    int horaFin;

public:
    /**
     * Constructor de ArbolDecision.
     * Inicializa el árbol de decisión con valores predeterminados.
     */
    ArbolDecision();

    /**
     * Método para construir el árbol de decisión con nodos predefinidos.
     */
    void construirArbol();

    /**
     * Evalúa una transacción según los criterios definidos en el árbol de decisión.
     * @param trans Puntero a la transacción a evaluar.
     */
    void evaluarTransaccion(Transaccion* trans);

    /**
     * Verifica si la hora especificada está dentro del rango permitido.
     * @param hora Cadena que representa la hora en formato "[hh:mm:ss]".
     * @return true si la hora está dentro del rango permitido, false de lo contrario.
     */
    bool verificarHoraEnRango(const string& hora);

    /**
     * Actualiza los criterios del árbol de decisión.
     * @param monto Nuevo límite de monto para considerar una transacción sospechosa.
     * @param ubicacion Nueva ubicación sospechosa para considerar una transacción sospechosa.
     * @param horaInicio Nueva hora de inicio del rango sospechoso.
     * @param horaFin Nueva hora de fin del rango sospechoso.
     */
    void actualizarCriterios(int monto, const string& ubicacion, int horaInicio, int horaFin);

    /**
     * Obtiene el monto límite actual para considerar una transacción sospechosa.
     * @return El monto límite.
     */
    int getMontoLimite() const;

    /**
     * Obtiene la ubicación sospechosa actual para considerar una transacción sospechosa.
     * @return La ubicación sospechosa.
     */
    string getUbicacionSospechosa() const;

    /**
     * Obtiene la hora de inicio actual del rango sospechoso.
     * @return La hora de inicio.
     */
    int getHoraInicio() const;

    /**
     * Obtiene la hora de fin actual del rango sospechoso.
     * @return La hora de fin.
     */
    int getHoraFin() const;
};