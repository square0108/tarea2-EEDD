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

using namespace std;

// Se inicializan todas las tablas hash con esta constante. Algunos otros primos grandes: {12821,17977,22187,30109,33533,65537,139969}.
// Con ALL_TABLES_SIZE = 30109 el factor de carga se *aproximará* a 0.70 al insertar todas las 21070 entradas.  
#define ALL_TABLES_SIZE 30109

// Numero de valores del dataset Twitter que se pre-insertarán en las tablas antes de realizar búsquedas
const int PRE_INSERTIONS = CSV_NUM_ENTRIES;

double total_running_time = 0;
vector<userdata> twitter_dataset;

/* Clase que almacena unicamente funciones estaticas de búsqueda para realizar experimentos sobre el dataset de Twitter.
*/
template <typename KeyT>
class SearchTester {
    public:
        static void search_test(std::vector<userdata>& dataset, MapADT<KeyT,userdata>& hash_table, int n_searches);
        static void search_test(std::vector<userdata>& dataset, std::unordered_map<KeyT,userdata>& map, int n_searches);
};

/* Declaraciones
*/
std::vector<userdata> create_dummy_data(int n_rows);

/* Syntax de ejecucion: ``./executable <dataset type> <table type> <key type> <number of searches>``
*
* - <dataset type> : {twitter_data,dummy_data}
* - <table type> : {STL_map,open_hash,closed_hash_linear,closed_hash_quadratic,closed_hash_double}
* - <key type> : {username,user_id}
* - <number of searches> : number in range [1,20000]
*/
int main(int argc, char** argv)
{
    // Verificar que se ingresaron los parametros correctamente al intentar ejecutar el codigo
    if (argc != 5)
        cout << "Invalid syntax. Usage: ./executable <dataset type> <table type> <key type> <number of insertions> <number of searches>" << endl;
    
    ifstream stream;
    vector<userdata> experiment_dataset;
    char *datasetType_arg = argv[1];
    char *tableType_arg = argv[2];
    char *keyType_arg = argv[3];
    int n_searches = atoi(argv[4]);

    stream.open("universities_followers.csv");
    twitter_dataset = tarea::csv_to_vector(stream, PRE_INSERTIONS);
    
    // Esta variación del experimento sólo hace búsquedas de datos existentes.
    if (strcmp(datasetType_arg,"twitter_data") == 0) {
        experiment_dataset = twitter_dataset;
    }
    // Las búsquedas sobre dummy_data son sólo de datos que no se encuentran en la tabla.
    else if (strcmp(datasetType_arg,"dummy_data") == 0)
        experiment_dataset = create_dummy_data(n_searches);
    
    stream.close();

    if (strcmp(keyType_arg,"username") == 0) {
        // Clave USERNAME ; Tabla STL MAP
        if (strcmp(tableType_arg,"STL_map") == 0) {
            std::unordered_map<std::string,userdata> map;
            map.reserve(ALL_TABLES_SIZE);
            SearchTester<std::string>::search_test(experiment_dataset,map,n_searches);
        }

        // Clave USERNAME ; Tabla OPEN HASH
        else if (strcmp(tableType_arg,"open_hash") == 0) {
            tarea::OpenHashTable<std::string,userdata> tabla(ALL_TABLES_SIZE,string_hash);
            SearchTester<std::string>::search_test(experiment_dataset,tabla,n_searches);
        }

        // Clave USERNAME ; Tablas CLOSED HASH
        else if (strcmp(tableType_arg,"closed_hash_linear") == 0) {
            ClosedHashTable<std::string, userdata> closed_hash(ALL_TABLES_SIZE,string_hash,LINEAR_PROBING);
            SearchTester<std::string>::search_test(experiment_dataset,closed_hash,n_searches);
        }

        else if (strcmp(tableType_arg,"closed_hash_quadratic") == 0) {
            ClosedHashTable<std::string, userdata> closed_hash(ALL_TABLES_SIZE,string_hash,QUADRATIC_PROBING);
            SearchTester<std::string>::search_test(experiment_dataset,closed_hash,n_searches);
        }

        else if (strcmp(tableType_arg,"closed_hash_double") == 0) {
            ClosedHashTable<std::string, userdata> closed_hash(ALL_TABLES_SIZE,string_hash,DOUBLE_HASHING);
            SearchTester<std::string>::search_test(experiment_dataset,closed_hash,n_searches);
        }
    }

    
    else if (strcmp(keyType_arg,"user_id") == 0) {
        // Clave ID ; Tabla STL MAP
        if (strcmp(tableType_arg,"STL_map") == 0) {
            std::unordered_map<unsigned long long int,userdata> map;
            map.reserve(ALL_TABLES_SIZE);
            SearchTester<unsigned long long int>::search_test(experiment_dataset,map,n_searches);
        }

        // Clave ID ; Tabla OPEN HASH
        else if (strcmp(tableType_arg,"open_hash") == 0) {
            tarea::OpenHashTable<unsigned long long int,userdata> tabla(ALL_TABLES_SIZE,CSandCompress);
            SearchTester<unsigned long long int>::search_test(experiment_dataset,tabla,n_searches);
        }

        // Clave ID ; Tabla CLOSED HASH
        else if (strcmp(tableType_arg,"closed_hash_linear") == 0) {
            ClosedHashTable<unsigned long long int, userdata> closed_hash(ALL_TABLES_SIZE,CSandCompress,LINEAR_PROBING);
            SearchTester<unsigned long long int>::search_test(experiment_dataset,closed_hash,n_searches);
        }

        else if (strcmp(tableType_arg,"closed_hash_quadratic") == 0) {
            ClosedHashTable<unsigned long long int, userdata> closed_hash(ALL_TABLES_SIZE,CSandCompress,QUADRATIC_PROBING);
            SearchTester<unsigned long long int>::search_test(experiment_dataset,closed_hash,n_searches);
        }

        else if (strcmp(tableType_arg,"closed_hash_double") == 0) {
            ClosedHashTable<unsigned long long int, userdata> closed_hash(ALL_TABLES_SIZE,CSandCompress,DOUBLE_HASHING);
            SearchTester<unsigned long long int>::search_test(experiment_dataset,closed_hash,n_searches);
        }
    }

    std::cout << total_running_time << std::endl;

    return 0;
}

