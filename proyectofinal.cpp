#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Producto{
    int codigo;
    char nombre[50];
    float precio;
    int stock;
    bool activo;
};

void mostrarEncabezado(){
    cout<<"\n--------Sistema de Ventas e Inventarios--------";
}

void pausarSistema(){
    cout<<"\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

bool existeCodigo(int codigoBuscado){
    Producto producto;
    ifstream archivo("productos.dat", ios::binary);
    if(!archivo){
        return false;
    }

    while(archivo.read((char*)&producto, sizeof(producto))){
        if(producto.codigo==codigoBuscado && producto.activo==true){
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

void registrarProducto(){
    Producto producto;
    ofstream archivo("productos.dat", ios::binary | ios::app);
    if(!archivo){
        cout<<"\nError al abrir el archivo\n";
        return;
    }

    cout<<"\n-----Registro de producto-----\n";
    do{
        cout<<"Codigo: ";
        cin>>producto.codigo;

        if(producto.codigo<=0){
            cout<<"\nEl codigo debe ser mayor a 0\n";
        }
        else if(existeCodigo(producto.codigo)){
            cout<<"\nEl codigo ya existe\n";
            producto.codigo=-1;
        }

    }while(producto.codigo<=0);

    cin.ignore();

    cout<<"Nombre: ";
    cin.getline(producto.nombre, 50);

    do{
        cout<<"Precio: ";
        cin>>producto.precio;

        if(producto.precio<=0){
            cout<<"\nEl precio debe ser mayor a 0\n";
        }
    }while(producto.precio<=0);

    do{
        cout<<"Stock: ";
        cin>>producto.stock;

        if(producto.stock<0){
            cout<<"\nEl stock no puede ser negativo\n";
        }
    }while(producto.stock<0);
    producto.activo=true;
    archivo.write((char*)&producto, sizeof(producto));
    archivo.close();
    cout<<"\nProducto registrado correctamente\n";
    pausarSistema();
}

void listarProductos(){
    Producto producto;
    ifstream archivo("productos.dat", ios::binary);
    if(!archivo){
        cout<<"\nNo hay productos registrados\n";
        return;
    }

    cout<<"\n--------Productos Activos--------\n";
    while(archivo.read((char*)&producto, sizeof(producto))){
        if(producto.activo==true){
            cout<<"\nCodigo: "<<producto.codigo;
            cout<<"\nNombre: "<<producto.nombre;
            cout<<"\nPrecio: Q"<<producto.precio;
            cout<<"\nStock: "<<producto.stock;
            cout<<"\n-----------------------------\n";
        }
    }
    archivo.close();
    pausarSistema();
}

void buscarProductoCodigo(){
    Producto producto;
    int codigoBuscado;
    bool encontrado=false;

    ifstream archivo("productos.dat", ios::binary);
    if(!archivo){
        cout<<"\nNo hay productos registrados\n";
        return;
    }

    cout<<"\nIngrese el codigo del producto: ";
    cin>>codigoBuscado;

    while(archivo.read((char*)&producto, sizeof(producto))){
        if(producto.codigo==codigoBuscado && producto.activo==true){
            cout<<"\nProducto encontrado";
            cout<<"\nNombre: "<<producto.nombre;
            cout<<"\nPrecio: Q"<<producto.precio;
            cout<<"\nStock: "<<producto.stock;

            encontrado=true;
            break;
        }
    }

    if(!encontrado){
        cout<<"\nProducto no encontrado\n";
    }

    archivo.close();
    pausarSistema();
}

void buscarProductoNombre(){
    Producto producto;
    char nombreBuscado[50];
    bool encontrado=false;

    ifstream archivo("productos.dat", ios::binary);

    if(!archivo){
        cout<<"\nNo hay productos registrados\n";
        return;
    }
    cin.ignore();

    cout<<"\nIngrese el nombre del producto: ";
    cin.getline(nombreBuscado, 50);

    while(archivo.read((char*)&producto, sizeof(producto))){
        if(strcmp(producto.nombre, nombreBuscado)==0 && producto.activo==true){

            cout<<"\nProducto encontrado";
            cout<<"\nCodigo: "<<producto.codigo;
            cout<<"\nPrecio: Q"<<producto.precio;
            cout<<"\nStock: "<<producto.stock;

            encontrado=true;
        }
    }

    if(!encontrado){
        cout<<"\nProducto no encontrado\n";
    }

    archivo.close();
    pausarSistema();
}

void modificarPrecio(){

    Producto producto;
    int codigoBuscado;
    float nuevoPrecio;
    bool encontrado=false;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    if(!archivo){
        cout<<"\nError al abrir archivo\n";
        return;
    }

    cout<<"\nCodigo del producto: ";
    cin>>codigoBuscado;

    while(archivo.read((char*)&producto, sizeof(producto))){

        if(producto.codigo==codigoBuscado && producto.activo==true){

            do{
                cout<<"Nuevo precio: ";
                cin>>nuevoPrecio;

                if(nuevoPrecio<=0){
                    cout<<"\nEl precio debe ser mayor a 0\n";
                }

            }while(nuevoPrecio<=0);

            producto.precio=nuevoPrecio;

            archivo.seekp(archivo.tellg()-(long)sizeof(producto));
            archivo.write((char*)&producto, sizeof(producto));

            cout<<"\nPrecio actualizado correctamente\n";

            encontrado=true;
            break;
        }
    }

    if(!encontrado){
        cout<<"\nProducto no encontrado\n";
    }

    archivo.close();

    pausarSistema();
}

void actualizarStock(){

    Producto producto;
    int codigoBuscado;
    int nuevoStock;
    bool encontrado=false;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    if(!archivo){
        cout<<"\nError al abrir archivo\n";
        return;
    }

    cout<<"\nCodigo del producto: ";
    cin>>codigoBuscado;

    while(archivo.read((char*)&producto, sizeof(producto))){

        if(producto.codigo==codigoBuscado && producto.activo==true){

            do{
                cout<<"Nuevo stock: ";
                cin>>nuevoStock;

                if(nuevoStock<0){
                    cout<<"\nNo se permiten negativos\n";
                }

            }while(nuevoStock<0);

            producto.stock=nuevoStock;

            archivo.seekp(archivo.tellg()-(long)sizeof(producto));
            archivo.write((char*)&producto, sizeof(producto));

            cout<<"\nStock actualizado correctamente\n";

            encontrado=true;
            break;
        }
    }

    if(!encontrado){
        cout<<"\nProducto no encontrado\n";
    }

    archivo.close();

    pausarSistema();
}

void desactivarProducto(){

    Producto producto;
    int codigoBuscado;
    bool encontrado=false;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    if(!archivo){
        cout<<"\nError al abrir archivo\n";
        return;
    }

    cout<<"\nCodigo del producto a desactivar: ";
    cin>>codigoBuscado;

    while(archivo.read((char*)&producto, sizeof(producto))){

        if(producto.codigo==codigoBuscado && producto.activo==true){

            producto.activo=false;

            archivo.seekp(archivo.tellg()-(long)sizeof(producto));
            archivo.write((char*)&producto, sizeof(producto));

            cout<<"\nProducto desactivado correctamente\n";

            encontrado=true;
            break;
        }
    }

    if(!encontrado){
        cout<<"\nProducto no encontrado\n";
    }

    archivo.close();

    pausarSistema();
}

void procesoVenta(){

    Producto producto;
    int codigoBuscado;
    int cantidad;
    bool encontrado=false;

    float subtotal;
    float iva;
    float total;

    fstream archivo("productos.dat", ios::binary | ios::in | ios::out);

    if(!archivo){
        cout<<"\nNo hay productos registrados\n";
        return;
    }

    cout<<"\n-----Proceso de Venta-----\n";

    cout<<"Codigo del producto: ";
    cin>>codigoBuscado;

    while(archivo.read((char*)&producto, sizeof(producto))){

        if(producto.codigo==codigoBuscado && producto.activo==true){

            encontrado=true;

            cout<<"\nProducto encontrado";
            cout<<"\nNombre: "<<producto.nombre;
            cout<<"\nPrecio: Q"<<producto.precio;
            cout<<"\nStock disponible: "<<producto.stock;

            do{
                cout<<"\nCantidad a vender: ";
                cin>>cantidad;

                if(cantidad<=0){
                    cout<<"\nIngrese una cantidad valida\n";
                }

                else if(cantidad>producto.stock){
                    cout<<"\nStock insuficiente\n";
                }

            }while(cantidad<=0 || cantidad>producto.stock);

            subtotal=producto.precio*cantidad;
            iva=subtotal*0.12;
            total=subtotal+iva;

            cout<<"\n--------Factura--------";
            cout<<"\nSubtotal: Q"<<subtotal;
            cout<<"\nIVA: Q"<<iva;
            cout<<"\nTotal: Q"<<total;

            producto.stock=producto.stock-cantidad;

            archivo.seekp(archivo.tellg()-(long)sizeof(producto));
            archivo.write((char*)&producto, sizeof(producto));

            cout<<"\n\nVenta realizada correctamente\n";

            break;
        }
    }

    if(!encontrado){
        cout<<"\nProducto no encontrado\n";
    }

    archivo.close();

    pausarSistema();
}

void menuProductos(){

    int opcion;

    do{

        mostrarEncabezado();

        cout<<"\n1. Registrar producto";
        cout<<"\n2. Listar productos";
        cout<<"\n3. Buscar producto por codigo";
        cout<<"\n4. Buscar producto por nombre";
        cout<<"\n5. Modificar precio";
        cout<<"\n6. Actualizar stock";
        cout<<"\n7. Desactivar producto";
        cout<<"\n8. Regresar";

        cout<<"\n\nSeleccione una opcion: ";
        cin>>opcion;

        switch(opcion){

            case 1:
                registrarProducto();
                break;

            case 2:
                listarProductos();
                break;

            case 3:
                buscarProductoCodigo();
                break;

            case 4:
                buscarProductoNombre();
                break;

            case 5:
                modificarPrecio();
                break;

            case 6:
                actualizarStock();
                break;

            case 7:
                desactivarProducto();
                break;

            case 8:
                break;

            default:
                cout<<"\nOpcion invalida\n";
        }

    }while(opcion!=8);
}

void menu(){

    int opcion;

    do{

        mostrarEncabezado();

        cout<<"\n1. Gestion de productos";
        cout<<"\n2. Proceso de venta";
        cout<<"\n3. Salir";

        cout<<"\n\nSeleccione una opcion: ";
        cin>>opcion;

        switch(opcion){

            case 1:
                menuProductos();
                break;

            case 2:
                procesoVenta();
                break;

            case 3:
                cout<<"\nGracias por usar el sistema\n";
                break;

            default:
                cout<<"\nOpcion invalida\n";
        }

    }while(opcion!=3);
}

int main(){

    cout<<"\nDesarrollado por Emily de Leon 9941-25-13659\n";

    menu();

    return 0;
}
