//Bot que te permite cargar apis de paguinas de invercion para luego operrar desde tu computadora de forma manual o automatica.
// ##### Modulo 1(lexico). #####
//Se importan las librerias, se crean las estructuras de datos y se declaran las variables necesarias.
//===== Librerias =====
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

//===== estructuras =====
struct apisWeb{                     //Registro donde se guardan las apis de una web de invercion en especifico.
    char nombreWeb [100];
    int cantApis;
    char apis[100][200];
};

struct configuracion{               //Registro donde se guardan los datos de configuracion del programa.
    string idioma;
    int tiempoBot;
    bool debugin;
    double riesgo;
    double stopLoss;
    double takeProfit;
    double comision;
    double gananciaMinima;
    bool modoAutomatico;
};

struct TART{                        //Registro para almacenar el token de validacion y de refresh.
    string token;
    string refreshToken;
};

struct usuarios{                    //Registro para almacenar los datos de inicio de secion del usuario.
    string name;
    string contraseña;
};

//===== variables y constantes globales =====
int cantidades[10] = {1, 1, 3, 5, 1, 11, 6, 1, 21, 1};          //Constantes de opciones disponibles para oprear.
string nombresLargos[10] = {"Asesores", "AsesoresOperar", "TestInversor", "MiCuenta", "Notificacion", "Operar", 
                            "Operatoria Simplificada", "Perfil","Titulos","Token"};
string especificacionesDeAPIS[51] = {
    "Debe ser la API de movimientos de asesores.",
    "Debe ser la API para vender especie D desde asesores.",
    "Debe ser la API para obtener el test inversor.",
    "Debe ser la API para crear el test inversor.",
    "Debe ser la API para actualizar el test inversor.",
    "Debe ser la API del estado de cuenta.",
    "Debe ser la API del portafolio. Ejemplo:",
    "Debe ser la API para eliminar operaciones.",
    "Debe ser la API para consultar una operacion.",
    "Debe ser la API para listar operaciones.",
    "Debe ser la API de notificaciones.",
    "Debe ser la API para verificar si puede operar CPD.",
    "Debe ser la API de estados y segmentos CPD.",
    "Debe ser la API de comisiones CPD. Ejemplo:",
    "Debe ser la API para operar CPD.",
    "Debe ser la API del token de operacion.",
    "Debe ser la API para vender.",
    "Debe ser la API para comprar.",
    "Debe ser la API para rescatar FCI.",
    "Debe ser la API para vender especie D.",
    "Debe ser la API para comprar especie D.",
    "Debe ser la API para suscripcion FCI.",
    "Debe ser la API de montos estimados.",
    "Debe ser la API de parametros de operatoria.",
    "Debe ser la API de validacion de operatoria.",
    "Debe ser la API de montos estimados MEP.",
    "Debe ser la API de cotizacion MEP.",
    "Debe ser la API de compra simplificada.",
    "Debe ser la API de datos del perfil.",
    "Debe ser la API de FCI. Ejemplo:",
    "Debe ser la API de simbolo FCI.",
    "Debe ser la API de tipos de fondos.",
    "Debe ser la API de cotizacion MEP por simbolo.",
    "Debe ser la API de administradoras FCI.",
    "Debe ser la API de titulos por mercado.",
    "Debe ser la API de opciones del titulo.",
    "Debe ser la API de instrumentos de cotizacion.",
    "Debe ser la API de cotizaciones generales.",
    "Debe ser la API de cotizaciones por panel.",
    "Debe ser la API de detalle de cotizacion.",
    "Debe ser la API de cotizaciones Orleans.",
    "Debe ser la API de paneles de cotizacion.",
    "Debe ser la API de cotizaciones Orleans operables.",
    "Debe ser la API de cotizacion de titulo.",
    "Debe ser la API de cotizaciones Orleans panel.",
    "Debe ser la API de administradoras y tipos de fondos.",
    "Debe ser la API de cotizaciones Orleans panel operables.",
    "Debe ser la API de detalle mobile de cotizacion.",
    "Debe ser la API de administradoras por tipo de fondo.",
    "Debe ser la API de serie historica.",
    "Debe ser la API principal del token/autenticacion del usuario."
};
string codigos[10] = {"es", "en", "pt", "fr", "de", "it", "zh", "ru", "ja", "ko"};  //Constante de valores para configurar el idioma.

FILE* listApis;                 //Archivo para guardar todas las apis de las paguinas web que el usuario aya cargado para operar en ellas.
FILE* configurar;               //Archivo para guardar la configuracion deseada por el usuario.
struct apisWeb listaApis[1000]; //Arreglo para levantar los dato del archivo de apis y no operar sobre este.
configuracion config;           //Variable para levantar los datos de configuracion del archivo y no trabajar sobre este.
TART tokenRefreshToken;         //token y refreshToken son para guardar las claves de validacion de acciones para operar en las distintas webs.
usuarios usuario;               //Datos del usuario para el inicio de secion.
int indice;                     //indice del lugar donde se almacena en el registro la api deseada para una operacion dada.
string simbolo;                 //Simbolo del activo con el que se va a operar.

//##### Modulo 2. #####
//Verifica si existen apis caragadas en el programa viendo si existe el archivo donde estas se guardan y si no esta vacio.
bool hayApisCargadas(FILE* g) {
    g = fopen("apis.dat", "rb");

    if(g == NULL  || feof(g)){
        fclose(g);
        return false;
    }else{
        fclose(g);
        return true;
    }
}

//##### Modulo 3. #####
//Trduce el texto que el programa muestra, para eso recibiendo el mensaje a traducir y la configuracion para ver a que idioma se debe traducir.
string traduccion (configuracion conf, string* ms){

}

//##### Modulo 4. #####
//Guarda los dato del archivo de apis y los guarda en el arreglo.
void levantarApis(FILE* g, apisWeb *list) {
    int i;
    bool hayApis;
    string msg;

    i = 0;
    hayApis = hayApisCargadas(g);                                           //Verifica si hay apis.

    if (hayApis) {                                                          //Si hay apis levanta los datos del archivo.
        g = fopen("apis.dat", "rb");

        if (g == NULL) {
            cout << "Error al abrir el archivo.\n";
            return;
        }

        while (i < 1000 && fread(&list[i], sizeof(apisWeb), 1, g) == 1) {
            i++;
        }

        fclose(g);
    } else {                                                                 //Sino hay apis manda un mensaje de advertencia.
        msg = "No hay datos existentes.\n";
        msg = traduccion(config, &msg);
        cout << msg;
    }
}

//##### Modulo 5. #####
//Muestra la cantidad y los registros cargado y retorna la cantidad de registros cargados.
int cantApis(apisWeb* list){
    int cantidad;
    string msg;

    cantidad = 0;
    while (cantidad < 1000 && list[cantidad].cantApis != 0) {
        cantidad++;                                             //Cuenta los registros cargados.
    }

    msg = "\n=== WEBS DISPONIBLES ===\n";
    msg = traduccion(config, &msg);
    cout << msg;
    for (int i = 0; i < cantidad; i++) {
        cout << i << " - " << list[i].nombreWeb << endl;        //muestra la lista de registros de webs cargadas.
    }

    if (cantidad < 1000){                                       //Muestra la cantidad de registros.
        msg = "De registros cargados\n";
        msg = traduccion(config, &msg);
        cout << msg;
        cout << cantidad << msg;
    }

    return cantidad;                                            //Retorna la cantidad de registros.
}

//##### Modulo 6. #####
//Guarda las apis en el archivo
void guardarApis(int cantApis, FILE** g){
    string msg;

    *g = fopen("apis.dat", "wb");
    if (*g == NULL) {                                               //Verifica que se pueda guardar correctamente.
        msg = "Error al guardar\n";
        msg = traduccion(config, &msg);
        cout << msg;
    }else {
        for (int i = 0; i < cantApis; i++) {
            fwrite(&listaApis[i], sizeof(apisWeb), 1, *g);          //Proceso para guardar las apis en el archivo.
        }
        fclose(*g);

        msg = "\n APIs guardadas correctamente por secciones\n";    //Confirma el guardado correctamente.
        msg = traduccion(config, &msg);
        cout << msg;
    }
}

//##### Modulo 7. #####
//Carga elementos a la lista.
void cargarALista(apisWeb* list, int opc){
    int idx;
    string msg;

    msg = "Nombre de la web: \n";                                       //Pide el nombre de la web de donde pertenecen las apis a cargar.
    msg = traduccion(config, &msg);
    cout << msg;
    cin.ignore();
    cin.getline(list[opc].nombreWeb, 100);
    msg = "\n===== CARGA POR SECCIONES =====\n";
    msg = traduccion(config, &msg);
    cout << msg;
    msg = "\n# Las api deben cargarce en orden y forma adecuado conforme se van pidiendo o pueden prodecirce errores a la hora de operar.\n";
    msg = traduccion(config, &msg);
    cout << msg;
    idx = 0;


    for(int n = 0; n < 10; n++){                                        //Se piden las apis necesarias y en orden especifico.
        msg = "\n" + nombresLargos[n] + " - cantidad de APIs: ";
        msg = traduccion(config, &msg);
        cout << msg << cantidades[n] << endl;

        
        for(int i = 0; i < cantidades[n]; i++){
            if(idx >= 100){
                msg = "Limite maximo de APIs alcanzado.\n";
                msg = traduccion(config, &msg);
                cout << msg;
                break;
            }else {
                msg = nombresLargos[n] + " API #" + to_string(i + 1) + " " + especificacionesDeAPIS[idx] + ": ";
                msg = traduccion(config, &msg);
                cout << msg;
                cin.getline(list[opc].apis[idx], 200);
                idx++;
            }
        }
    }
    list[opc].cantApis = idx;
}

//##### Modulo 8. #####
//Agrega las apis de una web nueva y las pide siguiendo un sierto ooreden para generalizar el codigo del programa
void agregarApis(){
    int total;
    int pos;
    string msg;

    pos = cantApis(listaApis);

    if(pos < 0){                                            //Se verifica que haya espacio en la lista y que no se vaya a agregar
        msg = "Error en el sistema.\n";                     //la nueva lista de apis en una posicion invalida.
        msg = traduccion(config, &msg);
        cout << msg;
    }else {
        if(pos >= 1000){
            msg = "Almacenamiento de APIs lleno.\n";
            msg = traduccion(config, &msg);
            cout << msg;
        }else{                                              //Se agregan la nuevas apis.
            cargarALista(listaApis, pos);
            total = pos + 1;
            guardarApis(total, &listApis);
        }
    }
}

