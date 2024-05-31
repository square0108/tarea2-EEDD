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

#define BIG_PRIME_SIZE 22189
const bool _main_debug = 1;

using namespace std;

/* IMPORTANTE: El codigo no puede ejecutarse solo con ./main, deben proporcionarse 3 argumentos en este orden:
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
    
    // Variable Input File Stream desde cual se leerá el dataset .csv
    ifstream twitter_csv;

    // Tiempo de ejecucion total de las N inserciones que se solicitaron al programa
    double total_running_time = 0;

    // Sólo para aclarar el código, estos son los argumentos que se ingresan
    char* table_type = argv[1];
    char* key_type = argv[2];
    size_t num_elements = atoi(argv[3]);

    // Vector que almacena instancias del struct "userdata", el cual guarda los valores de una fila del .csv (universidad, ID, nombre de usuario...)
    vector<userdata> twitter_values;

    // csv_to_vector ingresa los valores leídos en num_elements filas del .csv al vector anterior.
    twitter_csv.open("universities_followers.csv", ifstream::in);
    twitter_values = tarea::csv_to_vector(twitter_csv, num_elements);
    
    // Inserciones para claves tipo USERNAME
    if (strcmp(key_type,"username") == 0) {

        // Clave USERNAME ; Tabla STL MAP
        if (strcmp(table_type,"STL_map") == 0) {
            
            std::unordered_map<std::string,userdata> map;
            userdata current_row;

            for (userdata& row : twitter_values) {
                current_row = row;
                auto start = chrono::high_resolution_clock::now();
                map.insert({current_row.username,current_row});
                auto end = chrono::high_resolution_clock::now();
                total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
            }

        }

        // Clave USERNAME ; Tabla OPEN HASH
        else if (strcmp(table_type,"open_hash") == 0) {

            tarea::OpenHashTable<string,userdata> openhash(BIG_PRIME_SIZE,string_hash);
            userdata current_row;

            for (userdata& row : twitter_values) {
                current_row = row;
                auto start = chrono::high_resolution_clock::now();
                openhash.put(current_row.username,current_row);
                auto end = chrono::high_resolution_clock::now();
                total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
            }

            openhash.get_collisions_vector();
        }

        // Clave USERNAME ; Tabla CLOSED HASH
        else if (strcmp(table_type,"closed_hash") == 0) {
            // pendiente
        }
    }

    // Inserciones para claves tipo USER ID
    else if (strcmp(key_type,"user_id") == 0) {
        
        // Clave ID ; Tabla STL MAP
        if (strcmp(table_type,"STL_map") == 0) {
                        
            std::unordered_map<unsigned long long int,userdata> map;
            userdata current_row;

            for (userdata& row : twitter_values) {
                current_row = row;
                auto start = chrono::high_resolution_clock::now();
                map.insert({current_row.user_id,current_row});
                auto end = chrono::high_resolution_clock::now();
                total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
            }

        }

        // Clave ID ; Tabla OPEN HASH
        else if (strcmp(table_type,"open_hash") == 0) {
            tarea::OpenHashTable<unsigned long long int,userdata> openhash(BIG_PRIME_SIZE,CSandCompress);
            userdata current_row;
            for (auto& row : twitter_values) {
                current_row = row;
                auto start = chrono::high_resolution_clock::now();
                openhash.put(current_row.user_id,current_row);
                auto end = chrono::high_resolution_clock::now();

                total_running_time += (1e-9)*(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
            }
        }

        // Clave ID ; Tabla CLOSED HASH
        else if (strcmp(table_type,"closed_hash") == 0) {
            // pendiente
        }
    }

    // Si key_type no es igual ni a username ni a user_id, entonces se ejecutó incorrectamente el programa.
    else {
        cout << "Invalid hash key parameter. Possible key types: username, user_id" << endl;
        return -1;
    }

    // Se imprimen los resultados de un experimento con N inserciones (N: num_elements).
    cout << (string)key_type << ";" << num_elements << ";" << total_running_time << endl;
    twitter_csv.close();
    return 0;
}
