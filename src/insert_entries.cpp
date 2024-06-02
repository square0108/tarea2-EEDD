#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstring>
#include <utility>
#include <chrono>
#include "open_hash.h"
#include "hash_functions.h"
#include "datos_usuario.h"
#include "csv_data_insertion.h"
#include "closed_hash.h"

/* TODO
    - fix double hash
    - generate better dummy data
*/

// Se inicializan todas las tablas hash con esta constante. Algunos otros primos grandes: {12821,17977,22187,24821,30109,33533,65537,139969}.
// Con ALL_TABLES_SIZE = 30109 el factor de carga se *aproximará* a 0.70 al insertar todas las 21070 entradas.  
const int ALL_TABLES_SIZE = 24821;
double total_running_time = 0;

using namespace std;

/* Clase que almacena unicamente funciones estaticas para realizar experimentos sobre el dataset de Twitter.
*/
template <typename KeyT>
class InsertTester 
{
    public:
        static void insertion_test(std::vector<userdata>& dataset, MapADT<KeyT,userdata>& hash_table, int n_insertions);
        static void insertion_test(std::vector<userdata>& dataset, std::unordered_map<KeyT,userdata>& map, int n_insertions);
};

/* Syntax: ``./ejecutable <table type> <key type> <number of insertions>
*
* - <table type> : Tipo de tabla a usar. Posibles valores: {STL_map,open_hash,closed_hash}
* - <key type> : Tipo de llave que se va a ocupar para hashear. Posibles valores: {user_id,username}
* - <number of insertions> : numero de inserciones a realizar en el experimento. La tabla posee 21070 filas con datos.
*
* Ejemplo de uso:
* - Compilacion: ``g++ src/insert_entries.cpp -I headers/ -o hola``
* - Ejecucion: ``./hola open_hash user_id 20000``
*/
int main(int argc, char **argv)
{
    // Verificar que se ingresaron los parametros correctamente al intentar ejecutar el codigo
    if (argc != 4)
        cout << "Invalid syntax. Usage: ./main <table type> <key type> <number of insertions>" << endl;

    ifstream twitter_csv;
    char* table_type = argv[1];
    char* key_type = argv[2];
    size_t num_elements = atoi(argv[3]);

    // Vector que almacena instancias del struct "userdata", el cual guarda los valores de una fila del .csv (universidad, ID, nombre de usuario...)
    vector<userdata> twitter_values;

    twitter_csv.open("universities_followers.csv", ifstream::in);
    twitter_values = tarea::csv_to_vector(twitter_csv, num_elements);
    
    // Inserciones para claves tipo USERNAME
    if (strcmp(key_type,"username") == 0) {
        // Clave USERNAME ; Tabla STL MAP
        if (strcmp(table_type,"STL_map") == 0) {
            std::unordered_map<std::string,userdata> map;
            map.reserve(ALL_TABLES_SIZE);
            InsertTester<string>::insertion_test(twitter_values,map,num_elements);
        }

        // Clave USERNAME ; Tabla OPEN HASH
        else if (strcmp(table_type,"open_hash") == 0) {
            tarea::OpenHashTable<string,userdata> openhash(ALL_TABLES_SIZE,string_hash);
            InsertTester<string>::insertion_test(twitter_values,openhash,num_elements);
        }

        // Clave USERNAME ; Tablas CLOSED HASH
        else if (strcmp(table_type,"closed_hash_linear") == 0) {
            ClosedHashTable<string, userdata> closed_hash(ALL_TABLES_SIZE,string_hash,LINEAR_PROBING);
            InsertTester<string>::insertion_test(twitter_values,closed_hash, num_elements);
        }

        else if (strcmp(table_type,"closed_hash_quadratic") == 0) {
            ClosedHashTable<string, userdata> closed_hash(ALL_TABLES_SIZE,string_hash,QUADRATIC_PROBING);
            InsertTester<string>::insertion_test(twitter_values,closed_hash, num_elements);
        }

        else if (strcmp(table_type,"closed_hash_double") == 0) {
            ClosedHashTable<string, userdata> closed_hash(ALL_TABLES_SIZE,string_hash,DOUBLE_HASHING);
            InsertTester<string>::insertion_test(twitter_values,closed_hash, num_elements);
        }
    }

    // Inserciones para claves tipo USER ID
    else if (strcmp(key_type,"user_id") == 0) {
        // Clave ID ; Tabla STL MAP
        if (strcmp(table_type,"STL_map") == 0) {
            std::unordered_map<unsigned long long int,userdata> map;
            map.reserve(ALL_TABLES_SIZE);
            InsertTester<unsigned long long int>::insertion_test(twitter_values,map,num_elements);
        }

        // Clave ID ; Tabla OPEN HASH
        else if (strcmp(table_type,"open_hash") == 0) {
            tarea::OpenHashTable<unsigned long long int,userdata> openhash(ALL_TABLES_SIZE,CSandCompress);
            InsertTester<unsigned long long int>::insertion_test(twitter_values,openhash,num_elements);
        }

        // Clave ID ; Tabla CLOSED HASH
        else if (strcmp(table_type,"closed_hash_linear") == 0) {
            ClosedHashTable<unsigned long long int, userdata> closed_hash(ALL_TABLES_SIZE,CSandCompress,LINEAR_PROBING);
            InsertTester<unsigned long long int>::insertion_test(twitter_values,closed_hash, num_elements);
        }

        else if (strcmp(table_type,"closed_hash_quadratic") == 0) {
            ClosedHashTable<unsigned long long int, userdata> closed_hash(ALL_TABLES_SIZE,CSandCompress,QUADRATIC_PROBING);
            InsertTester<unsigned long long int>::insertion_test(twitter_values,closed_hash, num_elements);
        }

        else if (strcmp(table_type,"closed_hash_double") == 0) {
            ClosedHashTable<unsigned long long int, userdata> closed_hash(ALL_TABLES_SIZE,CSandCompress,DOUBLE_HASHING);
            InsertTester<unsigned long long int>::insertion_test(twitter_values,closed_hash, num_elements);
        }
    }

    // Si key_type no es igual ni a username ni a user_id, entonces se ejecutó incorrectamente el programa.
    else {
        cout << "Invalid hash key parameter. Possible key types: username, user_id" << endl;
        return -1;
    }

    // Se imprimen los resultados de un experimento con N inserciones (N: num_elements).
    cout << table_type << ";" << ALL_TABLES_SIZE << ";" << (string)key_type << ";" << num_elements << ";" << total_running_time << endl;
    twitter_csv.close();
    return 0;
}

