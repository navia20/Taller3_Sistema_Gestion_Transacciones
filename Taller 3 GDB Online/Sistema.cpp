#include "Sistema.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> // "Uso de vector exclusivamente par definir partes de una linea al momento de leer archivo .txt"
#include <limits>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;
using std::cin;
Sistema::Sistema(){
    
    arbolTransacciones = new AVL();
    arbolDetector = new ArbolDecision();
}
void Sistema::menu (Sistema * sistema){
    leerArchivo("transacciones.txt");
    leerCriterios("criterios.txt");
    int opcion;
    do{
	  cout << "------ Menu ------" << endl;
	  cout << "1. Ingresar Transaccion" << endl;
	  cout << "2. Buscar Transaccion" << endl;
	  cout << "3. Modificar Transaccion" << endl;
	  cout << "4. Historial Transacciones" << endl;
	  cout << "5. Historial Transacciones Sospechosas" << endl;
	  cout << "6. Definir Criterios Transacciones Sospechosas" << endl;
	  cout << "7. Salir" << endl;
	  cout << "------------------" << endl;
	  cout << "Ingrese una opcion: ";
	  cin >> opcion;
	  if (cin.fail ()){
		  cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
		  cin.clear ();
		  cin.ignore (numeric_limits < streamsize >::max (), '\n');
		  continue;
	  }
	  switch (opcion){
		case 1:{
		    cout << "------ Ingresar Transaccion ------" << endl;
		    IngresarTransaccion();
			break;
		  }
		case 2:{
		    cout << "------ Buscar Transaccion ------" << endl;
		    buscarTransaccion();
		    
			break;
		  }
		case 3:{
		    cout << "------ Modificar Transaccion ------" << endl;
		    ModificarTransaccion();
			break;
		  }
		case 4:{
		    cout << "------ Historial Transacciones ------" << endl;
		    historialTransacciones();
			break;
		  }
		case 5:{
		    cout << "------ Historial Transacciones Sospechosas ------" << endl;
		    historialTransaccionesSospechosas();
		    break;
		    
		}
		case 6:{
		    cout <<"------ Definir Criterios Transacciones Sospechosas ------" << endl;
		    definirCriterios();
		    guardarCriterios("criterios.txt");
		    break;
		    
		}
		case 7:{
		    break;
		    
		}
		default:
		  {
			cout << "Opcion invalida. Intente de nuevo." << endl;
			break;
		  }
		}
	} while (opcion != 7);
    guardarTransacciones("transacciones.txt");
    guardarCriterios("criterios.txt");
}
void Sistema::leerArchivo(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "Error, no se ha encontrado el archivo." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> partes;
        string parte;
        while (getline(ss, parte, ';')) {
            partes.push_back(parte);
        }
        int id = stoi(partes[0]);
        string cuentaOrigen = partes[1];
        string cuentaDestino = partes[2];
        int monto = stoi(partes[3]);
        string ubicacion = partes[4];
        string fechayHora = partes[5];
        Transaccion* pTransaccion = new Transaccion(id, cuentaOrigen, cuentaDestino, monto, ubicacion, fechayHora);
        arbolDetector->construirArbol();
        arbolDetector->evaluarTransaccion(pTransaccion);
        arbolTransacciones->ingresar(pTransaccion); 
    }
    file.close(); 
}
void Sistema::guardarTransacciones(const string& archivo) {
    cout << "Guardando datos..." << endl;
    ofstream file(archivo);
    if (!file.is_open()) {
        cout << "Error: no se pudo abrir el archivo." << endl;
        return;
    }
    guardarTransaccionesRecursivo(file, arbolTransacciones->getRaiz());
    file.close();
}

void Sistema::guardarTransaccionesRecursivo(ofstream& file, Nodo* nodo) {
    if (!nodo) return;
    guardarTransaccionesRecursivo(file, nodo->izq);
    Transaccion* t = nodo->transaccion;
    file << t->getId() << ';' << t->getCuentaOrigen() << ';' << t->getCuentaDestino() << ';' << t->getMonto() << ';' << t->getUbicacion() << ';' << t->getFechayHora() << endl;
    guardarTransaccionesRecursivo(file, nodo->der);
}

