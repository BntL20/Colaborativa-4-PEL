#include <iostream>
#include <string>

// ======================================================
// Lista enlazada genérica (plantilla propia)
// - NO usa vector, list, ni contenedores de la STL
// - Almacena datos de tipo T (en este proyecto, punteros)
// ======================================================

template <typename T>
class LinkedList {
private:
    // --------------------------------------------------
    // Clase interna Nodo: cada elemento de la lista
    // --------------------------------------------------
    class Nodo {
    public:
        T data;       // dato almacenado (puede ser un puntero)
        Nodo* next;   // puntero al siguiente nodo

        // Constructor por defecto
        Nodo() {
            data = T();        // valor por defecto del tipo T
            next = nullptr;    // siguiente nulo
        }

        // Constructor con dato
        Nodo(T e) {
            data = e;
            next = nullptr;
        }
    };

    // Puntero al primer nodo de la lista
    Nodo* first;
    // Puntero al último nodo de la lista
    Nodo* last;
    // Número de elementos en la lista
    int size;

public:
    // --------------------------------------------------
    // Constructor: crea una lista vacía
    // --------------------------------------------------
    LinkedList() {
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    // --------------------------------------------------
    // Destructor: libera todos los nodos
    // (NO borra el contenido de data si T es puntero)
    // --------------------------------------------------
    ~LinkedList() {
        limpiar();
    }

    // Indica si la lista está vacía
    bool estaVacia() {
        return size == 0;
    }

    // Devuelve cuántos elementos hay en la lista
    int getSize() {
        return size;
    }

    // --------------------------------------------------
    // Inserta un elemento al principio de la lista
    // --------------------------------------------------
    void insertar_cabeza(T e) {
        Nodo* nodo = new Nodo(e);

        if (first == nullptr) {
            // Lista vacía: el nuevo nodo es primero y último
            first = nodo;
            last = nodo;
        } else {
            // Lista no vacía: enganchamos delante del primero
            nodo->next = first;
            first = nodo;
        }

        size = size + 1;
    }

    // --------------------------------------------------
    // Inserta un elemento al final de la lista
    // --------------------------------------------------
    void insertar_cola(T e) {
        Nodo* nodo = new Nodo(e);

        if (first == nullptr) {
            // Lista vacía: el nuevo nodo es primero y último
            first = nodo;
            last = nodo;
        } else {
            // Lista no vacía: enganchamos detrás del último
            last->next = nodo;
            last = nodo;
        }

        size = size + 1;
    }

    // --------------------------------------------------
    // Inserta un elemento en la posición pos (0..size)
    // --------------------------------------------------
    void insert_at(T e, int pos) {
        if (pos >= 0 && pos <= size) {
            if (pos == 0) {
                // Insertar al principio
                insertar_cabeza(e);
            } else {
                if (pos == size) {
                    // Insertar al final
                    insertar_cola(e);
                } else {
                    // Insertar en posición intermedia
                    Nodo* nodo = new Nodo(e);
                    Nodo* index = first;
                    int i = 0;
                    // Avanzamos hasta el nodo anterior a "pos"
                    while (i < pos - 1) {
                        index = index->next;
                        i = i + 1;
                    }
                    // Ajustamos punteros para insertar en medio
                    nodo->next = index->next;
                    index->next = nodo;
                    size = size + 1;
                }
            }
        } else {
            std::cout << "No se puede insertar. Posición no disponible" << std::endl;
        }
    }

    // --------------------------------------------------
    // Extrae (elimina) el primer elemento y lo devuelve
    // --------------------------------------------------
    T extraer_cabeza() {
        if (first == nullptr) {
            std::cout << "Lista vacía, no se puede extraer" << std::endl;
            return T();
        }

        // Guardamos el nodo a borrar y el dato
        Nodo* n_aux = first;
        T aux = n_aux->data;

        // Avanzamos el primer nodo
        first = n_aux->next;

        // Si ya no quedan nodos, actualizamos last
        if (first == nullptr) {
            last = nullptr;
        }

        // Borramos el nodo
        delete n_aux;
        size = size - 1;

        return aux;
    }

    // --------------------------------------------------
    // Extrae (elimina) el último elemento y lo devuelve
    // --------------------------------------------------
    T extraer_cola() {
        if (first == nullptr) {
            std::cout << "Lista vacía, no se puede extraer" << std::endl;
            return T();
        }

        // Caso de un solo elemento
        if (first == last) {
            T aux = first->data;
            delete first;
            first = nullptr;
            last = nullptr;
            size = 0;
            return aux;
        }

        // Caso general: buscamos el nodo anterior al último
        Nodo* anterior = first;
        while (anterior->next != last) {
            anterior = anterior->next;
        }

        T aux = last->data;
        delete last;
        last = anterior;
        last->next = nullptr;
        size = size - 1;

        return aux;
    }

    // --------------------------------------------------
    // Extrae y devuelve el elemento de la posición pos
    // --------------------------------------------------
    T extract_at(int pos) {
        if (first == nullptr) {
            std::cout << "Lista vacía, no se puede extraer" << std::endl;
            return T();
        }

        if (pos < 0 || pos >= size) {
            std::cout << "Posición no válida" << std::endl;
            return T();
        }

        if (pos == 0) {
            return extraer_cabeza();
        }

        if (pos == size - 1) {
            return extraer_cola();
        }

        // Buscamos el nodo anterior al que queremos borrar
        Nodo* anterior = first;
        int i = 0;
        while (i < pos - 1) {
            anterior = anterior->next;
            i = i + 1;
        }

        // Nodo que queremos borrar
        Nodo* borrar = anterior->next;
        T aux = borrar->data;

        // Saltamos el nodo a borrar
        anterior->next = borrar->next;
        delete borrar;

        size = size - 1;
        return aux;
    }

    // --------------------------------------------------
    // Devuelve el dato de la posición pos (sin borrar)
    // --------------------------------------------------
    T obtener_en(int pos) {
        if (pos < 0 || pos >= size) {
            std::cout << "Posición no válida" << std::endl;
            return T();
        }

        Nodo* actual = first;
        int i = 0;
        while (i < pos) {
            actual = actual->next;
            i = i + 1;
        }

        return actual->data;
    }

    // --------------------------------------------------
    // Elimina todos los nodos de la lista
    // --------------------------------------------------
    void limpiar() {
        Nodo* actual = first;

        while (actual != nullptr) {
            Nodo* siguiente = actual->next;
            delete actual;
            actual = siguiente;
        }

        first = nullptr;
        last = nullptr;
        size = 0;
    }
};

// ======================================================
// Clase Contacto: representa un contacto de un perfil
// ======================================================

class Contacto {
private:
    std::string nombre;
    std::string telefono;
    int edad;
    std::string ciudad;
    std::string descripcion;

public:
    // Constructor por defecto (contacto vacío)
    Contacto() {
        nombre = "";
        telefono = "";
        edad = 0;
        ciudad = "";
        descripcion = "";
    }