template <typename KeyT>
void SearchTester<KeyT>::search_test(std::vector<userdata>& dataset, MapADT<KeyT,userdata>& hash_table, int n_searches)
{
    if constexpr (std::is_same_v<KeyT, std::string>) {
        // Pre-inserción de valores
        for (int i = 0; i < PRE_INSERTIONS; i++) {
            hash_table.put(twitter_dataset.at(i).username, twitter_dataset.at(i));
        }
        for (int i = 0; i < n_searches; i++) {
            userdata current_user = dataset.at(i);
            auto start = chrono::high_resolution_clock::now();
            hash_table.get(current_user.username);
            auto end = chrono::high_resolution_clock::now();
            total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
        }
    }
    else if constexpr (std::is_same_v<KeyT, unsigned long long int>) {
        // Pre-inserción de valores
        for (int i = 0; i < PRE_INSERTIONS; i++) {
            hash_table.put(twitter_dataset.at(i).user_id, twitter_dataset.at(i));
        }
        for (int i = 0; i < n_searches; i++) {
            userdata current_user = dataset.at(i);
            auto start = chrono::high_resolution_clock::now();
            hash_table.get(current_user.user_id);
            auto end = chrono::high_resolution_clock::now();
            total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
        }
    }
}

template <typename KeyT>
void SearchTester<KeyT>::search_test(std::vector<userdata>& dataset, std::unordered_map<KeyT,userdata>& map, int n_searches)
{
    if constexpr (std::is_same_v<KeyT, std::string>) {
        // Pre-inserción de valores
        for (int i = 0; i < PRE_INSERTIONS; i++) {
            map.insert({twitter_dataset.at(i).username, twitter_dataset.at(i)});
        }
        for (int i = 0; i < n_searches; i++) {
            userdata current_user = dataset.at(i);
            auto start = chrono::high_resolution_clock::now();
            map.find(current_user.username);
            auto end = chrono::high_resolution_clock::now();
            total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
        }
    }
    else if constexpr (std::is_same_v<KeyT, unsigned long long int>) {
        // Pre-inserción de valores
        for (int i = 0; i < PRE_INSERTIONS; i++) {
            map.insert({twitter_dataset.at(i).user_id, twitter_dataset.at(i)});
        }
        for (int i = 0; i < n_searches; i++) {
            userdata current_user = dataset.at(i);
            auto start = chrono::high_resolution_clock::now();
            map.find(current_user.user_id);
            auto end = chrono::high_resolution_clock::now();
            total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
        }
    }
}

std::vector<userdata> create_dummy_data(int n_rows) {
    // Sabemos que en el dataset el ID mínimo es 12852, podemos seguramente rellenar todos los valores antes de este tal que no sean del dataset.
    // Adicionalmente, el anterior ID más pequeño es 81213, así que también puede optarse por rellenar los ID's entre 12852 y 81213.
    const unsigned long long int SMALLEST_ID = 12852;
    std::vector<userdata> out;
    for (int i = 0; i < n_rows; i++) {
        userdata user;
        user.user_id = SMALLEST_ID+i+1;
        user.username = "Usuario" + std::to_string(i);
        out.push_back(user);
    }
    return out;
}