//##### Modulo 9. #####
//Busca si existe una web determinada
int seleccionarWeb(apisWeb* lista){
    int cantidad;
    int op;
    string msg;

    cantidad = cantApis(lista);                                 //Verifica que haya apis cargadas.

    if(cantidad <= 0){
        msg = "No hay APIs para modificar.\n";
        msg = traduccion(config, &msg);
        cout << msg;
        return -1;
    }

    msg = "\n=== MODIFICAR WEB ===\n";
    msg = traduccion(config, &msg);
    cout << msg;

    for(int i = 0; i < cantidad; i++){                          //Si hay apis cargadas se pide que selecciones una web y la busca.
        cout << i << " - " << lista[i].nombreWeb << endl;
    }

    msg = "\nSeleccione una web: ";
    msg = traduccion(config, &msg);
    cout << msg;
    cin >> op;

    if(op < 0 || op >= cantidad){
        msg = "Opcion invalida.\n";
        msg = traduccion(config, &msg);
        cout << msg;
        return -1;
    }

    return op;                                //Si se encuentra la web deseada se retorna la pocision de la web en casos cotrarios retorna -1.
}

//##### modulo 10. #####
//Limpia la lista de apis de la web deseada para agregar la lista modificada.
void limpiarApisWeb(apisWeb* web){
    web->cantApis = 0;

    for(int i = 0; i < 100; i++){
        web->apis[i][0] = '\0';
    }
}

//##### Modulo 11. #####
//Modifica las apis y guarda los cambios de la web deseada.
void modificarApis(FILE** g, apisWeb* lista){
    int op;
    int total;
    string msg;

    op = seleccionarWeb(lista);

    if(op != -1){
        msg = "\nModificando web: ";
        msg = traduccion(config, &msg);
        cout << msg << lista[op].nombreWeb << endl;
        limpiarApisWeb(&lista[op]);                     //Limpia la lista de apis de la web deseada.
        cargarALista(lista, op);                        //Pide la lista modificada.
        total = cantApis(lista);
        guardarApis(total, g);                       //Guarda los cambios (Este proceso lo hace si la web deseada esta cargada en el archivo).
        msg = "Web modificada correctamente.\n";
        msg = traduccion(config, &msg);
        cout << msg; 
    }
}

//##### Modulo 12. #####
//Elimina una web y sus APIs.
void eliminarApis(FILE** g, apisWeb* lista){
    int op;
    int total;
    string msg;

    op = seleccionarWeb(lista);                        //Pide la web deseada y la busca.

    if(op != -1){                                      //Si existe y esta al final de la lista la borra directamente sino la borra sobreescrive
        msg = "\nEliminando web: ";                    // los datos "moviendolos a la izquierda" y luego borra el ultimo elemento.
        msg = traduccion(config, &msg);
        cout << msg << lista[op].nombreWeb << endl;
        total = cantApis(lista);

        for(int i = op; i < total - 1; i++){
            lista[i] = lista[i + 1];
        }

        limpiarApisWeb(&lista[total - 1]);
        lista[total - 1].nombreWeb[0] = '\0';
        guardarApis(total - 1, g);
        msg = "Web eliminada correctamente.\n";
        msg = traduccion(config, &msg);
        cout << msg;
    } 
}

//##### Modulo 13. #####
//Menu de gestion de APIs.
void gestionarApis(FILE** g, apisWeb* lista){
    int op;
    string msg;

    do{
        msg = "\n====== GESTION DE APIs ======\n"     //Muestra el menu de opciones para gestionar las apis.
                "1. Agregar APIs\n"
                "2. Modificar APIs\n"
                "3. Eliminar APIs\n"
                "4. Volver\n"
                "\nOpcion: ";

        msg = traduccion(config, &msg);
        cout << msg;
        cin >> op;

        if(cin.fail()){                         //Si se ingresa una opcion valida se ejecuta las acciones requeridas sino
            cin.clear();                        //pide una opcion valida.
            cin.ignore(1000, '\n');
            msg = "Entrada invalida.\n";
            msg = traduccion(config, &msg);
            cout << msg;
            op = 0;
        }
        else{
            cin.ignore(1000, '\n');

            switch(op){

                case 1:
                    agregarApis();
                    break;

                case 2:
                    modificarApis(g, lista);
                    break;

                case 3:
                    eliminarApis(g, lista);
                    break;

                case 4:
                    msg = "Volviendo...\n";
                    msg = traduccion(config, &msg);
                    cout << msg;
                    break;

                default:
                    msg = "Opcion invalida.\n";
                    msg = traduccion(config, &msg);
                    cout << msg;
            }
        }
    }while(op != 4);
}

//##### Modulo 14. #####
//Menu para configurar el idioma del programa.
void configurarIdioma(configuracion *conf){
    int op;
    string msg;

    msg = "\n====== CONFIGURACION DE IDIOMA ======\n"     //Muestra el menu de opciones disponibles
          "1. Español.\n"                                //para configurar el idioma del programa.
          "2. Ingles.\n"
          "3. Portugues.\n"
          "4. Frances.\n"
          "5. Aleman.\n"
          "6. Italiano.\n"
          "7. Chino.\n"
          "8. Ruso.\n"
          "9. Japones.\n"
          "10. Coreano.\n"
          "11. Volver.\n"
          "\nOpcion: ";

    msg = traduccion(*conf, &msg);
    cout << msg;

    cin >> op;                                           //Pide seleccionar una opcion del menu.

    if(cin.fail()){                                      //Verifica que el dato ingresado sea valido.
        cin.clear();                                     //Limpia el estado de error de cin.
        cin.ignore(1000, '\n');                          //Limpia el buffer de entrada.
        msg = "Entrada invalida.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;

    }else{
        cin.ignore(1000, '\n');                          //Limpia el buffer despues de una entrada valida.

        if(op >= 1 && op <= 10){                         //Si la opcion corresponde a un idioma valido,                                
            conf->idioma = codigos[op - 1];              //configura el idioma seleccionado.
            msg = "Idioma configurado correctamente.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }else{
            if(op == 11){                                //La opcion 11 vuelve al menu anterior.
                msg = "Volviendo...\n";
                msg = traduccion(*conf, &msg);
                cout << msg;
            }else{                                       //Si la opcion no existe muestra error.
                msg = "Opcion invalida.\n";
                msg = traduccion(*conf, &msg);
                cout << msg;
            }
        }
    }
}

