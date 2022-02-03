#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <conio.h>
using namespace std;
const char DIR_ARCHIVO[] = "contactos.dat";

/** Programa de Agenda virtual Por Noé Rivera Lugo **/
/** Esta Agenda
 * Busca contactos
 * Ingresa contactos nuevos
 * ve el listado de los contactos
 * elimina un contacto
 * actualiza un contacto
 * TODO FUNCIONA A TRAVÉS DE ARCHIVOS
 */

struct Contacto{
    char nombre[30];
    char apellido[45];
    int edad;
    char mail[45];
};
/*definicion de funciones */
void CrearContacto(Contacto c);
void IngresarContacto(Contacto c);
Contacto leerContacto();
void EditarContacto(Contacto c);
void EliminarContacto(char nombre[], char apellido[]);
Contacto BuscaContacto(char nombre[], char apellido[]);
bool existeContacto(char nombre[], char apellido[]);
void mostrarContacto(Contacto c);
void EditarContacto(char nombre[], char apellido[]);
void listarContactos();

// Funciones del menu
void menuCrear();
void buscar();
void listar();
void eliminar();
void editar();


void menuCrear(){
    cout<<"\t\t\t Ingreso de nuevo contacto"<<endl;
    Contacto nuevo = leerContacto();
    CrearContacto(nuevo);
    cout<<"\t\t\t Contacto almacenado exitosamente"<<endl;
}
void buscar(){
    cout<<"\t\t\t Busqueda de contacto"<<endl;
    char nombre[30], apellido[45];
    cout<<"\t\t\t Ingrese los datos de busqueda"<<endl;
    cout<<"\t\t\t Nombre: ";
    cin.getline(nombre,30);
    cout<<"\t\t\t Apellido: ";
    cin.getline(apellido,45);
    if(existeContacto(nombre,apellido)){
        Contacto encontrado = BuscaContacto(nombre,apellido);
        mostrarContacto(encontrado);
    }else{
        cout<<"\t\t\t El contacto solicitado no se encuentra en la lista"<<endl;
    }
}

void listar(){
    cout<<"\t\t\t CONTACTOS "<<endl;
    listarContactos();

}
void eliminar(){
    cout<<"\t\t\t Eliminar contacto"<<endl;
    char nombre[30], apellido[45];
    cout<<"\t\t\t Ingrese los datos del contacto"<<endl;
    cout<<"\t\t\t Nombre: ";
    cin.getline(nombre,30);
    cout<<"\t\t\t Apellido: ";
    cin.getline(apellido,45);
    if(existeContacto(nombre,apellido)){
        int opc;
        Contacto eliminar = BuscaContacto(nombre,apellido);
        cout<<"\t\t\t ¿Desea eliminar este contacto?"<<endl;
        mostrarContacto(eliminar);
        do{
            cout<<"\t\t\t 1.-Si  2.-No";
            cin>>opc;
            cin.ignore();
            switch (opc) {
                case 1: EliminarContacto(nombre,apellido);
                    cout<<"\t\t\t Contacto eliminado exitosamente"<<endl;
                    break;
                case 2: break;
                default:
                    cout<<"\t\t\t La opcion seleccionada no es correcta"<<endl;
            }
        } while (opc!=1 && opc!=2);



    }else{
        cout<<"\t\t\t El contacto solicitado no se encuentra en la lista"<<endl;
    }
}
void editar(){
    cout<<"\t\t\t Editar contacto"<<endl;
    char nombre[30], apellido[45];
    cout<<"\t\t\t Ingrese los datos del contacto"<<endl;
    cout<<"\t\t\t Nombre: ";
    cin.getline(nombre,30);
    cout<<"\t\t\t Apellido: ";
    cin.getline(apellido,45);
    if(existeContacto(nombre,apellido)){
        Contacto editar = BuscaContacto(nombre,apellido);
        cout<<"\t\t\t Registro a modificar";
        mostrarContacto(editar);
        EditarContacto(nombre,apellido);
        cout<<"\t\t\t Contacto modificado exitosamente"<<endl;
    }else{
        cout<<"\t\t\t El contacto solicitado no se encuentra en la lista"<<endl;
    }
}



void CrearContacto(Contacto c){
    ofstream salida;
    salida.open(DIR_ARCHIVO,ios::binary | ios::app);
    salida.write((char*)&c,sizeof(Contacto));
    salida.close();

}

Contacto leerContacto(){
    Contacto c;
    cout<<"\t \t Nombre:  ";
    cin.getline(c.nombre, 30);
    cout<<"\t\t Apellido: ";
    cin.getline(c.apellido,45);
    cout<<"\t\t Edad:  ";
    cin>>c.edad;
    cin.ignore();
    cout<<"\t\t Correo: ";
    cin.getline(c.mail,45);
    return c;


}

