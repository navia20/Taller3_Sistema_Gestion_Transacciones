#pragma once
#include <iostream>
#include "Transaccion.h"
#include "AVL.h"
#include "ArbolDecision.h"
using namespace std;

class Sistema {
private:
    AVL* arbolTransacciones;
    ArbolDecision* arbolDetector;

    /**
     * Metodo para leer las transacciones desde un archivo .txt
     * @param archivo Nombre del archivo
     */
    void leerArchivo(const string& archivo);

    /**
     * Metodo para guardar todas las transacciones en un archivo .txt
     * @param archivo Nombre del archivo
     */
    void guardarTransacciones(const string& archivo);

    /**
     * Metodo auxiliar para guardar transacciones recursivamente en un archivo .txt
     * @param file Archivo de salida
     * @param nodo Nodo actual del árbol
     */
    void guardarTransaccionesRecursivo(ofstream& file, Nodo* nodo);

    /**
     * Metodo para ingresar una nueva transacción al sistema
     */
    void IngresarTransaccion();

    /**
     * Metodo para buscar una transacción en el sistema
     */
    void buscarTransaccion();

    /**
     * Metodo para mostrar el historial de transacciones sospechosas
     */
    void historialTransaccionesSospechosas();

    /**
     * Metodo para mostrar el historial de todas las transacciones
     */
    void historialTransacciones();

    /**
     * Metodo para modificar una transacción existente
     */
    void ModificarTransaccion();

    /**
     * Metodo para leer los criterios de evaluación desde un archivo .txt
     * @param archivo Nombre del archivo
     */
    void leerCriterios(const string& archivo);

    /**
     * Metodo para guardar los criterios de evaluación en un archivo .txt
     * @param archivo Nombre del archivo
     */
    void guardarCriterios(const string& archivo);

    /**
     * Metodo para definir los criterios de evaluación de transacciones sospechosas
     */
    void definirCriterios();

public:
    /**
     * Constructor de la clase Sistema
     */
    Sistema();

    /**
     * Metodo para mostrar el menú principal del sistema
     * @param sistema Puntero al sistema
     */
    void menu(Sistema* sistema);
};