//##### Modulo 15. #####
//Configura el tiempo de espera del bot entre operaciones.
void configurarTiempo(configuracion *conf){
    string msg;

    msg = "Tiempo del bot (segundos): ";      //Pide el tiempo de espera del bot en segundos.
    msg = traduccion(*conf, &msg);
    cout << msg;
    cin >> conf->tiempoBot;

    if(cin.fail()){                           //Verifica que el dato ingresado sea valido.
        cin.clear();                          //Limpia el estado de error de cin.
        cin.ignore(1000, '\n');               //Limpia el buffer de entrada.
        msg = "Entrada invalida.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;
    }else{
        cin.ignore(1000, '\n');               //Limpia el buffer despues de una entrada valida.

        if(conf->tiempoBot > 0){              //Verifica que el tiempo ingresado sea mayor a cero.
            msg = "Tiempo configurado correctamente.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }else{
            msg = "El tiempo debe ser mayor a cero.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }
    }
}

//##### Modulo 16. #####
//Configura el modo debug del programa.
void configurarDebug(configuracion *conf){
    int op;
    string msg;

    msg = "Activar debug? (1=Si / 0=No): ";   //Pregunta si se desea activar el modo debug.
    msg = traduccion(*conf, &msg);
    cout << msg;
    cin >> op;

    if(cin.fail()){                           //Verifica que el dato ingresado sea valido.
        cin.clear();                          //Limpia el estado de error de cin.
        cin.ignore(1000, '\n');               //Limpia el buffer de entrada.
        msg = "Entrada invalida.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;
    }else{
        cin.ignore(1000, '\n');               //Limpia el buffer despues de una entrada valida.

        if(op == 0 || op == 1){               //Verifica que la opcion sea valida.
            conf->debugin = (op == 1);        //Activa o desactiva el modo debug.
            msg = "Debug configurado correctamente.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }else{
            msg = "Opcion invalida.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }
    }
}

//##### Modulo 17. #####
//Configura el porcentaje de riesgo permitido para operar.
void configurarRiesgo(configuracion *conf){
    string msg;

    msg = "Ingrese riesgo (ej: 0.1): ";   //Pide el porcentaje de riesgo deseado.
    msg = traduccion(*conf, &msg);
    cout << msg;
    cin >> conf->riesgo;

    if(cin.fail()){                       //Verifica que el dato ingresado sea valido.
        cin.clear();                      //Limpia el estado de error de cin.
        cin.ignore(1000, '\n');           //Limpia el buffer de entrada.
        msg = "Entrada invalida.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;

    }else{
        cin.ignore(1000, '\n');           //Limpia el buffer despues de una entrada valida.

        if(conf->riesgo > 0){             //Verifica que el riesgo sea mayor a cero.
            msg = "Riesgo configurado correctamente.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;

        }else{
            msg = "El riesgo debe ser mayor a cero.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }
    }
}

//##### Modulo 18. #####
//Configura el limite de perdida permitido por operacion.
void configurarStopLoss(configuracion *conf){
    string msg;

    msg = "Ingrese Stop Loss (ej: 0.05): "; //Pide el porcentaje maximo de perdida permitido.
    msg = traduccion(*conf, &msg);
    cout << msg;
    cin >> conf->stopLoss;

    if(cin.fail()){                         //Verifica que el dato ingresado sea valido.
        cin.clear();                        //Limpia el estado de error de cin.
        cin.ignore(1000, '\n');             //Limpia el buffer de entrada.
        msg = "Entrada invalida.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;
    }else{
        cin.ignore(1000, '\n');             //Limpia el buffer despues de una entrada valida.

        if(conf->stopLoss > 0){             //Verifica que el Stop Loss sea mayor a cero.
            msg = "Stop Loss configurado correctamente.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;

        }else{
            msg = "El Stop Loss debe ser mayor a cero.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }
    }
}

//##### Modulo 19. #####
//Configura el objetivo de ganancia por operacion.
void configurarTakeProfit(configuracion *conf){
    string msg;

    msg = "Ingrese Take Profit (ej: 0.1): "; //Pide el porcentaje de ganancia objetivo.
    msg = traduccion(*conf, &msg);
    cout << msg;
    cin >> conf->takeProfit;

    if(cin.fail()){                          //Verifica que el dato ingresado sea valido.
        cin.clear();                         //Limpia el estado de error de cin.
        cin.ignore(1000, '\n');              //Limpia el buffer de entrada.
        msg = "Entrada invalida.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;
    }else{
        cin.ignore(1000, '\n');              //Limpia el buffer despues de una entrada valida.

        if(conf->takeProfit > 0){            //Verifica que el Take Profit sea mayor a cero.
            msg = "Take Profit configurado correctamente.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;

        }else{
            msg = "El Take Profit debe ser mayor a cero.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }
    }
}

//##### Modulo 20. #####
//Configura la comision que se descontara en cada operacion realizada.
void configurarComision(configuracion *conf){
    string msg;

    msg = "Ingrese comision (ej: 0.01): ";
    msg = traduccion(*conf, &msg);
    cout << msg;
    cin >> conf->comision;

    if(cin.fail()){                               //Verifica que el valor ingresado sea numerico.
        cin.clear();
        cin.ignore(1000, '\n');
        msg = "Entrada invalida.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;
    }else{
        cin.ignore(1000, '\n');
        msg = "Comision configurada correctamente.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;
    }
}

//##### Modulo 21. #####
//Configura si el bot debe operar automaticamente o manualmente.
void configurarModoAutomatico(configuracion *conf){
    int op;
    string msg;

    msg = "Modo automatico? (1=Si / 0=No): ";
    msg = traduccion(*conf, &msg);
    cout << msg;
    cin >> op;

    if(cin.fail()){                               //Verifica que se ingrese un valor valido.
        cin.clear();
        cin.ignore(1000, '\n');
        msg = "Entrada invalida.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;
    }else{
        cin.ignore(1000, '\n');

        if(op == 1 || op == 0){                   //Configura el modo automatico.
            conf->modoAutomatico = (op == 1);
            msg = "Modo automatico configurado correctamente.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }else{
            msg = "Opcion invalida.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }
    }
}

//##### Modulo 22. #####
//Guarda la configuracion actual del programa en el archivo config.dat.
void guardarConfiguracion(configuracion *conf, FILE** g){
    string msg;

    *g = fopen("config.dat", "wb");

    if(*g == NULL){                               //Verifica que el archivo pueda abrirse correctamente.
        msg = "Error al guardar configuracion.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;
        return;
    }

    fwrite(conf, sizeof(configuracion), 1, *g);  //Guarda la configuracion en el archivo.
    fclose(*g);
    msg = "Configuracion guardada correctamente.\n";
    msg = traduccion(*conf, &msg);
    cout << msg;
}

//##### Modulo 23. #####
//Carga los valores de configuracion por defecto.
void cargarConfiguracionPorDefecto(configuracion *conf){
    conf->idioma = "es";
    conf->tiempoBot = 15;
    conf->debugin = false;
    conf->riesgo = 0.1;
    conf->stopLoss = 0.05;
    conf->takeProfit = 0.1;
    conf->comision = 0.01;
    conf->gananciaMinima = 0.02;
    conf->modoAutomatico = false;
}

//##### Modulo 24. #####
//Carga la configuracion guardada desde el archivo config.dat.
void cargarConfiguracion(configuracion *conf, FILE** g){
    size_t leidos;
    string msg;

    *g = fopen("config.dat", "rb");

    if(*g == NULL){                                           //Si no existe el archivo crea una configuracion por defecto.
        msg = "No hay configuracion previa, usando valores por defecto.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;
        cargarConfiguracionPorDefecto(conf);
        guardarConfiguracion(conf, g);
        return;
    }

    leidos = fread(conf, sizeof(configuracion), 1, *g);

    if(leidos != 1){                                          //Si ocurre un error de lectura carga valores por defecto.
        fclose(*g);
        msg = "Error al leer configuracion, usando valores por defecto.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;
        cargarConfiguracionPorDefecto(conf);
        guardarConfiguracion(conf, g);
        return;
    }

    fclose(*g);
    msg = "Configuracion cargada correctamente.\n";
    msg = traduccion(*conf, &msg);
    cout << msg;
}

//##### Modulo 25. #####
//Menu principal de configuracion del programa.
void menuConfiguracion(){
    int op;
    string msg;

    do{
        msg =
        "\n=========== CONFIGURACION ===========\n"
        "1. Gestionar APIs.\n"
        "2. Idioma.\n"
        "3. Tiempo del bot.\n"
        "4. Debug.\n"
        "5. Riesgo.\n"
        "6. Stop Loss.\n"
        "7. Take Profit.\n"
        "8. Comision.\n"
        "9. Modo automatico.\n"
        "10. Guardar configuracion.\n"
        "11. Volver.\n"
        "\nOpcion: ";

        msg = traduccion(config, &msg);
        cout << msg;
        cin >> op;

        if(cin.fail()){                                    //Verifica que la opcion ingresada sea valida.
            cin.clear();
            cin.ignore(1000, '\n');
            msg = "Entrada invalida.\n";
            msg = traduccion(config, &msg);
            cout << msg;
            op = 0;
        }else{
            cin.ignore(1000, '\n');

            switch(op){
                case 1:
                    gestionarApis(&listApis, listaApis);
                    break;

                case 2:
                    configurarIdioma(&config);
                    break;

                case 3:
                    configurarTiempo(&config);
                    break;

                case 4:
                    configurarDebug(&config);
                    break;

                case 5:
                    configurarRiesgo(&config);
                    break;

                case 6:
                    configurarStopLoss(&config);
                    break;

                case 7:
                    configurarTakeProfit(&config);
                    break;

                case 8:
                    configurarComision(&config);
                    break;

                case 9:
                    configurarModoAutomatico(&config);
                    break;

                case 10:
                    guardarConfiguracion(&config, &configurar);
                    break;

                case 11:
                    msg = "Volviendo...\n";
                    msg = traduccion(config, &msg);
                    cout << msg;
                    break;

                default:
                    msg = "Opcion invalida.\n";
                    msg = traduccion(config, &msg);
                    cout << msg;
            }
        }
    }while(op != 11);
}

//##### Modulo 26. #####
//Inicializa el sistema cargando configuracion y APIs.
void inicializarSistema(configuracion *conf, FILE** g, FILE** f, apisWeb* lista){
    int cantidad;
    int seleccion;
    string msg;

    cargarConfiguracion(conf, g);                           //Carga la configuracion guardada.
    levantarApis(*f, lista);                                //Carga las APIs guardadas en memoria.
    cantidad = cantApis(lista);                             //Obtiene la cantidad de webs cargadas.

    if(cantidad <= 0){                                      //Si no hay APIs cargadas obliga a cargarlas.
        msg = "No hay APIs cargadas, debe cargarlas.\n";
        msg = traduccion(*conf, &msg);
        cout << msg;
        gestionarApis(f, lista);                            //Abre el menu de gestion de APIs.
        levantarApis(*f, lista);                            //Recarga las APIs luego de agregarlas.
        cantidad = cantApis(lista);

        if(cantidad <= 0){                                  //Si sigue sin haber APIs muestra error.
            msg = "Error: no se pudieron cargar APIs.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }
    }

    if(cantidad > 0){
        seleccion = seleccionarWeb(lista);                  //Permite seleccionar la web a utilizar.

        if(seleccion != -1){
            msg = "Sistema inicializado correctamente.\n";
            msg = traduccion(*conf, &msg);
            cout << msg;
        }
    }
}

//##### Modulo 27. #####
//Extrae el valor asociado a una clave dentro de un texto JSON.
string extraerValor(const string& json, const string& clave){
    size_t posicionClave;
    size_t inicioValor;
    size_t finValor;

    posicionClave = json.find(clave);                       //Busca la posicion donde aparece la clave.
    if(posicionClave == string::npos){                      //Si la clave no existe retorna vacio.
        return "";
    }

    inicioValor = json.find(":", posicionClave);            //Busca el separador entre clave y valor.
    if(inicioValor == string::npos){
        return "";
    }

    inicioValor = json.find("\"", inicioValor);             //Busca el inicio del valor entre comillas.
    if(inicioValor == string::npos){
        return "";
    }

    inicioValor++;                                          //Avanza al primer caracter del valor.
    finValor = json.find("\"", inicioValor);                //Busca el final del valor.
    if(finValor == string::npos){
        return "";
    }

    return json.substr(inicioValor, finValor - inicioValor); //Retorna el valor extraido.
}

//##### Modulo 28. #####
//Obtiene el endpoint de autenticacion correspondiente a la web activa.
string obtenerEndpointToken(int webActiva){
    if(listaApis[webActiva].cantApis <= 0){                                 //Verifica que la web tenga APIs cargadas.
        return "";
    }

    return listaApis[webActiva].apis[listaApis[webActiva].cantApis - 1];    //Retorna la ultima API cargada (endpoint de token).
}

//##### Modulo 29. #####
//Ejecuta la peticion HTTP para solicitar el token de autenticacion.
void ejecutarPeticionToken(string endpoint){
    string comando;

    comando =
    "curl -s -X POST " + endpoint +                             //Arma el comando curl para realizar la peticion POST.
    " -H \"Content-Type: application/x-www-form-urlencoded\" "
    "-d \"username=" + usuario.name +
    "&password=" + usuario.contraseña +
    "&grant_type=password\" > token.json";

    system(comando.c_str());                                    //Ejecuta el comando del sistema.
}

//##### Modulo 30. #####
//Lee el archivo token.json y retorna la respuesta completa.
string leerRespuestaToken(){
    ifstream archivo;
    string respuesta;

    archivo.open("token.json");                                                             //Abre el archivo generado por curl.

    if(!archivo.is_open()){                                                                 //Verifica que el archivo exista.
        return "";
    }

    respuesta = string((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());  //Lee todo el contenido del archivo.
    archivo.close();                                                                        //Cierra el archivo.

    return respuesta;                                                                        //Retorna la respuesta JSON.
}

//##### Modulo 31. #####
//Guarda los tokens obtenidos dentro de la estructura correspondiente.
bool guardarTokens(string respuesta, TART* tokenyRefreshToken){
    string accessToken;
    string refreshToken;

    accessToken = extraerValor(respuesta, "access_token");      //Extrae el access token del JSON.
    refreshToken = extraerValor(respuesta, "refresh_token");    //Extrae el refresh token del JSON.

    if(accessToken.empty()){                                    //Verifica que el token exista.
        return false;
    }

    tokenyRefreshToken->token = accessToken;                    //Guarda el access token.
    tokenyRefreshToken->refreshToken = refreshToken;            //Guarda el refresh token.

    return true;                                                //Confirma guardado correcto.
}

//##### Modulo 32. #####
//Obtiene el token y refresh token desde la API de autenticacion.
void conseguirToken(TART* tokenyRefreshToken){
    string endpoint;
    string respuesta;
    string msg;
    int webActiva;

    webActiva = 0;                                              //Selecciona la web activa actual.
    endpoint = obtenerEndpointToken(webActiva);                 //Obtiene el endpoint de autenticacion.

    if(endpoint.empty()){                                       //Verifica que el endpoint exista.
        msg = "No se encontro endpoint de token.\n";
        msg = traduccion(config, &msg);
        cout << msg;
    }else{
        ejecutarPeticionToken(endpoint);                        //Solicita el token al servidor.
        respuesta = leerRespuestaToken();                       //Lee la respuesta generada.

        if(respuesta.empty()){                                  //Verifica que exista respuesta.
            msg = "No se pudo leer token.json.\n";
            msg = traduccion(config, &msg);
            cout << msg;
        }else{
            if(guardarTokens(respuesta, tokenyRefreshToken)){   //Guarda los tokens obtenidos.
                msg = "Token obtenido correctamente.\n";
                msg = traduccion(config, &msg);
                cout << msg;
            }else{                                              //Muestra error si no se obtuvo token.
                msg = "Error al obtener token.\n";
                msg = traduccion(config, &msg);
                cout << msg;
                msg = "Respuesta del servidor:\n";
                msg = traduccion(config, &msg);
                cout << msg << respuesta << endl;
            }
        }
    }
}

//##### Modulo 33. #####
//Realiza el login del usuario obteniendo los tokens de autenticacion.
bool login(TART* tokenyRefreshToken){
    string msg;

    conseguirToken(tokenyRefreshToken);         //Solicita los tokens al servidor.

    if(tokenyRefreshToken->token.empty()){      //Verifica que el token se haya obtenido sino retorna falso.
        msg = "Error en login.\n";
        msg = traduccion(config, &msg);
        cout << msg;

        return false;

    }else{                                     //Si el login fue exitoso retorna verdader.
        msg = "Login exitoso.\n";
        msg = traduccion(config, &msg);
        cout << msg;

        return true;
    }
}

//##### Modulo 34. #####
//Obtiene el endpoint de la API deseada.
string obtenerEndpointPost(int indiceApi, apisWeb *lista){
    if(indiceApi < 0 || indiceApi >= lista[0].cantApis){
        return "";
    }

    return lista[0].apis[indiceApi];
}

//##### Modulo 35. #####
//Lee el archivo respuesta.json y retorna su contenido.
string leerRespuestaJson(){
    ifstream archivo;
    string linea;
    string respuesta;

    archivo.open("respuesta.json");
    if(!archivo.is_open()){                         //Verifica que el archivo exista.
        return "";
    }

    while(getline(archivo, linea)){                //Concatena toda la respuesta JSON.
        respuesta += linea;
    }
    archivo.close();

    return respuesta;
}

//##### Modulo 36. #####
//Solicita un simbolo al usuario.
string pedirSimbolo(){
    string simbolo;
    string msg;

    msg = "Simbolo: ";
    msg = traduccion(config, &msg);
    cout << msg;
    getline(cin, simbolo);

    return simbolo;
}

//##### Modulo 37. #####
//Construye el endpoint agregando simbolo si corresponde.
string construirEndpoint(string endpoint, string simbolo){
    if(simbolo != "-1-"){                          //Verifica que no sea unico elemento.
        if(simbolo != "-0-"){                      //Verifica que existan elementos.
            if(simbolo.empty() == false){          //Verifica que el simbolo no este vacio.
                endpoint += "/" + simbolo;         //Agrega el simbolo al endpoint.
            }
        }
    }

    return endpoint;
}

//##### Modulo 38. #####
//Ejecuta una peticion GET y guarda la respuesta en respuesta.json.
bool ejecutarGet(string endpoint){
    string comando;

    if(endpoint.empty()){                          //Verifica que exista endpoint.
        return false;
    }

    comando =
    "curl -s -X GET \"" + endpoint +
    "\" > respuesta.json";

    system(comando.c_str());                       //Ejecuta la peticion GET.

    return true;
}

//##### Modulo 39. #####
//Cuenta la cantidad de objetos JSON existentes en la respuesta.
int contarElementosJson(string respuesta){
    int cantidad;
    int i;

    cantidad = 0;

    for(i = 0; i < respuesta.size(); i++){
        if(respuesta[i] == '{'){                   //Cuenta objetos JSON.
            cantidad++;
        }
    }

    return cantidad;
}

//##### Modulo 40. #####
//Convierte una cantidad numerica al codigo interno correspondiente.
string convertirCantidadCodigo(int cantidad){
    if(cantidad <= 0){                             //No existen elementos.
        return "-0-";
    }else{
        if(cantidad == 1){                         //Existe un unico elemento.
            return "-1-";
        }else{                                     //Existen multiples elementos.
            return "-2-";
        }
    }
}

//##### Modulo 41. #####
//Retorna la cantidad de elementos disponibles para una API.
//("-0-" = no hay elementos.
// "-1-" = existe un unico elemento.
// "-2-" = existen multiples elementos.)
string getCantElementos(int indiceApi, apisWeb *lista){
    string endpoint;
    string respuesta;
    int cantidad;

    endpoint = obtenerEndpointPost(indiceApi, lista);
    if(endpoint.empty()){                          //Verifica que exista endpoint.
        return "-0-";
    }

    if(ejecutarGet(endpoint) == false){            //Ejecuta GET sin autenticacion.
        return "-0-";
    }

    respuesta = leerRespuestaJson();
    if(respuesta.empty()){                         //Verifica que exista respuesta.
        return "-0-";
    }

    cantidad = contarElementosJson(respuesta);

    return convertirCantidadCodigo(cantidad);
}

//##### Modulo 42. #####
//Ejecuta una peticion GET autenticada.
bool ejecutarGetAutenticado(string endpoint){
    string comando;

    if(endpoint.empty()){                          //Verifica que exista endpoint.
        return false;
    }

    comando =
    "curl -s -X GET \"" + endpoint + "\" "
    "-H \"Authorization: Bearer " + tokenRefreshToken.token +
    "\" > respuesta.json";

    system(comando.c_str());                       //Ejecuta la peticion autenticada.

    return true;
}

//##### Modulo 43. #####
//Obtiene el endpoint GET deseado.
string obtenerEndpointGet(int indiceApi, apisWeb *lista){
    if(indiceApi < 0){                             //Verifica indice negativo.
        return "";
    }else{
        if(indiceApi >= lista[0].cantApis){        //Verifica limite de APIs.
            return "";
        }else{
            return lista[0].apis[indiceApi];       //Retorna endpoint solicitado.
        }
    }
}

//##### Modulo 44. #####
//Obtiene el simbolo dependiendo de la cantidad de elementos.
string obtenerSimboloGet(int indiceApi, apisWeb *lista){
    string cantidadElementos;
    string simbolo;

    cantidadElementos = getCantElementos(indiceApi, lista);

    if(cantidadElementos == "-0-"){                //No existen elementos.
        return "-0-";
    }else{
        if(cantidadElementos == "-1-"){            //Existe un unico elemento.
            return "-1-";
        }else{
            simbolo = pedirSimbolo();              //Solicita simbolo al usuario.

            if(simbolo.empty()){                   //Verifica simbolo vacio.
                return "-0-";
            }else{
                return simbolo;
            }
        }
    }
}

//##### Modulo 45. #####
//Realiza el proceso GET completo.
string ejecutarProcesoGet(string endpoint){
    if(ejecutarGetAutenticado(endpoint) == false){
        return "";
    }

    return leerRespuestaJson();
}

//##### Modulo 46. #####
//Obtiene la informacion del estado de cuenta.
string getCuenta(int indiceApi, apisWeb *lista){
    string endpoint;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){                          //Verifica que exista endpoint.
        return "";
    }

    return ejecutarProcesoGet(endpoint);
}

//##### Modulo 47. #####
//Obtiene la informacion de acciones.
string getAcciones(int indiceApi, apisWeb *lista){
    string endpoint;
    string simbolo;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){                          //Verifica endpoint valido.
        return "";
    }

    simbolo = obtenerSimboloGet(indiceApi, lista);
    if(simbolo == "-0-"){                          //Verifica existencia de simbolo.
        return "";
    }

    endpoint = construirEndpoint(endpoint, simbolo);

    return ejecutarProcesoGet(endpoint);
}

//##### Modulo 48. #####
//Obtiene la informacion de CEDEARs.
string getCDEARs(int indiceApi, apisWeb *lista){
    string endpoint;
    string simbolo;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return "";
    }

    simbolo = obtenerSimboloGet(indiceApi, lista);
    if(simbolo == "-0-"){
        return "";
    }

    endpoint = construirEndpoint(endpoint, simbolo);

    return ejecutarProcesoGet(endpoint);
}

//##### Modulo 49. #####
//Obtiene la informacion de bonos.
string getBonos(int indiceApi, apisWeb *lista){
    string endpoint;
    string simbolo;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return "";
    }

    simbolo = obtenerSimboloGet(indiceApi, lista);
    if(simbolo == "-0-"){
        return "";
    }

    endpoint = construirEndpoint(endpoint, simbolo);

    return ejecutarProcesoGet(endpoint);
}

//##### Modulo 50. #####
//Obtiene la informacion de opciones.
string getOpciones(int indiceApi, apisWeb *lista){
    string endpoint;
    string simbolo;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return "";
    }

    simbolo = obtenerSimboloGet(indiceApi, lista);
    if(simbolo == "-0-"){
        return "";
    }

    endpoint = construirEndpoint(endpoint, simbolo);

    return ejecutarProcesoGet(endpoint);
}

//##### Modulo 51. #####
//Obtiene la informacion de cauciones.
string getCautiones(int indiceApi, apisWeb *lista){
    string endpoint;
    string simbolo;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return "";
    }

    simbolo = obtenerSimboloGet(indiceApi, lista);
    if(simbolo == "-0-"){
        return "";
    }

    endpoint = construirEndpoint(endpoint, simbolo);

    return ejecutarProcesoGet(endpoint);
}

//##### Modulo 52. #####
//Obtiene la informacion de FCI.
string getFCI(int indiceApi, apisWeb *lista){
    string endpoint;
    string simbolo;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return "";
    }

    simbolo = obtenerSimboloGet(indiceApi, lista);
    if(simbolo == "-0-"){
        return "";
    }

    endpoint = construirEndpoint(endpoint, simbolo);

    return ejecutarProcesoGet(endpoint);
}

//##### Modulo 53. #####
//Obtiene la informacion de obligaciones negociables.
string getON(int indiceApi, apisWeb *lista){
    string endpoint;
    string simbolo;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return "";
    }

    simbolo = obtenerSimboloGet(indiceApi, lista);
    if(simbolo == "-0-"){
        return "";
    }

    endpoint = construirEndpoint(endpoint, simbolo);

    return ejecutarProcesoGet(endpoint);
}