void Sistema::IngresarTransaccion() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   
    int id;
    string cuentaOrigen;
    string cuentaDestino;
    int monto;
    string ubicacion;
    string fecha;
    string hora;
    string fechayHora;
    cout << "Ingrese la Cuenta Origen (12 caracteres): ";
    while (true) {
        getline(cin, cuentaOrigen);
        if (cuentaOrigen.length() != 12) {
            cout << "Error, la cuenta debe tener exactamente 12 caracteres. Ingrese nuevamente: ";
        } else {
            break;
        }
    }
    cout << "Ingrese la Cuenta Destino (12 caracteres): ";
    while (true) {
        getline(cin, cuentaDestino);
        if (cuentaDestino.length() != 12) {
            cout << "Error, la cuenta debe tener exactamente 12 caracteres. Ingrese nuevamente: ";
        } else {
            break;
        }
    }
    while (true) {
        cout << "Ingrese el Monto: ";
        if (!(cin >> monto)) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error, ingrese un valor numérico válido para el monto." << endl;
        } else {
            break;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

    cout << "Ingrese la Ubicación: ";
    getline(cin, ubicacion);
    for (char &c : ubicacion) {
        c = std::toupper(c);
    }
    cout << "Ingrese la Fecha (dd/mm/yyyy): ";
    getline(cin, fecha);

    cout << "Ingrese la Hora (hh:mm:ss): ";
    getline(cin, hora);
    fechayHora = "[" + hora + ", " + fecha + "]";
    id=arbolTransacciones->contarNodos() + 1;
    Transaccion* nuevaTrans = new Transaccion(id,cuentaOrigen,cuentaDestino,monto,ubicacion,fechayHora);
    arbolDetector->construirArbol();
    arbolDetector->evaluarTransaccion(nuevaTrans);
    arbolTransacciones->ingresar(nuevaTrans);
    cout << "Transaccion agregada exitosamente."<<endl;
}
void Sistema::buscarTransaccion() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int id;
    cout << "Ingrese ID de Transaccion: ";
    cin >> id;  
    Nodo* resultado = arbolTransacciones->buscar(id);
    if (resultado != NULL) {
        resultado->transaccion->imprimir();
    } else {
        cout << "Transacción no encontrada." << endl;
    }
}