template <typename KeyT>
void InsertTester<KeyT>::insertion_test(std::vector<userdata>& dataset,MapADT<KeyT,userdata>& hash_table,int n_insertions) 
{
    if constexpr (std::is_same_v<KeyT, std::string>) {
        for (int i = 0; i < n_insertions; i++) {
            userdata current_user = dataset.at(i);
            auto start = chrono::high_resolution_clock::now();
            hash_table.put(current_user.username,current_user);
            auto end = chrono::high_resolution_clock::now();
            total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
        }
    }
    else if constexpr (std::is_same_v<KeyT, unsigned long long int>) {
        for (int i = 0; i < n_insertions; i++) {
            userdata current_user = dataset.at(i);
            auto start = chrono::high_resolution_clock::now();
            hash_table.put(current_user.user_id,current_user);
            auto end = chrono::high_resolution_clock::now();
            total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
        }
    }
}

template <typename KeyT>
void InsertTester<KeyT>::insertion_test(std::vector<userdata>& dataset, std::unordered_map<KeyT,userdata>& map, int n_insertions) 
{
    if constexpr (std::is_same_v<KeyT, std::string>) {
        for (int i = 0; i < n_insertions; i++) {
            userdata current_user = dataset.at(i);
            auto start = chrono::high_resolution_clock::now();
            map.insert({current_user.username,current_user});
            auto end = chrono::high_resolution_clock::now();
            total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
        }
    }
    else if constexpr (std::is_same_v<KeyT, unsigned long long int>) {
        for (int i = 0; i < n_insertions; i++) {
            userdata current_user = dataset.at(i);
            auto start = chrono::high_resolution_clock::now();
            map.insert({current_user.user_id,current_user});
            auto end = chrono::high_resolution_clock::now();
            total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
        }
    }
}