//##### Modulo 54. #####
//Obtiene la informacion de portafolios.
string getPortafolios(int indiceApi, apisWeb *lista){
    string endpoint;
    string simbolo;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return "";
    }

    simbolo = obtenerSimboloGet(indiceApi, lista);
    if(simbolo == "-0-"){
        return "";
    }

    endpoint = construirEndpoint(endpoint, simbolo);

    return ejecutarProcesoGet(endpoint);
}

//##### Modulo 55. #####
//Obtiene la informacion de dolar MEP.
string getDolarMEP(int indiceApi, apisWeb *lista){
    string endpoint;
    string simbolo;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return "";
    }

    simbolo = obtenerSimboloGet(indiceApi, lista);
    if(simbolo == "-0-"){
        return "";
    }

    endpoint = construirEndpoint(endpoint, simbolo);

    return ejecutarProcesoGet(endpoint);
}

//##### Modulo 56. #####
//Obtiene la informacion de licitaciones.
string getLicitaciones(int indiceApi, apisWeb *lista){
    string endpoint;
    string simbolo;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return "";
    }

    simbolo = obtenerSimboloGet(indiceApi, lista);
    if(simbolo == "-0-"){
        return "";
    }

    endpoint = construirEndpoint(endpoint, simbolo);

    return ejecutarProcesoGet(endpoint);
}