    // Constructor con parámetros (crea un contacto completo)
    Contacto(std::string n, std::string t, int e, std::string c, std::string d) {
        nombre = n;
        telefono = t;
        edad = e;
        ciudad = c;
        descripcion = d;
    }

    // Getters y setters básicos
    std::string getNombre() {
        return nombre;
    }

    void setNombre(std::string n) {
        nombre = n;
    }

    std::string getTelefono() {
        return telefono;
    }

    void setTelefono(std::string t) {
        telefono = t;
    }

    int getEdad() {
        return edad;
    }

    void setEdad(int e) {
        edad = e;
    }

    std::string getCiudad() {
        return ciudad;
    }

    void setCiudad(std::string c) {
        ciudad = c;
    }

    std::string getDescripcion() {
        return descripcion;
    }

    void setDescripcion(std::string d) {
        descripcion = d;
    }
};

// ======================================================
// Clase Perfil: representa un usuario de la "app"
// Cada perfil tiene su propia lista enlazada de contactos
// (lista guardada como puntero, para usar siempre ->)
// ======================================================

class Perfil {
private:
    std::string nombreUsuario;             // nombre del perfil
    std::string descripcion;               // descripción del perfil
    LinkedList<Contacto*>* contactos;      // puntero a lista enlazada de contactos

public:
    // Constructor por defecto
    Perfil() {
        nombreUsuario = "";
        descripcion = "";
        // Creamos la lista de contactos en el montón
        contactos = new LinkedList<Contacto*>();
    }

    // Constructor con parámetros
    Perfil(std::string nombre, std::string texto) {
        nombreUsuario = nombre;
        descripcion = texto;
        contactos = new LinkedList<Contacto*>();
    }

