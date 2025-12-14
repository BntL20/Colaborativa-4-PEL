/*
* Proyecto : Enlistando perfiles con listas enlazadas
 * Asignatura: Programación con estructuras lineales
 * Descripción:
 *   Aplicación de consola que simula una agenda de contactos con varios
 *   perfiles de usuario. Cada perfil tiene su propia lista de contactos,
 *   donde se guarda nombre, teléfono, edad, ciudad y una breve descripción.
 *
 *   El programa permite:
 *     - Mostrar los perfiles disponibles e iniciar sesión en uno de ellos.
 *     - Consultar, añadir, modificar y eliminar contactos de un perfil.
 *     - Importar contactos desde otro perfil evitando teléfonos duplicados.
 *     - Exportar los contactos de un perfil a otro.
 *     - Detectar contactos duplicados dentro de un mismo perfil.
 *
 *   Todas las estructuras de datos se han implementado usando únicamente
 *   punteros y una lista enlazada propia (plantilla LinkedList<T>), sin
 *   utilizar contenedores estándar de C++ como vector o list. Perfiles y
 *   contactos se crean dinámicamente con new y se gestionan mediante punteros.
 *
 * Autor/es:  Brent Delgado Ravichagua, Lucía Sánchez Grande
 * Grupo    : Grupo 5
 * Fecha    : 14/12/2025
 */

#include <iostream>
#include <string>

// Lista enlazada genérica
template <typename T>
class LinkedList {
private:
    // Clase interna Nodo: cada elemento de la lista
    class Nodo {
    public:
        T data;       // dato almacenado
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
    // Constructor: crea una lista vacía
    LinkedList() {
        first = nullptr;
        last = nullptr;
        size = 0;
    }

    // Destructor: libera todos los nodos
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

    // Inserta un elemento al principio de la lista
    void insertar_cabeza(T e) {
        Nodo* nodo = new Nodo(e);

        if (first == nullptr) {
            // Lista vacía: el nuevo nodo es primero y último
            first = nodo;
            last = nodo;
        } else {
            // Lista no vacía: insertamos delante del primero
            nodo->next = first;
            first = nodo;
        }

        size = size + 1;
    }

    // Inserta un elemento al final de la lista
    void insertar_cola(T e) {
        Nodo* nodo = new Nodo(e);

        if (first == nullptr) {
            // Lista vacía: el nuevo nodo es primero y último
            first = nodo;
            last = nodo;
        } else {
            // Lista no vacía: insertamos detrás del último
            last->next = nodo;
            last = nodo;
        }

        size = size + 1;
    }