//##### Modulo 57. #####
//Ejecuta una peticion POST a la API indicada.
bool ejecutarPost(string endpoint, string datos){
    string comando;

    if(endpoint.empty()){                          //Verifica que exista endpoint.
        return false;
    }

    comando =
    "curl -s -X POST \"" + endpoint + "\" "
    "-H \"Authorization: Bearer " + tokenRefreshToken.token + "\" "
    "-H \"Content-Type: application/json\" "
    "-d \"" + datos + "\" > respuesta.json";

    system(comando.c_str());                       //Ejecuta la peticion POST.

    return true;
}

//##### Modulo 58. #####
//Lee la respuesta generada por la peticion POST.
string leerRespuestaPost(){
    return leerRespuestaJson();
}

//##### Modulo 59. #####
//Realiza una peticion POST utilizando la API seleccionada.
void post(int indiceApi, apisWeb *lista){
    string endpoint;
    string respuesta;
    string datos;
    string msg;

    endpoint = obtenerEndpointPost(indiceApi, lista);

    if(endpoint.empty()){                          //Verifica que exista endpoint.
        msg = "Indice de API invalido.\n";
        msg = traduccion(config, &msg);
        cout << msg;
    }else{
        msg = "Datos JSON: ";
        msg = traduccion(config, &msg);
        cout << msg;
        getline(cin, datos);                       //Solicita datos JSON.

        if(ejecutarPost(endpoint, datos)){         //Ejecuta peticion POST.
            respuesta = leerRespuestaPost();
            msg = "POST ejecutado correctamente.\n";
            msg = traduccion(config, &msg);
            cout << msg;

            if(!respuesta.empty()){                //Muestra respuesta del servidor.
                msg = "Respuesta del servidor:\n";
                msg = traduccion(config, &msg);
                cout << msg << respuesta << endl;
            }

        }else{
            msg = "Error al ejecutar POST.\n";
            msg = traduccion(config, &msg);
            cout << msg;
        }
    }
}

//##### Modulo 60. #####
//Retorna una linea horizontal del cuadro.
string generarLineaCuadro(int columnas, int ancho){
    string linea;
    int i;
    int j;

    linea = "";

    for(i = 0; i < columnas; i++){
        linea += "+";

        for(j = 0; j < ancho; j++){
            linea += "-";
        }
    }

    linea += "+\n";

    return linea;
}

//##### Modulo 61. #####
//Centra un texto dentro de un ancho determinado.
string centrarTexto(string texto, int ancho){
    int espaciosIzquierda;
    int espaciosDerecha;
    string resultado;

    if(texto.size() >= ancho){
        return texto.substr(0, ancho);
    }

    espaciosIzquierda = (ancho - texto.size()) / 2;
    espaciosDerecha = ancho - texto.size() - espaciosIzquierda;

    resultado = "";

    while(espaciosIzquierda > 0){
        resultado += " ";
        espaciosIzquierda--;
    }

    resultado += texto;

    while(espaciosDerecha > 0){
        resultado += " ";
        espaciosDerecha--;
    }

    return resultado;
}

//##### Modulo 62. #####
//Retorna el mayor ancho necesario para una columna.
int obtenerMayorAncho(vector<string> claves, vector<string> valores){
    int ancho;
    int i;

    ancho = 15;

    for(i = 0; i < claves.size(); i++){
        if(claves[i].size() > ancho){
            ancho = claves[i].size();
        }

        if(valores[i].size() > ancho){
            ancho = valores[i].size();
        }
    }

    ancho += 4;

    return ancho;
}

//##### Modulo 63. #####
//Elimina caracteres innecesarios del valor extraido.
string limpiarValor(string valor){
    while(valor.empty() == false){
        if(valor[0] == ' ' || valor[0] == '\"'){
            valor.erase(0, 1);
        }else{
            break;
        }
    }

    while(valor.empty() == false){
        if(valor[valor.size() - 1] == ' ' || valor[valor.size() - 1] == '\"' || valor[valor.size() - 1] == '\n'){
            valor.erase(valor.size() - 1);
        }else{
            break;
        }
    }

    return valor;
}

//##### Modulo 64. #####
//Extrae claves y valores simples desde un JSON.
void extraerDatosJson(string respuesta, vector<string> *claves, vector<string> *valores){
    string clave;
    string valor;
    int posicion;
    int inicioClave;
    int finClave;
    int inicioValor;
    int finValor;

    posicion = 0;

    while(true){
        inicioClave = respuesta.find("\"", posicion);
        if(inicioClave == string::npos){
            break;
        }

        finClave = respuesta.find("\"", inicioClave + 1);
        if(finClave == string::npos){
            break;
        }

        clave = respuesta.substr(inicioClave + 1, finClave - inicioClave - 1);
        inicioValor = respuesta.find(":", finClave);
        if(inicioValor == string::npos){
            break;
        }

        inicioValor++;
        while(respuesta[inicioValor] == ' ' || respuesta[inicioValor] == '\"'){
            inicioValor++;
        }

        finValor = respuesta.find(",", inicioValor);
        if(finValor == string::npos){
            finValor = respuesta.find("}", inicioValor);
        }

        if(finValor == string::npos){
            break;
        }

        valor = respuesta.substr(inicioValor, finValor - inicioValor);
        valor = limpiarValor(valor);
        claves->push_back(clave);
        valores->push_back(valor);
        posicion = finValor + 1;
    }
}

//##### Modulo 65. #####
//Muestra una fila del cuadro.
void mostrarFila(vector<string> datos, int ancho){
    int i;
    string texto;

    for(i = 0; i < datos.size(); i++){
        texto = centrarTexto(datos[i], ancho);
        cout << "|" << texto;
    }

    cout << "|" << endl;
}

//##### Modulo 66. #####
//Traduce todas las claves del cuadro.
void traducirClaves(vector<string> *claves){
    int i;
    string texto;

    for(i = 0; i < claves->size(); i++){
        texto = (*claves)[i];
        texto = traduccion(config, &texto);
        (*claves)[i] = texto;
    }
}

//##### Modulo 67. #####
//Verifica que existan datos validos.
bool datosValidos(vector<string> claves, vector<string> valores){
    if(claves.size() <= 0){
        return false;
    }

    if(valores.size() <= 0){
        return false;
    }

    return true;
}

//##### Modulo 68. #####
//Muestra mensaje de error generico.
void mostrarErrorMostrar(string texto){
    texto = traduccion(config, &texto);
    cout << texto;
}

//##### Modulo 69. #####
//Muestra la informacion obtenida desde los GET en forma de cuadro.
void mostrar(int opcion){
    string respuesta;
    string linea;
    vector<string> claves;
    vector<string> valores;
    vector<string> fila;
    int ancho;

    respuesta = leerRespuestaJson();                   //Lee la respuesta JSON.

    if(respuesta.empty()){                             //Verifica que exista respuesta.
        mostrarErrorMostrar(
            "No hay informacion para mostrar.\n"
        );

        return;
    }

    extraerDatosJson(respuesta, &claves, &valores);

    if(datosValidos(claves, valores) == false){        
        mostrarErrorMostrar("No se encontraron datos validos.\n");

        return;
    }

    traducirClaves(&claves);                           //Traduce encabezados.
    ancho = obtenerMayorAncho(claves, valores);
    linea = generarLineaCuadro(claves.size(), ancho);
    cout << linea;
    mostrarFila(claves, ancho);                        //Muestra encabezados.
    cout << linea;
    mostrarFila(valores, ancho);                       //Muestra datos.
    cout << linea;
}

//##### Modulo 75. #####
//Obtiene el precio de un activo especifico.
double obtenerPrecio(string simbolo, int indiceApi, apisWeb *lista){
    string endpoint;
    string respuesta;
    string precioStr;

    endpoint = obtenerEndpointGet(indiceApi, lista);    //Obtiene el endpoint correspondiente.
    if(endpoint.empty()){                               //Verifica que exista endpoint.
        return 0.0;
    }

    if(simbolo.empty()){                                //Verifica que exista simbolo.
        return 0.0;
    }

    endpoint = construirEndpoint(endpoint, simbolo);    //Construye el endpoint final.
    respuesta = ejecutarProcesoGet(endpoint);           //Ejecuta la peticion GET.
    if(respuesta.empty()){                              //Verifica que exista respuesta.
        return 0.0;
    }

    precioStr = extraerValor(respuesta, "price");       //Extrae el precio del JSON.

    if(precioStr.empty()){                              //Verifica que exista el precio.
        precioStr = extraerValor(respuesta, "precio");
    }

    if(precioStr.empty()){
        return 0.0;
    }

    return atof(precioStr.c_str());                     //Convierte el valor a double.
}

//##### Modulo 76. #####
//Obtiene el saldo disponible de la cuenta.
double obtenerSaldo(int indiceApi, apisWeb *lista){
    string respuesta;
    string saldoStr;

    respuesta = getCuenta(indiceApi, lista);            //Obtiene la informacion de la cuenta.
    if(respuesta.empty()){                              //Verifica que exista respuesta.
        return 0.0;
    }

    saldoStr = extraerValor(respuesta, "saldo");        //Busca el saldo principal.

    if(saldoStr.empty()){                               //Busca nombres alternativos.
        saldoStr = extraerValor(respuesta, "balance");
    }

    if(saldoStr.empty()){
        saldoStr = extraerValor(respuesta, "cash");
    }

    if(saldoStr.empty()){                               //Verifica que exista saldo.
        return 0.0;
    }

    return atof(saldoStr.c_str());                      //Convierte el saldo a double.
}

//##### Modulo 77. #####
//Verifica si existe un activo especifico.
bool existeActivo(string respuesta, string simbolo){
    if(respuesta.find(simbolo) != string::npos){
        return true;
    }else{
        return false;
    }
}