    // Destructor: podría liberar contactos y lista.
    // En esta práctica no lo usamos en main, pero queda definido.
    ~Perfil() {
        // Si tu profe no quiere destructores, puedes comentar este bloque entero
        if (contactos != nullptr) {
            int total = contactos->getSize();
            int i = 0;
            // Borramos cada Contacto* almacenado en la lista
            while (i < total) {
                Contacto* c = contactos->obtener_en(i);
                if (c != nullptr) {
                    delete c;
                }
                i = i + 1;
            }
            // Vaciamos nodos de la lista
            contactos->limpiar();
            // Borramos la propia lista
            delete contactos;
            contactos = nullptr;
        }
    }

    // Getters y setters del perfil
    std::string getNombreUsuario() {
        return nombreUsuario;
    }

    void setNombreUsuario(std::string nombre) {
        nombreUsuario = nombre;
    }

    std::string getDescripcion() {
        return descripcion;
    }

    void setDescripcion(std::string texto) {
        descripcion = texto;
    }

    // Devuelve cuántos contactos tiene el perfil
    int getNumeroContactos() {
        return contactos->getSize();
    }

    // Devuelve el puntero al contacto en una posición
    Contacto* getContactoEn(int posicion) {
        Contacto* puntero = contactos->obtener_en(posicion);
        return puntero;
    }

    // Añade un contacto al final de la lista
    void aniadirContactoFinal(Contacto* contacto) {
        contactos->insertar_cola(contacto);
    }

    // --------------------------------------------------
    // Comprueba si ya existe un contacto con ese teléfono
    // (se usa para evitar duplicados al importar)
    // --------------------------------------------------
    bool existeTelefono(std::string telefono) {
        int total = contactos->getSize();
        int i = 0;

        while (i < total) {
            Contacto* c = contactos->obtener_en(i);
            if (c != nullptr) {
                if (c->getTelefono() == telefono) {
                    return true;
                }
            }
            i = i + 1;
        }

        return false;
    }

    // --------------------------------------------------
    // Importa contactos desde otro perfil
    // - Recorre los contactos del perfil origen
    // - Copia solo los que no tengan teléfono repetido
    // --------------------------------------------------
    void importarContactosDesde(Perfil* origen) {
        if (origen != nullptr) {
            int total = origen->getNumeroContactos();
            int importados = 0;
            int duplicados = 0;
            int i = 0;

            while (i < total) {
                Contacto* original = origen->getContactoEn(i);
                if (original != nullptr) {
                    std::string telefono = original->getTelefono();
                    bool existe = existeTelefono(telefono);
                    if (!existe) {
                        // Creamos una copia del contacto original
                        Contacto* copia = new Contacto(original->getNombre(),original->getTelefono(),original->getEdad(),original->getCiudad(),original->getDescripcion());
                        // Añadimos la copia a este perfil (destino)
                        aniadirContactoFinal(copia);
                        importados = importados + 1;
                    } else {
                        // Teléfono repetido → se cuenta como duplicado
                        duplicados = duplicados + 1;
                    }
                }
                i = i + 1;
            }

            // Mensajes informativos
            std::cout << "Se han importado " << importados
                      << " contactos desde el perfil \"" << origen->getNombreUsuario()
                      << "\" al perfil \"" << nombreUsuario << "\"." << std::endl;

            if (duplicados > 0) {
                std::cout << "Se han omitido " << duplicados
                          << " contactos por tener el mismo número de teléfono en el perfil destino."
                          << std::endl;
            }
        }
    }