void Sistema::historialTransaccionesSospechosas(){
    cout << "ID  Origen       Destino     Monto Ubicacion   Hora/Fecha        Etiqueta" << endl;
    arbolTransacciones->imprimirSospechosos();
    
}
void Sistema::historialTransacciones(){
    cout << "ID  Origen       Destino     Monto Ubicacion   Hora/Fecha        Etiqueta" << endl;
    arbolTransacciones->imprimir();
}
void Sistema::ModificarTransaccion() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int id;
    cout << "Ingrese ID de Transaccion: ";
    cin >> id;  
    Nodo* resultado = arbolTransacciones->buscar(id);
    if (resultado != nullptr) {
        cout << "Transacción encontrada. Seleccione el atributo a modificar:" << endl;
        cout << "1. Cuenta Origen" << endl;
        cout << "2. Cuenta Destino" << endl;
        cout << "3. Monto" << endl;
        cout << "4. Ubicación" << endl;
        cout << "5. Fecha y Hora" << endl;
        int opcion;
        cout << "Ingrese opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string nuevaCuentaOrigen;
                cout << "Ingrese la Cuenta Origen (12 caracteres): ";
                while (true) {
                    getline(cin, nuevaCuentaOrigen);
                    if (nuevaCuentaOrigen.length() != 12) {
                        cout << "Error, la cuenta debe tener exactamente 12 caracteres. Ingrese nuevamente: ";
                    } else {
                        break;
                    }
                }
                resultado->transaccion->setCuentaOrigen(nuevaCuentaOrigen);
                arbolDetector->construirArbol();
                arbolDetector->evaluarTransaccion(resultado->transaccion);
                break;
            }
            case 2: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string nuevaCuentaDestino;
                cout << "Ingrese la Cuenta Destino (12 caracteres): ";
                while (true) {
                    getline(cin, nuevaCuentaDestino);
                    if (nuevaCuentaDestino.length() != 12) {
                        cout << "Error, la cuenta debe tener exactamente 12 caracteres. Ingrese nuevamente: ";
                    } else {
                        break;
                    }
                }
                resultado->transaccion->setCuentaDestino(nuevaCuentaDestino);
                arbolDetector->construirArbol();
                arbolDetector->evaluarTransaccion(resultado->transaccion);
                break;
            }
            case 3: {
                double nuevoMonto;
                cout << "Ingrese el Monto: ";
                while (!(cin >> nuevoMonto)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error, ingrese un valor numérico válido para el monto." << endl;
                }
                resultado->transaccion->setMonto(nuevoMonto);
                arbolDetector->construirArbol();
                arbolDetector->evaluarTransaccion(resultado->transaccion);
                break;
            }
            case 4: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string nuevaUbicacion;
                cout << "Ingrese la Ubicación: ";
                getline(cin, nuevaUbicacion);
                for (char &c : nuevaUbicacion) {
                    c = std::toupper(c);
                }
                resultado->transaccion->setUbicacion(nuevaUbicacion);
                arbolDetector->construirArbol();
                arbolDetector->evaluarTransaccion(resultado->transaccion);
                break;
            }
            case 5: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string nuevaFecha;
                string nuevaHora;
                cout << "Ingrese la Fecha (dd/mm/yyyy): ";
                getline(cin, nuevaFecha);
                cout << "Ingrese la Hora (hh:mm:ss): ";
                getline(cin, nuevaHora);
                string nuevaFechaHora = "[" + nuevaHora + ", " + nuevaFecha + "]";
                resultado->transaccion->setFechayHora(nuevaFechaHora);
                arbolDetector->construirArbol();
                arbolDetector->evaluarTransaccion(resultado->transaccion);
                break;
            }
            default:
                cout << "Opción inválida." << endl;
                break;
        }
    } else {
        cout << "Transacción no encontrada." << endl;
    }
    cout << "Cambio realizado con exito." << endl;
}
void Sistema::leerCriterios(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "Error, no se ha encontrado el archivo de criterios." << endl;
        return;
    }

    int monto;
    string ubicacion;
    int horaInicio, horaFin;

    file >> monto;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar el salto de línea

    getline(file, ubicacion);
    file >> horaInicio;
    file >> horaFin;

    arbolDetector->actualizarCriterios(monto, ubicacion, horaInicio, horaFin);

    file.close();
}

void Sistema::guardarCriterios(const string& archivo) {
    ofstream file(archivo);
    if (!file.is_open()) {
        cout << "Error: no se pudo abrir el archivo de criterios." << endl;
        return;
    }
    file << arbolDetector->getMontoLimite() << endl;
    file << arbolDetector->getUbicacionSospechosa() << endl;
    file << arbolDetector->getHoraInicio() << endl;
    file << arbolDetector->getHoraFin() << endl;

    file.close();
}
void Sistema::definirCriterios() {
    int monto;
    string ubicacion;
    int horaInicio, horaFin;

    cout << "Ingrese el monto limite: ";
    cin >> monto;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer

    cout << "Ingrese la ubicacion sospechosa: ";
    getline(cin, ubicacion);

    cout << "Ingrese la hora de inicio: ";
    cin >> horaInicio;

    cout << "Ingrese la hora de fin: ";
    cin >> horaFin;

    arbolDetector->actualizarCriterios(monto, ubicacion, horaInicio, horaFin);
}