//##### Modulo 78. #####
//Consulta si la cuenta posee un activo especifico.
bool tengoActivo(string simbolo, int indiceApi, apisWeb *lista){
    string endpoint;
    string respuesta;

    endpoint = obtenerEndpointGet(indiceApi, lista);    //Obtiene el endpoint correspondiente.
    if(endpoint.empty()){                               //Verifica que exista endpoint.
        return false;
    }

    respuesta = ejecutarProcesoGet(endpoint);           //Obtiene la informacion de activos.
    if(respuesta.empty()){                              //Verifica que exista respuesta.
        return false;
    }

    return existeActivo(respuesta, simbolo);            //Busca el simbolo en la respuesta.
}

//##### Modulo 79. #####
//Solicita una cantidad numerica al usuario.
int pedirCantidad(){
    int cantidad;
    string msg;

    msg = "Cantidad: ";
    msg = traduccion(config, &msg);
    cout << msg;
    cin >> cantidad;
    cin.ignore();

    return cantidad;
}

//##### Modulo 80. #####
//Construye el JSON de compra o venta.
string construirJsonOperacion(string simbolo, int cantidad){
    string datos;

    datos =
    "{\\\"symbol\\\":\\\"" + simbolo +
    "\\\",\\\"quantity\\\":" + to_string(cantidad) +
    "}";

    return datos;
}

//##### Modulo 81. #####
//Ejecuta una operacion POST autenticada.
bool ejecutarOperacionPost(string endpoint, string datos){
    string comando;

    if(endpoint.empty()){
        return false;
    }

    comando =
    "curl -s -X POST \"" + endpoint + "\" "
    "-H \"Authorization: Bearer " + tokenRefreshToken.token + "\" "
    "-H \"Content-Type: application/json\" "
    "-d \"" + datos + "\" > respuesta.json";

    system(comando.c_str());

    return true;
}

//##### Modulo 82. #####
//Calcula el costo total de una operacion.
double calcularCostoOperacion(double precio, int cantidad){
    return precio * cantidad;
}

//##### Modulo 83. #####
//Verifica si el saldo disponible alcanza para operar.
bool saldoSuficiente(double saldo, double costoTotal){
    if(saldo >= costoTotal){
        return true;
    }else{
        return false;
    }
}

//##### Modulo 84. #####
//Muestra el listado de activos segun la opcion elegida.
void mostrarActivosOperacion(int opcion){
    mostrar(opcion);
}

//##### Modulo 85. #####
//Obtiene el endpoint de operacion.
string obtenerEndpointOperacion(int indiceApi, apisWeb *lista){
    if(indiceApi < 0){
        return "";
    }else{
        if(indiceApi >= lista[0].cantApis){
            return "";
        }else{
            return lista[0].apis[indiceApi];
        }
    }
}

//##### Modulo 86. #####
//Muestra un mensaje traducido.
void mostrarMensaje(string mensaje){
    mensaje = traduccion(config, &mensaje);
    cout << mensaje;
}

//##### Modulo 87. #####
//Verifica que el simbolo ingresado sea valido.
bool simboloValido(string simbolo){
    if(simbolo.empty()){
        mostrarMensaje("Simbolo invalido.\n");
        return false;
    }else{
        return true;
    }
}

//##### Modulo 88. #####
//Verifica que la cantidad ingresada sea valida.
bool cantidadValida(int cantidad){
    if(cantidad <= 0){
        mostrarMensaje("Cantidad invalida.\n");
        return false;
    }else{
        return true;
    }
}

//##### Modulo 89. #####
//Verifica que el precio obtenido sea valido.
bool precioValido(double precio){
    if(precio <= 0){
        mostrarMensaje("No se pudo obtener el precio.\n");
        return false;
    }else{
        return true;
    }
}

//##### Modulo 90. #####
//Verifica que exista saldo suficiente.
bool verificarSaldo(double saldo, double costoTotal){
    if(saldoSuficiente(saldo, costoTotal) == false){
        mostrarMensaje("Saldo insuficiente.\n");
        return false;
    }else{
        return true;
    }
}

//##### Modulo 91. #####
//Verifica que el endpoint sea valido.
bool endpointValido(string endpoint){
    if(endpoint.empty()){
        mostrarMensaje("Endpoint invalido.\n");
        return false;
    }else{
        return true;
    }
}

//##### Modulo 92. #####
//Verifica si el usuario posee el activo.
bool verificarActivoUsuario(string simbolo, int indiceApi, apisWeb *lista){
    if(tengoActivo(simbolo, indiceApi, lista) == false){
        mostrarMensaje("No posee este activo.\n");
        return false;
    }else{
        return true;
    }
}

//##### Modulo 93. #####
//Muestra el resultado de una operacion.
void mostrarResultadoOperacion(bool estado, string respuesta, string mensajeExito, string mensajeError){
    if(estado){
        mostrarMensaje(mensajeExito);

        if(respuesta.empty() == false){
            mostrarMensaje("Respuesta del servidor:\n");
            cout << respuesta << endl;
        }
    }else{
        mostrarMensaje(mensajeError);
    }
}

//##### Modulo 94. #####
//Realiza la compra de un activo.
void compra(int opcion, int indiceApi, apisWeb *lista){
    string simbolo;
    string endpoint;
    string datos;
    string respuesta;
    int cantidad;
    double precio;
    double saldo;
    double costoTotal;
    bool estadoOperacion;

    mostrarActivosOperacion(opcion);                    //Muestra activos disponibles.
    simbolo = pedirSimbolo();                           //Solicita simbolo.
    if(simboloValido(simbolo) == false){
        return;
    }

    cantidad = pedirCantidad();                         //Solicita cantidad.
    if(cantidadValida(cantidad) == false){
        return;
    }

    precio = obtenerPrecio(simbolo, indiceApi, lista); //Obtiene precio.
    if(precioValido(precio) == false){
        return;
    }

    saldo = obtenerSaldo(0, lista);                    //Obtiene saldo.
    costoTotal = calcularCostoOperacion(precio, cantidad);
    if(verificarSaldo(saldo, costoTotal) == false){
        return;
    }

    endpoint = obtenerEndpointOperacion(indiceApi, lista);
    if(endpointValido(endpoint) == false){
        return;
    }

    datos = construirJsonOperacion(simbolo, cantidad);
    estadoOperacion = ejecutarOperacionPost(endpoint, datos);
    respuesta = leerRespuestaJson();
    mostrarResultadoOperacion(estadoOperacion, respuesta, "Compra realizada correctamente.\n", "Error al realizar la compra.\n");
}

//##### Modulo 95. #####
//Realiza la venta de un activo.
void venta(int opcion, int indiceApi, apisWeb *lista){
    string simbolo;
    string endpoint;
    string datos;
    string respuesta;
    int cantidad;
    bool estadoOperacion;

    mostrarActivosOperacion(opcion);                    //Muestra activos disponibles.
    simbolo = pedirSimbolo();                           //Solicita simbolo.
    if(simboloValido(simbolo) == false){
        return;
    }

    if(verificarActivoUsuario(simbolo, indiceApi, lista) == false){
        return;
    }

    cantidad = pedirCantidad();                         //Solicita cantidad.
    if(cantidadValida(cantidad) == false){
        return;
    }

    endpoint = obtenerEndpointOperacion(indiceApi, lista);
    if(endpointValido(endpoint) == false){
        return;
    }

    datos = construirJsonOperacion(simbolo, cantidad);
    estadoOperacion = ejecutarOperacionPost(endpoint, datos);
    respuesta = leerRespuestaJson();
    mostrarResultadoOperacion(estadoOperacion, respuesta, "Venta realizada correctamente.\n", "Error al realizar la venta.\n"
    );
}

//##### Modulo 96. #####
//Obtiene el historial de precios de un activo.
vector<double> obtenerHistorial(string simbolo, int indiceApi, apisWeb *lista){
    vector<double> precios;
    string endpoint;
    string respuesta;
    string valor;
    int posicion;
    int inicio;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return precios;
    }

    endpoint = construirEndpoint(endpoint, simbolo);
    if(ejecutarGetAutenticado(endpoint) == false){
        return precios;
    }

    respuesta = leerRespuestaJson();
    if(respuesta.empty()){
        return precios;
    }

    posicion = 0;

    while(true){
        posicion = respuesta.find("\"price\"", posicion);
        if(posicion == string::npos){
            break;
        }

        inicio = respuesta.find(":", posicion);
        if(inicio == string::npos){
            break;
        }

        inicio++;
        while(inicio < respuesta.size() && (respuesta[inicio] == ' '  || respuesta[inicio] == '"'  || respuesta[inicio] == '\t')){
            inicio++;
        }

        valor = "";
        while(inicio < respuesta.size() && ((respuesta[inicio] >= '0' && respuesta[inicio] <= '9') || respuesta[inicio] == '.')){
            valor += respuesta[inicio];
            inicio++;
        }

        if(valor.empty() == false){
            precios.push_back(atof(valor.c_str()));
        }

        posicion = inicio;
    }

    return precios;
}

//##### Modulo 97. #####
//Calcula la suma de un rango del historial.
double calcularSumaHistorial(vector<double> datos, int inicio, int fin){
    double suma;
    int i;

    suma = 0;
    for(i = inicio; i <= fin; i++){
        suma += datos[i];
    }

    return suma;
}

//##### Modulo 98. #####
//Verifica si el periodo solicitado es valido.
bool periodoValido(vector<double> datos, int periodo){
    if(periodo <= 0){
        return false;
    }else{
        if(datos.size() < periodo){
            return false;
        }
    }

    return true;
}

//##### Modulo 99. #####
//Calcula la media movil de un historial.
double mediaMovil(vector<double> datos, int periodo){
    double suma;
    int inicio;
    int fin;

    if(periodoValido(datos, periodo) == false){
        return 0.0;
    }

    inicio = datos.size() - periodo;
    fin = datos.size() - 1;
    suma = calcularSumaHistorial(datos, inicio, fin);

    return suma / periodo;
}

//##### Modulo 100. #####
//Calcula la variacion entre dos precios.
double calcularCambio(double actual, double anterior){
    return actual - anterior;
}

//##### Modulo 101. #####
//Acumula ganancias y perdidas del historial.
void acumularGananciasPerdidas(vector<double> datos, double *ganancias, double *perdidas){
    double cambio;
    int i;

    *ganancias = 0.0;
    *perdidas = 0.0;

    for(i = 1; i < datos.size(); i++){
        cambio = calcularCambio(
            datos[i],
            datos[i - 1]
        );

        if(cambio > 0){
            *ganancias += cambio;
        }else{
            *perdidas -= cambio;
        }
    }
}

//##### Modulo 102. #####
//Calcula el valor RS.
double calcularRS(double ganancias, double perdidas){
    if(perdidas <= 0){
        return 0.0;
    }

    return ganancias / perdidas;
}