    // --------------------------------------------------
    // Busca teléfonos repetidos dentro del mismo perfil
    // y los muestra por pantalla
    // --------------------------------------------------
    void detectarContactosDuplicados() {
        int total = contactos->getSize();
        bool hayDuplicados = false;
        int i = 0;

        // Doble bucle para comparar cada contacto con los demás
        while (i < total) {
            Contacto* primero = contactos->obtener_en(i);
            if (primero != nullptr) {
                int j = i + 1;
                while (j < total) {
                    Contacto* segundo = contactos->obtener_en(j);
                    if (segundo != nullptr) {
                        if (primero->getTelefono() == segundo->getTelefono()) {
                            if (!hayDuplicados) {
                                std::cout << "Contactos duplicados en el perfil \""
                                          << nombreUsuario << "\":" << std::endl;
                                hayDuplicados = true;
                            }
                            std::cout << "- " << primero->getNombre()
                                      << " y " << segundo->getNombre()
                                      << " comparten el teléfono "
                                      << primero->getTelefono() << std::endl;
                        }
                    }
                    j = j + 1;
                }
            }
            i = i + 1;
        }

        if (!hayDuplicados) {
            std::cout << "No hay contactos duplicados en el perfil \""
                      << nombreUsuario << "\"." << std::endl;
        }
    }
};

// ------------------------------------------------------
// Función libre: exporta contactos de un perfil a otro
// (internamente usa importarContactosDesde del destino)
// ------------------------------------------------------

void exportarContactos(Perfil* origen, Perfil* destino) {
    if (origen != nullptr && destino != nullptr) {
        destino->importarContactosDesde(origen);
    }
}

// ------------------------------------------------------
// Carga inicial de perfiles
// - Recibe un puntero a LinkedList<Perfil*>
// - Crea 3 perfiles con al menos 5 contactos cada uno
// - Inserta los perfiles en la lista con ->insertar_cola
// ------------------------------------------------------

void inicializarPerfiles(LinkedList<Perfil*>* listaPerfiles) {
    // ---------- Perfil 1 ----------
    Perfil* p1 = new Perfil("ana", "Le gusta la música y viajar");
    p1->aniadirContactoFinal(new Contacto("Carlos",  "111111111", 25, "Madrid",   "Amigo de la universidad"));
    p1->aniadirContactoFinal(new Contacto("Lucía",   "222222222", 23, "Valencia", "Compañera de trabajo"));
    p1->aniadirContactoFinal(new Contacto("Miguel",  "333333333", 28, "Sevilla",  "Conocido del gimnasio"));
    p1->aniadirContactoFinal(new Contacto("Sofía",   "444444444", 24, "Bilbao",   "Amiga de la infancia"));
    p1->aniadirContactoFinal(new Contacto("Raúl",    "555555555", 29, "Zaragoza", "Contacto de un viaje"));

    // ---------- Perfil 2 ----------
    Perfil* p2 = new Perfil("borja", "Aficionado al deporte y al cine");
    p2->aniadirContactoFinal(new Contacto("Irene",   "666666666", 26, "Madrid",    "Compañera de clase"));
    p2->aniadirContactoFinal(new Contacto("Diego",   "777777777", 30, "Barcelona", "Amigo de fiestas"));
    p2->aniadirContactoFinal(new Contacto("Natalia", "888888888", 27, "Granada",   "Amiga de Erasmus"));
    p2->aniadirContactoFinal(new Contacto("Pedro",   "999999999", 31, "Málaga",    "Conocido del trabajo"));
    p2->aniadirContactoFinal(new Contacto("Laura",   "101010101", 22, "Valladolid","Amiga del gimnasio"));

    // ---------- Perfil 3 ----------
    Perfil* p3 = new Perfil("carla", "Le encantan los videojuegos y la tecnología");
    p3->aniadirContactoFinal(new Contacto("Javier",   "202020202", 24, "Madrid",   "Amigo de instituto"));
    p3->aniadirContactoFinal(new Contacto("Patricia", "303030303", 29, "Valencia", "Compañera de piso"));
    p3->aniadirContactoFinal(new Contacto("Hugo",     "404040404", 27, "A Coruña", "Amigo de vacaciones"));
    p3->aniadirContactoFinal(new Contacto("Elena",    "505050505", 25, "Murcia",   "Conocida de un curso"));
    p3->aniadirContactoFinal(new Contacto("Sergio",   "606060606", 28, "Oviedo",   "Amigo de la universidad"));

    // Insertamos los perfiles en la lista usando puntero y ->
    listaPerfiles->insertar_cola(p1);
    listaPerfiles->insertar_cola(p2);
    listaPerfiles->insertar_cola(p3);
}

// ------------------------------------------------------
// main mínimo del BLOQUE A
// - Crea la lista de perfiles como puntero
// - Llama a inicializarPerfiles con puntero
// ------------------------------------------------------

int main() {
    // Creamos la lista principal de perfiles como puntero
    LinkedList<Perfil*>* perfiles;
    perfiles = new LinkedList<Perfil*>();

    // Cargamos los 3 perfiles iniciales con sus contactos
    inicializarPerfiles(perfiles);

    std::cout << "Perfiles iniciales cargados correctamente." << std::endl;

    return 0;
}