void IngresarContacto(Contacto c){
    Contacto leerContacto();
    bool existeContacto(char nombre[], char apellido[]); //retorna V o F si el contacto existe o no.
    Contacto BuscaContacto(char nombre[], char apellido[]);
    void mostrarContacto(Contacto c);
}

Contacto BuscaContacto(char nombre[], char apellido[]) {
    Contacto c;
    ifstream entrada;
    entrada.open(DIR_ARCHIVO, ios::binary);
    if (entrada.good()){
        while(entrada.read((char*)&c,sizeof(Contacto))){
            //strcmp -> string comparison o comparacion de cadenas
            if (strcmp(nombre,c.nombre)==0 && strcmp(apellido, c.apellido)==0){
                entrada.close();
                return c;
            }
        }

    }else{
        entrada.close();
        return c;
    }

}
bool existeContacto(char nombre[], char apellido[]){
    Contacto c;
    ifstream entrada;
    entrada.open(DIR_ARCHIVO, ios::binary);
    if (entrada.good()){
        while(entrada.read((char*)&c,sizeof(Contacto))){
            //strcmp -> string comparison o comparacion de cadenas
            if (strcmp(nombre,c.nombre)==0 && strcmp(apellido, c.apellido)==0){
                entrada.close();
                return true;
            }
        }
        entrada.close();
        return false;
    }else{
        return false;
    }

}

void mostrarContacto(Contacto c){
    cout<<"\t\t\t NOMBRE:  "<<c.nombre<<endl;
    cout<<"\t\t\t APELLIDO:  "<<c.apellido<<endl;
    cout<<"\t\t\t EDAD:  "<<c.edad<<endl;
    cout<<"\t\t\t CORREO:  "<<c.mail<<endl;
}
void listarContactos(){
    ifstream entrada;
    entrada.open(DIR_ARCHIVO, ios::binary);
    Contacto c;
    if(entrada.good()){
        while (entrada.read((char*)&c,sizeof (Contacto))){
            mostrarContacto(c);
        }
    }else{
        cout<<"No se puede leer el archivo"<<endl;
    }
    entrada.close();
}

void EditarContacto(char nombre[], char apellido[]){
    ifstream entrada;
    ofstream temporal;
    entrada.open(DIR_ARCHIVO,ios::binary);
    temporal.open("temp.dat",ios::binary);
    Contacto c;
    if(entrada.good()){
        while(entrada.read((char*)&c, sizeof (Contacto))){
            if (strcmp(nombre,c.nombre)==0 || strcmp(apellido, c.apellido)==0){
                Contacto actualizado = leerContacto();
                temporal.write((char*)&actualizado,sizeof (Contacto));
            }else{
                temporal.write((char*)&c,sizeof (Contacto));
            }
        }
    }
    entrada.close();
    temporal.close();
    remove(DIR_ARCHIVO);
    rename("temp.dat", DIR_ARCHIVO);

}

void EliminarContacto(char nombre[], char apellido[]){
    ifstream entrada;
    ofstream temporal;
    entrada.open(DIR_ARCHIVO,ios::binary);
    temporal.open("temp.dat",ios::binary);
    Contacto c;
    if(entrada.good()){
        while(entrada.read((char*)&c, sizeof (Contacto))){
            if (strcmp(nombre,c.nombre)!=0 || strcmp(apellido, c.apellido)!=0){
                temporal.write((char*)&c,sizeof (Contacto));
            }
        }
    }
    entrada.close();
    temporal.close();
    remove(DIR_ARCHIVO);
    rename("temp.dat", DIR_ARCHIVO);


}

int main() {
    int op;
    do{
        cout<<"\t\t\t AGENDA"<<endl;
        cout<<"\t\t\t Ingresar contacto......[1]"<<endl;
        cout<<"\t\t\t Buscar contacto........[2]"<<endl;
        cout<<"\t\t\t Eliminar contacto......[3]"<<endl;
        cout<<"\t\t\t Modificar contacto.....[4]"<<endl;
        cout<<"\t\t\t Listar contactos.......[5]"<<endl;
        cout<<"\t\t\t Salir..................[6]"<<endl;
        cout<<"\t\t\t Ingrese una opcion ";
        cin>>op;
        cin.ignore();

        switch (op) {
            case 1:
                system("cls");
                menuCrear();
                break;
            case 2:  system("cls");
            buscar();
                break;
            case 3:
                system("cls");
                eliminar();
                break;
            case 4:  system("cls");
            editar();
                break;
            case 5:  system("cls");
            listar();
                break;
            case 6: break;
            default: cout<<"opcion incorrecta"<<endl;

        }
    } while (op!=6);

    return 0;
}
