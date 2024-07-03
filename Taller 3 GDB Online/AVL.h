#pragma once
#include "Transaccion.h"
#include <iostream>

class Nodo {
public:
    Transaccion* transaccion;
    Nodo* izq;
    Nodo* der;
    int altura;

    Nodo(Transaccion* trans) : transaccion(trans), izq(NULL), der(NULL), altura(1) {}
};

class AVL {
public:
     /**
     * Constructor de la clase AVL
     */
    AVL();

    /**
     * Destructor de la clase AVL
     */
    ~AVL();

    /**
     * Metodo para ingresar una nueva transacción en el árbol AVL
     * @param transaccion Puntero a la transacción
     */
    void ingresar(Transaccion* transaccion);

    /**
     * Metodo para buscar una transacción en el árbol AVL por su ID
     * @param id ID de la transacción
     * @return Puntero al nodo que contiene la transacción
     */
    Nodo* buscar(int id);

    /**
     * Metodo para eliminar una transacción del árbol AVL por su ID
     * @param id ID de la transacción
     */
    void eliminar(int id);

    /**
     * Metodo para eliminar la raíz del árbol AVL
     * @return Verdadero si se eliminó la raíz, falso si no
     */
    bool eliminarRaiz();

    /**
     * Metodo para obtener la raíz del árbol AVL
     * @return Puntero a la raíz del árbol
     */
    Nodo* getRaiz();

    /**
     * Metodo para imprimir todas las transacciones en el árbol AVL
     */
    void imprimir();

    /**
     * Metodo para contar el número de nodos en el árbol AVL
     * @return Número de nodos en el árbol
     */
    int contarNodos();

    /**
     * Metodo para imprimir las transacciones sospechosas en el árbol AVL
     */
    void imprimirSospechosos();

private:
    Nodo* raiz;

    /**
     * Metodo para destruir recursivamente los nodos del árbol AVL
     * @param nodo Nodo actual del árbol
     */
    void destruir(Nodo* nodo);

    /**
     * Metodo para devolver el mayor de dos enteros
     * @param a Primer entero
     * @param b Segundo entero
     * @return El mayor de los dos enteros
     */
    int mayor(int a, int b);

    /**
     * Metodo para obtener la altura de un nodo
     * @param nodo Nodo actual
     * @return Altura del nodo
     */
    int getAltura(Nodo* nodo);

    /**
     * Metodo para actualizar la altura de un nodo
     * @param nodo Nodo actual
     */
    void actualizarAltura(Nodo* nodo);

    /**
     * Metodo para obtener el balance de un nodo
     * @param nodo Nodo actual
     * @return Balance del nodo
     */
    int getBalance(Nodo* nodo);

    /**
     * Metodo para obtener el sucesor en el árbol AVL
     * @param nodo Nodo actual
     * @return Puntero al sucesor del nodo
     */
    Nodo* getSucesor(Nodo* nodo);

    /**
     * Metodo para realizar una rotación simple a la izquierda
     * @param nodo Nodo actual
     * @return Puntero al nodo rotado
     */
    Nodo* ll(Nodo* nodo);

    /**
     * Metodo para realizar una rotación simple a la derecha
     * @param nodo Nodo actual
     * @return Puntero al nodo rotado
     */
    Nodo* rr(Nodo* nodo);

    /**
     * Metodo para insertar un nuevo nodo en el árbol AVL
     * @param nodo Nodo actual del árbol
     * @param nuevoNodo Nuevo nodo a insertar
     * @return Puntero al nodo insertado
     */
    Nodo* ingresarNodo(Nodo* nodo, Nodo* nuevoNodo);

    /**
     * Metodo para buscar un nodo en el árbol AVL
     * @param nodo Nodo actual del árbol
     * @param id ID de la transacción a buscar
     * @return Puntero al nodo que contiene la transacción
     */
    Nodo* buscarNodo(Nodo* nodo, int id);

    /**
     * Metodo para eliminar un nodo del árbol AVL
     * @param nodo Nodo actual del árbol
     * @param id ID de la transacción a eliminar
     * @return Puntero al nodo eliminado
     */
    Nodo* eliminarNodo(Nodo* nodo, int id);

    /**
     * Metodo para imprimir en orden los nodos del árbol AVL
     * @param nodo Nodo actual del árbol
     */
    void imprimirInOrden(Nodo* nodo);

    /**
     * Metodo para imprimir en orden las transacciones sospechosas
     * @param nodo Nodo actual del árbol
     */
    void imprimirInOrdenSus(Nodo* nodo);

    /**
     * Metodo para contar los nodos del árbol AVL recursivamente
     * @param nodo Nodo actual del árbol
     * @return Número de nodos en el árbol
     */
    int contarNodos(Nodo* nodo);
};