//##### Modulo 103. #####
//Calcula el indicador RSI.
double calcularRSI(vector<double> datos){
    double ganancias;
    double perdidas;
    double rs;

    if(datos.size() < 2){
        return 0.0;
    }

    acumularGananciasPerdidas(datos, &ganancias, &perdidas);

    if(perdidas == 0){
        return 100.0;
    }

    rs = calcularRS(ganancias, perdidas);

    return 100 - (100 / (1 + rs));
}

//##### Modulo 104. #####
//Obtiene el volumen de un activo.
double obtenerVolumen(string simbolo, int indiceApi, apisWeb *lista){
    string endpoint;
    string respuesta;
    string volumenStr;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return 0.0;
    }

    endpoint = construirEndpoint(endpoint, simbolo);
    respuesta = ejecutarProcesoGet(endpoint);
    if(respuesta.empty()){
        return 0.0;
    }

    volumenStr = extraerValor(respuesta, "volume");
    if(volumenStr.empty()){
        volumenStr = extraerValor(
            respuesta,
            "volumen"
        );
    }

    if(volumenStr.empty()){
        return 0.0;
    }

    return atof(volumenStr.c_str());
}

//##### Modulo 105. #####
//Verifica si el volumen es considerado alto.
bool volumenAlto(string simbolo, int indiceApi, apisWeb *lista){
    double volumen;
    double limite;

    limite = 1000000;
    volumen = obtenerVolumen(simbolo, indiceApi, lista);

    if(volumen > limite){
        return true;
    }else{
        return false;
    }
}

//##### Modulo 106. #####
//Calcula el multiplicador de la EMA.
double calcularMultiplicadorEMA(int periodo){
    return 2.0 / (periodo + 1);
}

//##### Modulo 107. #####
//Verifica si existen datos suficientes para calcular EMA.
bool datosSuficientesEMA(vector<double> datos, int periodo){
    if(periodo <= 0){
        return false;
    }else{
        if(datos.size() < periodo){
            return false;
        }
    }

    return true;
}

//##### Modulo 108. #####
//Calcula la EMA de un historial de precios.
double calcularEMA(vector<double> datos, int periodo){
    double ema;
    double multiplicador;
    int i;

    if(datosSuficientesEMA(datos, periodo) == false){
        return 0.0;
    }

    multiplicador = calcularMultiplicadorEMA(periodo);
    ema = datos[0];

    for(i = 1; i < datos.size(); i++){
        ema = (datos[i] * multiplicador) + (ema * (1 - multiplicador));
    }

    return ema;
}

//##### Modulo 109. #####
//Obtiene el ultimo precio del historial.
double obtenerUltimoPrecio(vector<double> datos){
    if(datos.empty()){
        return 0.0;
    }

    return datos.back();
}

//##### Modulo 110. #####
//Calcula el porcentaje de ganancia o perdida.
double calcularGananciaPorcentual(double precioActual, double precioCompra){
    if(precioCompra <= 0){
        return 0.0;
    }

    return (precioActual - precioCompra) / precioCompra;
}

//##### Modulo 111. #####
//Evalua condiciones tecnicas de compra.
bool condicionesCompraValidas(double rsi, double precioActual, double ema, bool volumen){
    if(rsi < 30){
        if(precioActual > ema){
            if(volumen){
                return true;
            }
        }
    }

    return false;
}

//##### Modulo 112. #####
//Evalua condiciones tecnicas de venta.
bool condicionesVentaValidas(double rsi, double ganancia, double takeProfit, double stopLoss){
    if(rsi > 70){
        return true;
    }else{
        if(ganancia > takeProfit){
            return true;
        }else{
            if(ganancia < -stopLoss){
                return true;
            }
        }
    }

    return false;
}

//##### Modulo 113. #####
//Evalua si conviene comprar un activo.
bool evaluarCompra(string simbolo, int indiceApi, apisWeb *lista){
    vector<double> datos;
    double rsi;
    double ema;
    double precioActual;
    bool volumen;

    datos = obtenerHistorial(simbolo, indiceApi, lista);
    if(datos.empty()){
        return false;
    }

    rsi = calcularRSI(datos);
    ema = calcularEMA(datos, 10);
    precioActual = obtenerUltimoPrecio(datos);
    volumen = volumenAlto(simbolo, indiceApi, lista);

    return condicionesCompraValidas(rsi, precioActual, ema, volumen);
}

//##### Modulo 114. #####
//Evalua si conviene vender un activo.
bool evaluarVenta(string simbolo, double precioCompra, int indiceApi, apisWeb *lista){
    vector<double> datos;
    double rsi;
    double precioActual;
    double ganancia;

    datos = obtenerHistorial(simbolo, indiceApi, lista);
    if(datos.empty()){
        return false;
    }

    rsi = calcularRSI(datos);
    precioActual = obtenerUltimoPrecio(datos);
    ganancia = calcularGananciaPorcentual(precioActual, precioCompra);

    return condicionesVentaValidas(rsi, ganancia, config.takeProfit, config.stopLoss);
}

//##### Modulo 115. #####
//Retorna el indice de API correspondiente segun la opcion elegida.
int obtenerIndiceApiOperacion(int opcion){
    switch(opcion){
        case 1:
            return 1;   //Acciones

        case 2:
            return 2;   //CEDEARs

        case 3:
            return 3;   //Bonos

        case 4:
            return 4;   //Opciones

        case 5:
            return 5;   //Cauciones

        case 6:
            return 6;   //FCI

        case 7:
            return 7;   //ON

        case 8:
            return 8;   //Portafolios

        case 9:
            return 9;   //Dolar MEP

        case 10:
            return 10;  //Licitaciones

        default:
            return -1;
    }
}

//##### Modulo 116. #####
//Muestra mensaje informativo.
void mostrarMensajeOperacion(string mensaje){
    mensaje = traduccion(config, &mensaje);
    cout << mensaje;
}

//##### Modulo 117. #####
//Verifica si una opcion de operacion es valida.
bool opcionOperacionValida(int opcion){
    if(opcion >= 1){
        if(opcion <= 10){
            return true;
        }
    }

    return false;
}

//##### Modulo 118. #####
//Obtiene una cantidad automatica para operar.
int calcularCantidadAutomatica(double saldo, double precio){
    if(precio <= 0){
        return 0;
    }

    return saldo / precio;
}

//##### Modulo 119. #####
//Obtiene el precio de compra almacenado.
double obtenerPrecioCompra(string simbolo, int indiceApi, apisWeb *lista){
    string endpoint;
    string respuesta;
    string precioStr;

    endpoint = obtenerEndpointGet(indiceApi, lista);
    if(endpoint.empty()){
        return 0.0;
    }

    endpoint = construirEndpoint(endpoint, simbolo);
    respuesta = ejecutarProcesoGet(endpoint);
    if(respuesta.empty()){
        return 0.0;
    }

    precioStr = extraerValor(respuesta, "purchasePrice");
    if(precioStr.empty()){
        precioStr = extraerValor(respuesta, "precioCompra");
    }

    if(precioStr.empty()){
        return 0.0;
    }

    return atof(precioStr.c_str());
}

//##### Modulo 120. #####
//Realiza una compra automatica.
void ejecutarCompraAutomatica(string simbolo, int indiceApi, apisWeb *lista){
    string endpoint;
    string datos;
    string respuesta;
    double precio;
    double saldo;
    double costoTotal;
    int cantidad;

    precio = obtenerPrecio(simbolo, indiceApi, lista);
    if(precio <= 0){
        mostrarMensajeOperacion("No se pudo obtener el precio.\n");
        return;
    }

    saldo = obtenerSaldo(0, lista);
    cantidad = calcularCantidadAutomatica(saldo, precio);
    if(cantidad <= 0){
        mostrarMensajeOperacion("Saldo insuficiente.\n");
        return;
    }

    costoTotal = calcularCostoOperacion(precio, cantidad);
    if(saldoSuficiente(saldo, costoTotal) == false){
        mostrarMensajeOperacion("Saldo insuficiente.\n");
        return;
    }

    endpoint = obtenerEndpointOperacion(indiceApi, lista);
    if(endpoint.empty()){
        mostrarMensajeOperacion("Endpoint invalido.\n");
        return;
    }

    datos = construirJsonOperacion(simbolo, cantidad);

    if(ejecutarOperacionPost(endpoint, datos)){
        respuesta = leerRespuestaJson();
        mostrarMensajeOperacion("Compra automatica realizada.\n");

        if(respuesta.empty() == false){
            mostrarMensajeOperacion("Respuesta del servidor:\n");
            cout << respuesta << endl;
        }
    }else{
        mostrarMensajeOperacion("Error en compra automatica.\n");
    }
}

//##### Modulo 121. #####
//Realiza una venta automatica.
void ejecutarVentaAutomatica(string simbolo, int indiceApi, apisWeb *lista){
    string endpoint;
    string datos;
    string respuesta;
    double precioCompra;
    int cantidad;

    if(tengoActivo(simbolo, indiceApi, lista) == false){
        mostrarMensajeOperacion("No posee el activo.\n");
        return;
    }

    precioCompra = obtenerPrecioCompra(simbolo, indiceApi, lista);
    cantidad = 1;
    endpoint = obtenerEndpointOperacion(indiceApi, lista);

    if(endpoint.empty()){
        mostrarMensajeOperacion("Endpoint invalido.\n");
        return;
    }

    datos = construirJsonOperacion(simbolo, cantidad);

    if(ejecutarOperacionPost(endpoint, datos)){
        respuesta = leerRespuestaJson();
        mostrarMensajeOperacion("Venta automatica realizada.\n");

        if(respuesta.empty() == false){
            mostrarMensajeOperacion("Respuesta del servidor:\n");
            cout << respuesta << endl;
        }
    }else{
        mostrarMensajeOperacion("Error en venta automatica.\n");
    }
}

//##### Modulo 122. #####
//Evalua y ejecuta operaciones automaticas.
void compraVentaAutomatica(string simbolo, int opcion, apisWeb *lista){
    int indiceApi;
    double precioCompra;

    if(opcionOperacionValida(opcion) == false){
        mostrarMensajeOperacion("Opcion invalida.\n");
        return;
    }

    indiceApi = obtenerIndiceApiOperacion(opcion);

    if(indiceApi < 0){
        mostrarMensajeOperacion("API invalida.\n");
        return;
    }

    if(evaluarCompra(simbolo, indiceApi, lista)){
        ejecutarCompraAutomatica(simbolo, indiceApi, lista);
        return;
    }

    if(tengoActivo(simbolo, indiceApi, lista)){
        precioCompra = obtenerPrecioCompra(simbolo, indiceApi, lista);

        if(evaluarVenta(simbolo, precioCompra, indiceApi, lista)){
            ejecutarVentaAutomatica(simbolo, indiceApi, lista);
            return;
        }
    }

    mostrarMensajeOperacion("No se encontraron oportunidades.\n");
}

