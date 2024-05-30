#include "hashCerrado.h"
#include <fstream> // para leer archivos csv


using namespace std;

int main(){

hashCerrado hash;

string miArchivo = "universities_followers.csv";
ifstream todos;

todos.open(miArchivo);

if(todos.fail()){
    cerr << "No se pudo abrir el archivo " << miArchivo << endl;
    return 1;
}
 usuario generico;
int contador = 0;
generico.user = "wequereque";
while(todos.peek()!=EOF){ //Esta lesera suguro que esta mala
    string datos;
    getline(todos, datos,',');
    if(contador > 6){
        if(contador%7 == 0){
            generico.universidad = datos;
        }if(contador%7 == 1){
            generico.stringID = datos;
        }if(contador%7 == 2){
            generico.user = datos;
        }if(contador%7 == 3){
            generico.nTweets = datos;
        }if(contador%7 == 4){
            generico.nFriends = datos;
        }if(contador%7 == 5){
            generico.nFollows = datos;
        }if(contador%7 == 6){
            generico.date = datos;
        }  
    }
    contador++;
    cout << generico.universidad << endl;
}
todos.close();

usuario weco{"wena","1",1,"Weco","12","25","65","Manana"};
usuario weco1{"wena","2",2,"Weco","1","25","65","Manana"};
usuario weco2{"wena","3",3,"Weco","12","25","65","Manana"};
usuario weco3{"wena","4",4,"Weco","12","25","65","Manana"};
usuario weco4{"wena","5",5,"Weco","12","25","65","Manana"};
usuario weco5{"wena","22",22,"Weco","12","25","65","Manana"};

hash.put(weco);
hash.put(weco1);
hash.put(weco2);
hash.put(weco3);
hash.put(weco4);
hash.imprimirID();

    return 0;
}