    // Inserta un elemento en la posición pos
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
            std::cout << "No se puede insertar. Posicion no disponible" << std::endl;
        }
    }

    // Extrae (elimina) el primer elemento y lo devuelve
    T extraer_cabeza() {
        if (first == nullptr) {
            std::cout << "Lista vacia, no se puede extraer" << std::endl;
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

    // Extrae (elimina) el último elemento y lo devuelve
    T extraer_cola() {
        if (first == nullptr) {
            std::cout << "Lista vacia, no se puede extraer" << std::endl;
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

    // Extrae y devuelve el elemento de la posición pos
    T extract_at(int pos) {
        if (first == nullptr) {
            std::cout << "Lista vacia, no se puede extraer" << std::endl;
            return T();
        }

        if (pos < 0 || pos >= size) {
            std::cout << "Posicion no valida" << std::endl;
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

    // Devuelve el dato de la posición pos (sin borrar)
    T obtener_en(int pos) {
        if (pos < 0 || pos >= size) {
            std::cout << "Posicion no valida" << std::endl;
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

    // Elimina todos los nodos de la lista
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


// Clase Contacto: representa un contacto de un perfil
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

// Clase Perfil: representa un usuario de la "app"
// Cada perfil tiene su propia lista enlazada de contactos
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
        // Creamos la lista de contactos
        contactos = new LinkedList<Contacto*>();
    }

    // Constructor con parámetros
    Perfil(std::string nombre, std::string texto) {
        nombreUsuario = nombre;
        descripcion = texto;
        contactos = new LinkedList<Contacto*>();
    }

    // Destructor: podría liberar contactos y lista.
    ~Perfil() {
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
    void agregarContactoFinal(Contacto* contacto) {
        contactos->insertar_cola(contacto);
    }

    // Comprueba si ya existe un contacto con ese teléfono
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

    // Importa contactos desde otro perfil (omito comentarios largos)
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
                        // Creamos copia
                        Contacto* copia = new Contacto(original->getNombre(),original->getTelefono(),original->getEdad(),original->getCiudad(),original->getDescripcion());
                        agregarContactoFinal(copia);
                        importados++;
                    } else {
                        duplicados++;
                    }
                }
                i++;
            }

            std::cout << "Se han importado " << importados
                      << " contactos desde el perfil \"" << origen->getNombreUsuario()
                      << "\" al perfil \"" << nombreUsuario << "\"." << std::endl;

            if (duplicados > 0) {
                std::cout << "Se han omitido " << duplicados
                          << " contactos por tener el mismo numero de telefono en el perfil destino."
                          << std::endl;
            }
        }
    }

    // Detecta contactos duplicados por teléfono
    void detectarContactosDuplicados() {
        int total = contactos->getSize();
        bool hayDuplicados = false;
        int i = 0;

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
                                      << " comparten el telefono "
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

    // Elimina un contacto por posición y libera memoria
    void eliminarContactoEn(int posicion) {
        if (posicion >= 0 && posicion < getNumeroContactos()) {
            Contacto* c = contactos->extract_at(posicion);
            if (c != nullptr) {
                delete c;
            }
        }
    }
};


// Exporta contactos de un perfil a otro
void exportarContactos(Perfil* origen, Perfil* destino) {
    if (origen != nullptr && destino != nullptr) {
        destino->importarContactosDesde(origen);
    }
}

// Carga inicial de perfiles
void inicializarPerfiles(LinkedList<Perfil*>* listaPerfiles) {
    // Perfil 1
    Perfil* p1 = new Perfil("Ana", "Le gusta la música y viajar");
    p1->agregarContactoFinal(new Contacto("Carlos",  "111111111", 25, "Madrid",   "Amigo de la universidad"));
    p1->agregarContactoFinal(new Contacto("Lucia",   "222222222", 23, "Valencia", "Companera de trabajo"));
    p1->agregarContactoFinal(new Contacto("Miguel",  "333333333", 28, "Sevilla",  "Conocido del gimnasio"));
    p1->agregarContactoFinal(new Contacto("Sofia",   "444444444", 24, "Bilbao",   "Amiga de la infancia"));
    p1->agregarContactoFinal(new Contacto("Raul",    "555555555", 29, "Zaragoza", "Contacto de un viaje"));

    // Perfil 2
    Perfil* p2 = new Perfil("Borja", "Aficionado al deporte y al cine");
    p2->agregarContactoFinal(new Contacto("Irene",   "666666666", 26, "Madrid",    "Companera de clase"));
    p2->agregarContactoFinal(new Contacto("Diego",   "777777777", 30, "Barcelona", "Amigo de fiestas"));
    p2->agregarContactoFinal(new Contacto("Natalia", "888888888", 27, "Granada",   "Amiga de Erasmus"));
    p2->agregarContactoFinal(new Contacto("Pedro",   "999999999", 31, "Malaga",    "Conocido del trabajo"));
    p2->agregarContactoFinal(new Contacto("Laura",   "101010101", 22, "Valladolid","Amiga del gimnasio"));

    // Perfil 3
    Perfil* p3 = new Perfil("Carla", "Le encantan los videojuegos y la tecnologia");
    p3->agregarContactoFinal(new Contacto("Javier",   "202020202", 24, "Madrid",   "Amigo de instituto"));
    p3->agregarContactoFinal(new Contacto("Patricia", "303030303", 29, "Valencia", "Companera de piso"));
    p3->agregarContactoFinal(new Contacto("Hugo",     "404040404", 27, "A Coruna", "Amigo de vacaciones"));
    p3->agregarContactoFinal(new Contacto("Elena",    "505050505", 25, "Murcia",   "Conocida de un curso"));
    p3->agregarContactoFinal(new Contacto("Sergio",   "606060606", 28, "Oviedo",   "Amigo de la universidad"));

    // Insertamos los perfiles en la lista
    listaPerfiles->insertar_cola(p1);
    listaPerfiles->insertar_cola(p2);
    listaPerfiles->insertar_cola(p3);
}


// Muestra el menú principal
int mostrarMenuPrincipal() {
    std::cout << "\n===== MENU PRINCIPAL =====\n";
    std::cout << "1. Ver perfiles disponibles\n";
    std::cout << "2. Iniciar sesion en un perfil\n";
    std::cout << "3. Salir\n";
    std::cout << "Seleccione una opcion: ";

    int op;
    std::cin >> op;
    return op;
}

// Muestra todos los perfiles
void mostrarPerfiles(LinkedList<Perfil*>* listaPerfiles) {
    std::cout << "\n=== PERFILES DISPONIBLES ===\n";

    int total = listaPerfiles->getSize();
    for (int i = 0; i < total; i++) {
        Perfil* p = listaPerfiles->obtener_en(i);
        std::cout << (i + 1) << ". " << p->getNombreUsuario()
                  << " (" << p->getNumeroContactos() << " contactos)\n";
    }
}

// Permite seleccionar un perfil
Perfil* seleccionarPerfil(LinkedList<Perfil*>* listaPerfiles) {
    mostrarPerfiles(listaPerfiles);

    int total = listaPerfiles->getSize();
    int op;

    while (true) {
        std::cout << "Seleccione un perfil (1-" << total << "): ";
        std::cin >> op;

        if (op >= 1 && op <= total) {
            return listaPerfiles->obtener_en(op - 1);
        }

        std::cout << "Opcion invalida.\n" << std::endl;
    }
}

// Muestra la información básica del perfil
void mostrarInfoPerfil(Perfil* perfilActual) {
    std::cout << "\n=== INFORMACION DEL PERFIL ===\n";
    std::cout << "Usuario: " << perfilActual->getNombreUsuario() << std::endl;
    std::cout << "Descripcion: " << perfilActual->getDescripcion() << std::endl;
    std::cout << "Numero de contactos: " << perfilActual->getNumeroContactos() << std::endl;
}

// Muestra todos los contactos de un perfil
void mostrarContactosPerfil(Perfil* perfilActual) {
    int total = perfilActual->getNumeroContactos();

    if (total == 0) {
        std::cout << "Este perfil no tiene contactos aun.\n";
    } else {
        std::cout << "\n=== LISTA DE CONTACTOS ===\n";
        for (int i = 0; i < total; i++) {
            Contacto* c = perfilActual->getContactoEn(i);
            std::cout << (i + 1) << ". "
                      << c->getNombre() << " | "
                      << c->getTelefono() << " | "
                      << c->getEdad() << " | "
                      << c->getCiudad() << " | "
                      << c->getDescripcion() << std::endl;
        }
    }
}

// Añade un contacto leyendo los datos por teclado
void aniadirContactoDesdeTeclado(Perfil* perfilActual) {
    std::string nombre, telefono, ciudad, descripcion;
    int edad;

    std::cin.ignore();

    std::cout << "Nombre: ";
    std::getline(std::cin, nombre);

    std::cout << "Telefono: ";
    std::getline(std::cin, telefono);

    if (perfilActual->existeTelefono(telefono)) {
        std::cout << "Ya existe un contacto con ese telefono en este perfil.\n";
    } else {
        std::cout << "Edad: ";
        std::cin >> edad;
        std::cin.ignore();

        std::cout << "Ciudad: ";
        std::getline(std::cin, ciudad);

        std::cout << "Descripcion: ";
        std::getline(std::cin, descripcion);

        Contacto* nuevo = new Contacto(nombre, telefono, edad, ciudad, descripcion);
        perfilActual->agregarContactoFinal(nuevo);

        std::cout << "Contacto agregado correctamente.\n";
    }
}

// Modifica un contacto existente
void modificarContactoPerfil(Perfil* perfilActual) {
    int total = perfilActual->getNumeroContactos();

    if (total == 0) {
        std::cout << "No hay contactos para modificar.\n";
    } else {
        mostrarContactosPerfil(perfilActual);

        int op;
        std::cout << "Seleccione el contacto a modificar: ";
        std::cin >> op;

        if (op >= 1 && op <= total) {
            Contacto* c = perfilActual->getContactoEn(op - 1);

            std::cin.ignore();

            std::string nombre, telefono, ciudad, descripcion;
            int edad;

            std::cout << "Nuevo nombre: ";
            std::getline(std::cin, nombre);

            std::cout << "Nuevo telefono: ";
            std::getline(std::cin, telefono);

            std::cout << "Nueva edad: ";
            std::cin >> edad;
            std::cin.ignore();

            std::cout << "Nueva ciudad: ";
            std::getline(std::cin, ciudad);

            std::cout << "Nueva descripcion: ";
            std::getline(std::cin, descripcion);

            c->setNombre(nombre);
            c->setTelefono(telefono);
            c->setEdad(edad);
            c->setCiudad(ciudad);
            c->setDescripcion(descripcion);

            std::cout << "Contacto modificado correctamente.\n";
        } else {
            std::cout << "Opcion invalida.\n";
        }
    }
}

// Elimina un contacto del perfil
void eliminarContactoPerfil(Perfil* perfilActual) {
    int total = perfilActual->getNumeroContactos();

    if (total == 0) {
        std::cout << "No hay contactos para eliminar.\n";
    } else {
        mostrarContactosPerfil(perfilActual);

        int op;
        std::cout << "Seleccione el contacto a eliminar: ";
        std::cin >> op;

        if (op >= 1 && op <= total) {
            perfilActual->eliminarContactoEn(op - 1);
            std::cout << "Contacto eliminado correctamente.\n";
        } else {
            std::cout << "Opcion invalida.\n";
        }
    }
}

// Importa contactos desde otro perfil
void importarDesdeOtroPerfil(Perfil* perfilActual, LinkedList<Perfil*>* listaPerfiles) {
    mostrarPerfiles(listaPerfiles);

    int total = listaPerfiles->getSize();
    int op;

    std::cout << "Seleccione el perfil de origen: ";
    std::cin >> op;

    if (op >= 1 && op <= total) {
        Perfil* origen = listaPerfiles->obtener_en(op - 1);

        if (origen == perfilActual) {
            std::cout << "No puede importar contactos de su propio perfil.\n";
        } else {
            perfilActual->importarContactosDesde(origen);
        }
    } else {
        std::cout << "Opcion invalida.\n";
    }
}

// Exporta contactos hacia otro perfil
void exportarAHaciaOtroPerfil(Perfil* perfilActual, LinkedList<Perfil*>* listaPerfiles) {
    mostrarPerfiles(listaPerfiles);

    int total = listaPerfiles->getSize();
    int op;

    std::cout << "Seleccione el perfil de destino: ";
    std::cin >> op;

    if (op >= 1 && op <= total) {
        Perfil* destino = listaPerfiles->obtener_en(op - 1);

        if (destino == perfilActual) {
            std::cout << "No puede exportar contactos a su propio perfil.\n";
        } else {
            exportarContactos(perfilActual, destino);
            std::cout << "Contactos exportados correctamente.\n";
        }
    } else {
        std::cout << "Opcion invalida.\n";
    }
}

// Menú de gestión del perfil
void menuPerfil(Perfil* perfilActual, LinkedList<Perfil*>* listaPerfiles) {
    int op = 0;

    while (op != 9) {
        std::cout << "\n===== MENU DEL PERFIL =====\n";
        std::cout << "1. Ver informacion del perfil\n";
        std::cout << "2. Ver lista de contactos\n";
        std::cout << "3. Agregar contacto\n";
        std::cout << "4. Modificar contacto\n";
        std::cout << "5. Eliminar contacto\n";
        std::cout << "6. Importar contactos desde otro perfil\n";
        std::cout << "7. Exportar contactos a otro perfil\n";
        std::cout << "8. Mostrar contactos duplicados\n";
        std::cout << "9. Cerrar sesion\n";
        std::cout << "Seleccione una opcion: ";

        std::cin >> op;

        if (op == 1) {
            mostrarInfoPerfil(perfilActual);
        } else if (op == 2) {
            mostrarContactosPerfil(perfilActual);
        } else if (op == 3) {
            aniadirContactoDesdeTeclado(perfilActual);
        } else if (op == 4) {
            modificarContactoPerfil(perfilActual);
        } else if (op == 5) {
            eliminarContactoPerfil(perfilActual);
        } else if (op == 6) {
            importarDesdeOtroPerfil(perfilActual, listaPerfiles);
        } else if (op == 7) {
            exportarAHaciaOtroPerfil(perfilActual, listaPerfiles);
        } else if (op == 8) {
            perfilActual->detectarContactosDuplicados();
        } else if (op == 9) {
            std::cout << "Cerrando sesion...\n";
        } else {
            std::cout << "Opcion invalida.\n";
        }
    }
}

// main con menú principal
int main() {
    LinkedList<Perfil*>* perfiles = new LinkedList<Perfil*>();
    inicializarPerfiles(perfiles);

    int opcion = 0;

    while (opcion != 3) {
        opcion = mostrarMenuPrincipal();

        if (opcion == 1) {
            mostrarPerfiles(perfiles);
        } else if (opcion == 2) {
            Perfil* perfilActual = seleccionarPerfil(perfiles);
            menuPerfil(perfilActual, perfiles);
        } else if (opcion == 3) {
            std::cout << "Saliendo del programa...\n";
        } else {
            std::cout << "Opcion invalida.\n";
        }
    }

    // Liberación básica de memoria
    int total = perfiles->getSize();
    for (int i = 0; i < total; i++) {
        delete perfiles->obtener_en(i);
    }
    delete perfiles;

    return 0;
}