//##### Modulo 123. #####
//Verifica si existe el archivo de operaciones.
bool existeArchivoOperaciones(){
    ifstream archivo;

    archivo.open("operaciones.txt");
    if(archivo.is_open()){
        archivo.close();
        return true;
    }

    return false;
}

//##### Modulo 124. #####
//Muestra un mensaje traducido.
void mostrarMensajeHistorial(string mensaje){
    mensaje = traduccion(config, &mensaje);
    cout << mensaje;
}

//##### Modulo 125. #####
//Muestra el encabezado del historial.
void mostrarEncabezadoHistorial(){
    string msg;

    msg = "\n============================================================\n";
    mostrarMensajeHistorial(msg);
    msg = "               HISTORIAL DE OPERACIONES\n";
    mostrarMensajeHistorial(msg);
    msg = "============================================================\n";
    mostrarMensajeHistorial(msg);
}

//##### Modulo 126. #####
//Muestra los titulos de las columnas.
void mostrarColumnasHistorial(){
    string tipo;
    string simbolo;
    string cantidad;
    string precio;
    string fecha;

    tipo = "TIPO";
    simbolo = "SIMBOLO";
    cantidad = "CANTIDAD";
    precio = "PRECIO";
    fecha = "FECHA";

    tipo = traduccion(config, &tipo);
    simbolo = traduccion(config, &simbolo);
    cantidad = traduccion(config, &cantidad);
    precio = traduccion(config, &precio);
    fecha = traduccion(config, &fecha);

    cout << left << setw(15) << tipo << setw(15) << simbolo << setw(15) << cantidad << setw(15) << precio << setw(25) << fecha << endl;
    cout << "------------------------------------------------------------";
    cout << "-------------------------------\n";
}

//##### Modulo 127. #####
//Separa una linea del historial en campos.
bool separarOperacion(string linea, string &tipo, string &simbolo, string &cantidad, string &precio, string &fecha){
    stringstream ss(linea);

    getline(ss, tipo, ',');
    getline(ss, simbolo, ',');
    getline(ss, cantidad, ',');
    getline(ss, precio, ',');
    getline(ss, fecha, ',');

    if(tipo.empty()){
        return false;
    }

    return true;
}

//##### Modulo 128. #####
//Muestra una operacion del historial.
void mostrarOperacionHistorial(string tipo, string simbolo, string cantidad, string precio, string fecha){
    cout << left << setw(15) << tipo << setw(15) << simbolo << setw(15) << cantidad << setw(15) << precio << setw(25) << fecha << endl;
}

//##### Modulo 129. #####
//Muestra el pie del historial.
void mostrarPieHistorial(){
    string msg;

    msg = "============================================================\n";
    mostrarMensajeHistorial(msg);
}

//##### Modulo 130. #####
//Muestra el historial completo de operaciones.
void verOperaciones(){
    ifstream archivo;
    string linea;
    string tipo;
    string simbolo;
    string cantidad;
    string precio;
    string fecha;
    string msg;

    if(existeArchivoOperaciones() == false){
        msg = "No hay operaciones registradas.\n";
        mostrarMensajeHistorial(msg);
        return;
    }

    archivo.open("operaciones.txt");
    if(!archivo.is_open()){
        msg = "No se pudo abrir el archivo de operaciones.\n";
        mostrarMensajeHistorial(msg);
        return;
    }

    mostrarEncabezadoHistorial();
    mostrarColumnasHistorial();

    while(getline(archivo, linea)){
        if(separarOperacion(linea, tipo, simbolo, cantidad, precio, fecha)){
            mostrarOperacionHistorial(tipo, simbolo, cantidad, precio, fecha);
        }
    }

    archivo.close();
    mostrarPieHistorial();
}
//===============================================================================
// Se han modificado y completado hasta el modulo 130, se deben seguir modificando
// y completando (o directamente desarrollar) los modulos del 131 en adelante.
// Este comentario solo se usa como marca par determinar hasta donde se hizo y
// desde donde se debe seguir por lo que si se avanza de debe cambiar de lugar 
// y modificar (o borrar si es que ya se termino).
//===============================================================================

//##### Modulo 150. #####
//Muestra el titulo principal del sistema.
void mostrarTituloPrincipal(){
    cout << "\n=================================\n";
    mostrarMensaje("BOT INVERSION IOL\n");
    cout << "=================================\n";
}

//##### Modulo 151. #####
//Solicita una opcion numerica.
int pedirOpcionMenu(){
    int opcion;

    mostrarMensaje("Seleccione una opcion: ");
    cin >> opcion;
    cin.ignore();

    return opcion;
}

//##### Modulo 152. #####
//Muestra un separador visual.
void mostrarSeparadorMenu(){
    cout << "---------------------------------\n";
}

//##### Modulo 153. #####
//Muestra el menu principal.
void mostrarMenuPrincipal(){
    mostrarTituloPrincipal();
    mostrarMensaje("1  - Estado de cuenta\n");
    mostrarMensaje("2  - Acciones\n");
    mostrarMensaje("3  - CEDEARs\n");
    mostrarMensaje("4  - Bonos\n");
    mostrarMensaje("5  - Opciones\n");
    mostrarMensaje("6  - Cauciones\n");
    mostrarMensaje("7  - FCI\n");
    mostrarMensaje("8  - ON\n");
    mostrarMensaje("9  - Portafolios\n");
    mostrarMensaje("10 - Dolar MEP\n");
    mostrarMensaje("11 - Licitaciones\n");
    mostrarMensaje("12 - Configuracion\n");
    mostrarMensaje("13 - Salir\n");
    mostrarSeparadorMenu();
}

//##### Modulo 154. #####
//Muestra el submenu de operaciones.
void mostrarSubmenuOperaciones(){
    mostrarMensaje("\n--- OPERAR ---\n");
    mostrarMensaje("1. Comprar\n");
    mostrarMensaje("2. Vender\n");
    mostrarMensaje("3. Ver operaciones\n");
    mostrarMensaje("4. Trading automatico\n");
    mostrarMensaje("5. Volver\n");
}

//##### Modulo 155. #####
//Muestra el menu de activos.
void mostrarMenuActivo(string nombre){
    string titulo;

    titulo = "\n=== " + nombre + " ===\n";
    mostrarMensaje(titulo);
    mostrarMensaje("1. Ver lista de activos\n");
    mostrarMensaje("2. Operar\n");
    mostrarMensaje("3. Volver\n");
}

//##### Modulo 156. #####
//Ejecuta una opcion del submenu de operaciones.
void ejecutarOpcionOperaciones(int opcion, int opcionMenu){
    switch(opcion){
        case 1:
            compra(opcionMenu, opcionMenu, listaApis[0]);
            break;

        case 2:
            venta(opcionMenu, opcionMenu, listaApis[0]
            );
            break;

        case 3:
            verOperaciones();
            break;

        case 4:
            compraVentaAutomatica(pedirSimbolo(), opcionMenu, listaApis[0]);
            break;

        case 5:
            mostrarMensaje("Volviendo...\n");
            break;

        default:
            mostrarMensaje("Opcion invalida.\n");
    }
}

//##### Modulo 157. #####
//Submenu de operaciones.
void submenuOperaciones(int opcionMenu){
    int opcion;
    string refreshToken;

    do{
        mostrarSubmenuOperaciones();
        mostrarMensaje("Opcion: ");
        cin >> opcion;
        cin.ignore();
        conseguirToken(&tokenRefreshToken.token, &refreshToken);
        ejecutarOpcionOperaciones(opcion, opcionMenu);
    }while(opcion != 5);
}

//##### Modulo 158. #####
//Ejecuta una opcion del menu de activos.
void ejecutarOpcionActivo(int opcion, int opcionMenu){
    switch(opcion){
        case 1:
            mostrar(opcionMenu);
            break;

        case 2:
            submenuOperaciones(opcionMenu);
            break;

        case 3:
            mostrarMensaje("Volviendo...\n");
            break;

        default:
            mostrarMensaje("Opcion invalida.\n");
    }
}

//##### Modulo 159. #####
//Menu de activos.
void menuActivo(int opcionMenu, string nombre){
    int opcion;

    do{
        mostrarMenuActivo(nombre);
        mostrarMensaje("Opcion: ");
        cin >> opcion;
        cin.ignore();
        ejecutarOpcionActivo(opcion, opcionMenu);
    }while(opcion != 3);
}

//##### Modulo 160. #####
//Ejecuta una opcion del menu principal.
bool ejecutarOpcionPrincipal(int opcion){
    switch(opcion){
        case 1:
            mostrar(1);
            break;

        case 2:
            menuActivo(2, "Acciones");
            break;

        case 3:
            menuActivo(3, "CEDEARs");
            break;

        case 4:
            menuActivo(4, "Bonos");
            break;

        case 5:
            menuActivo(5, "Opciones");
            break;

        case 6:
            menuActivo(6, "Cauciones");
            break;

        case 7:
            menuActivo(7, "FCI");
            break;

        case 8:
            menuActivo(8, "ON");
            break;

        case 9:
            menuActivo(9, "Portafolios");
            break;

        case 10:
            menuActivo(10, "Dolar MEP");
            break;

        case 11:
            menuActivo(11, "Licitaciones");
            break;

        case 12:
            menuConfiguracion();
            break;

        case 13:
            mostrarMensaje("Cerrando sistema...\n");

            return false;

        default:
            mostrarMensaje("Opcion invalida.\n");
    }

    return true;
}

//##### Modulo 161. #####
//Menu principal del sistema.
void menuPrincipal(){
    int opcion;
    bool continuar;

    continuar = true;

    do{
        mostrarMenuPrincipal();
        opcion = pedirOpcionMenu();
        continuar = ejecutarOpcionPrincipal(opcion);
    }while(continuar);
}

//##### Modulo 162. #####
//Solicita las credenciales del usuario.
void pedirCredenciales(){
    mostrarMensaje("Ingrese usuario: ");
    getline(cin, configurar[0].credenciales.usuario);
    mostrarMensaje("Ingrese password: ");
    getline(cin, configurar[0].credenciales.password);
}

//##### Modulo 163. #####
//Inicia sesion en el sistema.
bool iniciarSesionSistema(){
    if(login(configurar[0].credenciales.usuario, configurar[0].credenciales.password) == false){
        mostrarMensaje("No se pudo iniciar sesion.\n");

        return false;
    }

    return true;
}

//##### Modulo 164 (modul principal main). #####
//Inicializa y ejecuta el sistema.
int main(){
    inicializarSistema(&config, &configurar, &listApis, listaApis);
    pedirCredenciales();

    if(iniciarSesionSistema() == false){
        return 1;
    }

    menuPrincipal();

    return 0;
}