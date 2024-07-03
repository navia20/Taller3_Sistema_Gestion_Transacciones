#include "AVL.h"


AVL::AVL() : raiz(NULL) {}

AVL::~AVL() {
    destruir(raiz);
}

void AVL::destruir(Nodo* nodo) {
    if (nodo) {
        destruir(nodo->izq);
        destruir(nodo->der);
        delete nodo->transaccion;
        delete nodo;
    }
}

int AVL::mayor(int a, int b) {
    return (a > b) ? a : b;
}

int AVL::getAltura(Nodo* nodo) {
    if (!nodo) return 0;
    return nodo->altura;
}

void AVL::actualizarAltura(Nodo* nodo) {
    if (nodo) {
        int alturaIzq = getAltura(nodo->izq);
        int alturaDer = getAltura(nodo->der);
        nodo->altura = 1 + mayor(alturaIzq, alturaDer);
    }
}

int AVL::getBalance(Nodo* nodo) {
    if (!nodo) return 0;
    return getAltura(nodo->izq) - getAltura(nodo->der);
}

Nodo* AVL::getSucesor(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual && actual->izq) {
        actual = actual->izq;
    }
    return actual;
}

Nodo* AVL::ll(Nodo* nodo) {
    Nodo* hDer = nodo->der;
    Nodo* hDerI = hDer->izq;
    hDer->izq = nodo;
    nodo->der = hDerI;
    actualizarAltura(nodo);
    actualizarAltura(hDer);
    return hDer;
}

Nodo* AVL::rr(Nodo* nodo) {
    Nodo* hIzq = nodo->izq;
    Nodo* hIzqD = hIzq->der;
    hIzq->der = nodo;
    nodo->izq = hIzqD;
    actualizarAltura(nodo);
    actualizarAltura(hIzq);
    return hIzq;
}

Nodo* AVL::ingresarNodo(Nodo* nodo, Nodo* nuevoNodo) {
    if (nodo == NULL) {
        return nuevoNodo;
    }
    if (nodo->transaccion->getId() > nuevoNodo->transaccion->getId()) {
        nodo->izq = ingresarNodo(nodo->izq, nuevoNodo);
    } else if (nodo->transaccion->getId() < nuevoNodo->transaccion->getId()) {
        nodo->der = ingresarNodo(nodo->der, nuevoNodo);
    } else {
        return nodo;
    }
    actualizarAltura(nodo);
    int factorBalanceo = getBalance(nodo);
    if (factorBalanceo > 1 && nodo->izq->transaccion->getId() > nuevoNodo->transaccion->getId()) {
        return rr(nodo);
    } else if (factorBalanceo < -1 && nodo->der->transaccion->getId() < nuevoNodo->transaccion->getId()) {
        return ll(nodo);
    } else if (factorBalanceo > 1 && nodo->izq->transaccion->getId() < nuevoNodo->transaccion->getId()) {
        nodo->izq = ll(nodo->izq);
        return rr(nodo);
    } else if (factorBalanceo < -1 && nodo->der->transaccion->getId() > nuevoNodo->transaccion->getId()) {
        nodo->der = rr(nodo->der);
        return ll(nodo);
    }
    return nodo;
}

void AVL::ingresar(Transaccion* transaccion) {
    Nodo* nuevoNodo = new Nodo(transaccion);
    raiz = ingresarNodo(raiz, nuevoNodo);
}

Nodo* AVL::buscarNodo(Nodo* nodo, int id) {
    if (!nodo) return NULL;
    if (nodo->transaccion->getId() == id) return nodo;
    if (nodo->transaccion->getId() > id) return buscarNodo(nodo->izq, id);
    if (nodo->transaccion->getId() < id) return buscarNodo(nodo->der, id);
    return NULL;
}

Nodo* AVL::buscar(int id) { 
    return buscarNodo(raiz, id);
}

Nodo* AVL::eliminarNodo(Nodo* nodo, int id) {
    if (!nodo) return NULL;
    if (nodo->transaccion->getId() < id) nodo->der = eliminarNodo(nodo->der, id);
    else if (nodo->transaccion->getId() > id) nodo->izq = eliminarNodo(nodo->izq, id);
    else {
        if (!nodo->izq) {
            Nodo* hijo = nodo->der;
            delete nodo->transaccion;
            delete nodo;
            return hijo;
        } else if (!nodo->der) {
            Nodo* hijo = nodo->izq;
            delete nodo->transaccion;
            delete nodo;
            return hijo;
        }
        Nodo* sucesor = getSucesor(nodo->der);
        nodo->transaccion = sucesor->transaccion;
        nodo->der = eliminarNodo(nodo->der, sucesor->transaccion->getId());
    }
    if (!nodo) {
        return nodo;
    }
    actualizarAltura(nodo);
    int factorBalanceo = getBalance(nodo);
    if (factorBalanceo > 1 && getBalance(nodo->izq) >= 0) {
        return rr(nodo);
    } else if (factorBalanceo < -1 && getBalance(nodo->der) <= 0) {
        return ll(nodo);
    } else if (factorBalanceo > 1 && getBalance(nodo->izq) < 0) {
        nodo->izq = ll(nodo->izq);
        return rr(nodo);
    } else if (factorBalanceo < -1 && getBalance(nodo->der) > 0) {
        nodo->der = rr(nodo->der);
        return ll(nodo);
    }
    return nodo;
}

void AVL::eliminar(int id) {
    raiz = eliminarNodo(raiz, id);
}

bool AVL::eliminarRaiz() {
    if (raiz != NULL) {
        cout << "ID: " << to_string(raiz->transaccion->getId()) << endl;
        cout << "Se elimina la transacción de la cuenta: " << raiz->transaccion->getCuentaOrigen() << endl;
        eliminar(raiz->transaccion->getId());
        return true;
    }
    return false;
}

Nodo* AVL::getRaiz() {
    return raiz;
}

void AVL::imprimirInOrden(Nodo* nodo) {
    if (nodo != NULL) {
        imprimirInOrden(nodo->izq); 
        nodo->transaccion->catalogo(); 
        imprimirInOrden(nodo->der); 
    }
}

void AVL::imprimir() {
    imprimirInOrden(raiz);
}


void AVL::imprimirInOrdenSus(Nodo* nodo){
    if (nodo != NULL) {
        imprimirInOrdenSus(nodo->izq); 
        if(nodo->transaccion->getEtiqueta()!="No Sospechoso"){
        nodo->transaccion->catalogo(); 
        }
        imprimirInOrdenSus(nodo->der); 
    }
}



void AVL::imprimirSospechosos(){
    imprimirInOrdenSus(raiz);
}



int AVL::contarNodos(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return 1 + contarNodos(nodo->izq) + contarNodos(nodo->der);
}

int AVL::contarNodos() {
    return contarNodos(raiz);
}