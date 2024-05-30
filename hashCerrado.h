#include <iostream>
#include <list>
#include <string>

using namespace std;

//Estructura con los parametros de los usuarios 
struct usuario{
    string universidad; 
    string stringID;
    int ID; 
    string user;
    string nTweets;
    string nFriends;
    string nFollows;
    string date;
};

//Clase que implementara la tabla con Hash Cerrado 
class hashCerrado{
private: 
    //Inteo de la tabla que almacena usuarios y su tamaño
    int tabla[5] = {-1,-1,-1,-1,-1}; // Tengo que inicializarla vacia 
public:
    //Declaracion de Funciones
    int fHashUser(usuario alguien); 
    int fHash(usuario alguien);
    int get(usuario alguien);
    int put(usuario alguien);
    int remove(usuario alguien);
    int size();
    bool isEmpty();
    void imprimirID();
};
//Implementacion de Funciones
int hashCerrado::fHash(usuario _alguien){
    int clave = _alguien.ID % 5;
    return clave;
}
int hashCerrado::fHashUser(usuario _alguien){
    
}
int hashCerrado::get(usuario _alguien){
    int clave = fHash(_alguien);
    //Si tabla en la posicion clave tiene el mismo ID que el ingresado en la funcion devuelve 1
        for (int i = 0; i < 5; i++){
            if(tabla[clave%5] == _alguien.ID){
                cout << _alguien.ID <<" estoy aqui" << endl;
                return _alguien.ID;
            }
            //Si tabla en la posicion clave no tiene el mismo id o el id es -2 salta a la siguiente casilla hasta que encuentre una vacia o recorra todo el arreglo
            else if(tabla[clave%5] == -1){ 
                cout << "No ta" << endl;
                return -100;
            }
            clave++;
        }
        cout << "No ta" << endl;
}
int hashCerrado::put(usuario _alguien){
    int clave = fHash(_alguien);
    //Si la posicion clave del arreglo esta vacia inserta al usuario 
    if(tabla[clave] == -1 || tabla[clave] == -2){
        tabla[clave] = _alguien.ID;
    }else{
        //Si la posicion clave del arreglo esta ocupada busca a la suguiente posicion vacia para insertarlo
        for(int i = 0; i < 5; i++){
           if(tabla[clave%5] == -1 || tabla[clave%5] == -2){
                tabla[clave%5] = _alguien.ID;
                break;
           }
           clave++;
        }
        cout << "No queda espacio" << endl;
        //Si no hay posiciones vacias tira error
        return -100;
    }
}
int hashCerrado::remove(usuario _alguien){
    int clave = fHash(_alguien);
    int aux;
    for (int i = 0; i < 5; i++){
            if(tabla[clave%5] == _alguien.ID){
                aux = tabla[clave%5];
                tabla[clave%5] = -2;
                cout << "Eliminado" << endl;
                return aux;
            }
            //Si tabla en la posicion clave no tiene el mismo id o el id es -2 salta a la siguiente casilla hasta que encuentre una vacia o recorra todo el arreglo
            else if(tabla[clave%5] == -1){ 
                cout << "No hay nada que eliminar" << endl;
                return -100;
            }
            clave++;
        }
        cout << "No hay nada en el arr que eliminar" << endl;
    
}
int hashCerrado::size(){

}
bool hashCerrado::isEmpty(){

}
void hashCerrado::imprimirID(){
    for(size_t i = 0; i < 5; i++){
        cout << tabla[i] << endl;
    }
}

