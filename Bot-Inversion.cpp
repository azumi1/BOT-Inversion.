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
string token;
string refreshToken;            //token y refreshToken son para guardar las claves de validacion de acciones para operar en las distintas webs.
string usuario;
string password;                //Datos del usuario para el inicio de secion.
int indice;        //indice del lugar donde se almacena en el registro la api deseada para una operacion dada.

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
//===============================================================================
// Se han modificado y completado hasta el modulo 25, se deben seguir modificando
// y completando (o directamente desarrollar) los modulos del 26 en adelante.
// Este comentario solo se usa como marca par determinar hasta donde se hizo y
// desde donde se debe seguir por lo que si se avanza de debe cambiar de lugar 
// y modificar (o borrar si es que ya se termino).
//===============================================================================

//##### Modulo 26. #####
void inicializarSistema(configuracion *conf, FILE** g, FILE** f, apisWeb* lista){
    string msg;
    int seleccion;
    int cantidad;

    cargarConfiguracion(conf, g);
    levantarApis(*g);
    cantidad = 0;

    while (cantidad < 1000 && lista[cantidad].cantApis != 0) {
        cantidad++;
    }

    if (cantidad == 0) {
        msg = "No hay APIs cargadas, debe cargarlas";
        msg = traduccion(*conf, &msg);
        cout << msg << endl;

        gestionarApis(f, lista);
        levantarApis(*f);

        cantidad = 0;
        while (cantidad < 1000 && lista[cantidad].cantApis != 0) {
            cantidad++;
        }

        if (cantidad == 0) {
            msg = "Error: no se pudieron cargar APIs";
            msg = traduccion(*conf, &msg);
            cout << msg << endl;
            return;
        }
    }

    seleccion = seleccionarWeb(cantidad);
    msg = "Sistema inicializado correctamente";
    msg = traduccion(*conf, &msg);
    cout << msg << endl;
}

//##### Modulo . #####
string extraerValor(const string& json, const string& clave) {
    size_t posicionClave = json.find(clave);

    if (posicionClave == string::npos)
        return "";

    size_t inicioValor = json.find(":", posicionClave);
    if (inicioValor == string::npos)
        return "";

    inicioValor = json.find("\"", inicioValor);
    if (inicioValor == string::npos)
        return "";

    inicioValor++;

    size_t finValor = json.find("\"", inicioValor);
    if (finValor == string::npos)
        return "";

    return json.substr(inicioValor, finValor - inicioValor);
}

//##### Modulo . #####
void conseguirToken(string* toke, string* refre){
    string comando;
    string access_token;
    string new_refresh_token;
    string msg;
    int webActiva;

    webActiva = 0;
    if (listaApis[webActiva].cantApis == 0) {
        msg = "No hay APIs cargadas";
        msg = traduccion(config, &msg);
        cout << msg << endl;
        return;
    }

    string endpoint = listaApis[webActiva].apis[
        listaApis[webActiva].cantApis - 1
    ];

    if (endpoint.empty()) {
        msg = "No se encontró endpoint de token";
        msg = traduccion(config, &msg);
        cout << msg << endl;
        return;
    }

    comando =
        "curl -s -X POST " + endpoint +
        " -H \"Content-Type: application/x-www-form-urlencoded\" "
        "-d \"username=" + usuario +
        "&password=" + password +
        "&grant_type=password\" > token.json";

    system(comando.c_str());

    ifstream archivo("token.json");

    if (!archivo.is_open()) {
        msg = "No se pudo abrir token.json";
        msg = traduccion(config, &msg);
        cout << msg << endl;
        return;
    }

    string respuesta((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    archivo.close();

    access_token = extraerValor(respuesta, "access_token");
    new_refresh_token = extraerValor(respuesta, "refresh_token");

    if (!access_token.empty()) {
        *toke = access_token;
        *refre = new_refresh_token;

        msg = "Token obtenido correctamente";
        msg = traduccion(config, &msg);
        cout << msg << endl;
    } else {
        msg = "Error al obtener token";
        msg = traduccion(config, &msg);
        cout << msg << endl;

        msg = "Respuesta:";
        msg = traduccion(config, &msg);
        cout << msg << endl << respuesta << endl;
    }
}

//##### Modulo . #####
bool login(const string& usuario, const string& password){
    string access_token;
    string refresh_token_local;
    string msg;

    conseguirToken(&access_token, &refresh_token_local);

    if (access_token.empty()) {
        msg = "Error en login";
        msg = traduccion(config, &msg);
        cout << msg << endl;
        return false;
    }

    token = access_token;
    refresh = refresh_token_local;

    msg = "Login exitoso";
    msg = traduccion(config, &msg);
    cout << msg << endl;

    return true;
}

//##### Modulo . #####
string get(int indiceApi, apisWeb *lista[100]){
    //recibe como parametro el indice de la api deseada y el listado de apis y hace la consulta deseada (ya sea de la cuenta, activos, etc)
    string msg;
    string comando;
    string endpoint;

    if (indiceApi < 0 || indiceApi >= lista.cantApis) {
        msg = "Indice de API invalido";
        msg = traduccion(config, &msg);
        cout << msg << endl;
        return "";
    }

    endpoint = lista.apis[indiceApi];
    comando =
        "curl -s -X GET \"" + endpoint + "\" "
        "-H \"Authorization: Bearer " + token + "\" > respuesta.json";

    system(comando.c_str());
    ifstream archivo("respuesta.json");

    if (!archivo.is_open()) {
        msg = "No se pudo abrir respuesta.json";
        msg = traduccion(config, &msg);
        cout << msg << endl;
        return "";
    }

    string respuesta((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    archivo.close();

    return respuesta;
}

//##### Modulo . #####
void post(int indiceApi, apisWeb *lista[100]){
    //recibe como parametro el indice de la api deseada y el listado de apis y hace el posteo deseado (ya sea de la cuenta, activos, etc)
    string msg;
    string comando;
    string endpoint;

    if (indiceApi < 0 || indiceApi >= lista.cantApis) {
        msg = "Indice de API invalido";
        msg = traduccion(config, &msg);
        cout << msg << endl;
        return;
    }

    endpoint = lista.apis[indiceApi];
    comando =
        "curl -s -X POST \"" + endpoint + "\" "
        "-H \"Authorization: Bearer " + token + "\" "
        "-H \"Content-Type: application/json\" "
        "-d \"{}\" > respuesta.json";

    system(comando.c_str());
    msg = "POST ejecutado";
    msg = traduccion(config, &msg);
    cout << msg << endl;
}

//##### Modulo . #####
void mostrar(int opcion){
    //recibe la opcion de lo que se desea mostrar (ya sea de la cuenta, activos, etc) y lo muestra
}

//##### Modulo . #####
double obtenerPrecio(const string& simbolo, int indiceApi, apisWeb *lista[100]){
    //recibe como parametro el simbolo del activo deseado y retorna el precio
    string respuesta;
    string precioStr;

    respuesta = get(indiceApi, lista);
    precioStr = extraerValor(respuesta, "price");

    if (precioStr.empty()){
        return 0.0;
    }

    return atof(precioStr.c_str());
}

//##### Modulo . #####
double obtenerSaldo(int indiceApi, apisWeb *lista[100]){
    //obtiene el saldo de la cuenta
    string respuesta;
    string saldoStr;

    respuesta = get(indiceApi, lista);
    saldoStr = extraerValor(respuesta, "saldo");

    if (saldoStr.empty()){
        return 0.0;
    }

    return atof(saldoStr.c_str());
}

//##### Modulo . #####
bool tengoActivo(const string& simbolo, int indiceApi, apisWeb *lista[100]){
    //consulta si tengo un activo en especifico
    string respuesta;

    respuesta = get(indiceApi, lista);
    if (respuesta.find(simbolo) != string::npos){
        return true;
    }

    return false;
}

//##### Modulo . #####
void compra(int opcion, int indiceApi, apisWeb *lista[100]){
    //recive la opcion del tipo de activo que se desea comprar, muestra el listado de activos, pide el simbolo del activo en especifico, la 
    //cantidad de esos activos y hace la compra, en caso de que el saldo sea insuficiente muetra un mensaje
    string simbolo;
    int cantidad;
    string msg;
    string endpoint;
    string comando;
    double precio;
    double saldo;

    msg = "Ingrese simbolo: ";
    msg = traduccion(config, &msg);
    cout << msg;
    cin >> simbolo;
    msg = "Cantidad: ";
    msg = traduccion(config, &msg);
    cout << msg;
    cin >> cantidad;

    precio = obtenerPrecio(simbolo, indiceApi, lista);
    saldo = obtenerSaldo(indiceApi, lista);

    if (precio * cantidad > saldo) {
        msg = "Saldo insuficiente";
        msg = traduccion(config, &msg);
        cout << traduccion(config, &msg) << endl;
        return;
    }

    endpoint = lista.apis[indiceApi];
    comando =
        "curl -s -X POST \"" + endpoint + "\" "
        "-H \"Authorization: Bearer " + token + "\" "
        "-H \"Content-Type: application/json\" "
        "-d \"{\\\"symbol\\\":\\\"" + simbolo +
        "\\\",\\\"quantity\\\":" + to_string(cantidad) + "}\"";

    system(comando.c_str());
    msg = "Compra realizada";
    msg = traduccion(config, &msg);
    cout << msg << endl;
}

//##### Modulo . #####
void venta(int opcion, int indiceApi, apisWeb lista){
    //recive la opcion del tipo de activo que se desea comprar, muestra el listado de activos de ese tipo que tienes para vender, pide el
    //simbolo y la cantidad de ese activo que deseas vender y las vende en caso contrario muestra un mensaje
    string simbolo;
    int cantidad;
    string msg;
    string comando;
    string endpoint;

    msg = "Ingrese simbolo: ";
    cout << traduccion(config, &msg);
    msg = msg;
    cin >> simbolo;

    if (!tengoActivo(simbolo, indiceApi, lista)) {
        msg = "No posee este activo";
        msg = traduccion(config, &msg);
        cout << msg << endl;
        return;
    }

    msg = "Cantidad: ";
    msg = traduccion(config, &msg);
    cout << msg;
    cin >> cantidad;

    endpoint = lista.apis[indiceApi];
    comando =
        "curl -s -X POST \"" + endpoint + "\" "
        "-H \"Authorization: Bearer " + token + "\" "
        "-H \"Content-Type: application/json\" "
        "-d \"{\\\"symbol\\\":\\\"" + simbolo +
        "\\\",\\\"quantity\\\":" + to_string(cantidad) + "}\"";
    system(comando.c_str());

    msg = "Venta realizada";
    msg = traduccion(config, &msg);
    cout << msg << endl;
}

//##### Modulo . #####
vector<double> obtenerHistorial(const string& simbolo){
    vector<double> precios;
    string respuesta;

    respuesta = get(1, listaApis[0]); // suponiendo API precios
    size_t pos = 0;

    while ((pos = respuesta.find("price", pos)) != string::npos) {
        string precioStr = extraerValor(respuesta.substr(pos), "price");
        precios.push_back(atof(precioStr.c_str()));
        pos += 10;
    }

    return precios;
}

//##### Modulo . #####
double mediaMovil(const vector<double>& datos, int periodo){
    double suma;

    if (datos.size() < periodo) {
        return 0.0;
    }
    suma = 0.0;
    for (int i = datos.size() - periodo; i < datos.size(); i++) {
        suma += datos[i];
    }

    return suma / periodo;
}

//##### Modulo . #####
double calcularRSI(const vector<double>& datos){
    double ganancias;
    double perdidas;
    double cambio;
    double rs;

    if (datos.size() < 2) {
        return 0.0;
    }
    ganancias = 0.0;
    perdidas = 0.0;

    for (size_t i = 1; i < datos.size(); i++) {
        cambio = datos[i] - datos[i - 1];
        if (cambio > 0){
            ganancias += cambio;
        }
        else{
            perdidas -= cambio;
        }
    }

    if (perdidas == 0) {
        return 100.0;
    }
    rs = ganancias / perdidas;
    return 100 - (100 / (1 + rs));
}
    
//##### Modulo . #####
bool volumenAlto(const string& simbolo){
    string respuesta;
    string volumenStr;
    double volumen;

    respuesta = get(1, listaApis[0]);
    volumenStr = extraerValor(respuesta, "volume");
    volumen = atof(volumenStr.c_str());

    return volumen > 1000000;
}

//##### Modulo . #####
double calcularEMA(const vector<double>& datos, int periodo){
    double k;
    double ema;

    if (datos.size() < periodo) {
        return 0.0;
    }
    k = 2.0 / (periodo + 1);
    ema = datos[0];
    for (size_t i = 1; i < datos.size(); i++) {
        ema = datos[i] * k + ema * (1 - k);
    }

    return ema;
}

//##### Modulo . #####
bool evaluarCompra(const string& simbolo){
    vector<double> datos;
    double rsi;
    double ema;
    double precioActual;

    datos = obtenerHistorial(simbolo);
    rsi = calcularRSI(datos);
    ema = calcularEMA(datos, 10);
    precioActual = datos.back();
    if (rsi < 30 && precioActual > ema && volumenAlto(simbolo)) {
        return true;
    }

    return false;
}

//##### Modulo . #####
bool evaluarVenta(const string& simbolo, double precioCompra){
    vector<double> datos;
    double rsi;
    double precioActual;
    double ganancia;

    datos = obtenerHistorial(simbolo);
    rsi = calcularRSI(datos);
    precioActual = datos.back();
    ganancia = (precioActual - precioCompra) / precioCompra;
    if (rsi > 70 || ganancia > config.takeProfit || ganancia < -config.stopLoss) {
        return true;
    }

    return false;
}

//##### Modulo . #####
void compraVentaAutomatica(string simbolo, int opcion, apisWeb *lista[100]){
    //recibe el simbolo, la opcion y la lista de apis busca la api correcta evaluando la opcion y el simbolo y opera
}

//##### Modulo . #####
void verOperaciones(){
    string msg;

    ifstream archivo("operaciones.txt");

    if (!archivo.is_open()) {
        msg = "No hay operaciones registradas";
        cout << traduccion(config, &msg) << endl;
        return;
    }

    msg = "\n===== HISTORIAL DE OPERACIONES =====";
    cout << traduccion(config, &msg) << endl;

    msg = "TIPO | SIMBOLO | CANTIDAD | PRECIO";
    cout << traduccion(config, &msg) << endl;

    cout << "------------------------------------------\n";

    string linea;

    while (getline(archivo, linea)) {

        // Se espera formato: tipo,simbolo,cantidad,precio
        stringstream ss(linea);
        string tipo, simbolo, cantidad, precio;

        getline(ss, tipo, ',');
        getline(ss, simbolo, ',');
        getline(ss, cantidad, ',');
        getline(ss, precio, ',');

        cout << tipo << " | "
             << simbolo << " | "
             << cantidad << " | "
             << precio << endl;
    }

    archivo.close();

    msg = "==========================================";
    cout << traduccion(config, &msg) << endl;
}

//##### Modulo . #####
void submenuOperaciones(int opcionMenu){
    int opcion;
    string msg;

    do {
        msg = "\n--- OPERAR ---\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "1. Comprar\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "2. Vender\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "3. Ver operaciones\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "4. Trading automatico\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "5. Volver\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "Opcion: ";
        msg = traduccion(config, &msg);
        cout << msg;

        cin >> opcion;

        string refresh_local;
        conseguirToken(&token, &refresh_local);

        switch (opcion) {
            case 1: 
                compra(); 
                break;
            case 2: 
                venta(); 
                break;
            case 3: 
                verOperaciones(); 
                break;
            case 4: 
                compraVentaAutomatica(); 
                break;
            case 5:
                msg = "Volviendo...\n";
                msg = traduccion(config, &msg);
                cout << msg;
                break;

            default:
                msg = "Opcion invalida\n";
                msg = traduccion(config, &msg);
                cout << msg;
        }

    } while (opcion != 5);
}

//##### Modulo . #####
void menuActivo(int opcionMenu, const string& nombre){
    int opcion;
    string msg;

    do {
        msg = "\n=== " + nombre + " ===\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "1. Ver lista de activos\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "2. Operar\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "3. Volver\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "Opcion: ";
        msg = traduccion(config, &msg);
        cout << msg;

        cin >> opcion;

        switch (opcion) {
            case 1: 
                mostrar(opcionMenu); 
                break;
            case 2: 
                submenuOperaciones(opcionMenu); 
                break;
            case 3:
                msg = "Volviendo...\n";
                msg = traduccion(config, &msg);
                cout << msg;
                break;

            default:
                msg = "Opcion invalida\n";
                msg = traduccion(config, &msg);
                cout << msg;
        }

    } while (opcion != 3);
}

//##### Modulo . #####
void menuPrincipal(){
    int opcion;
    string msg;

    do {
        cout << "\n=================================\n";
        msg = "BOT INVERSION IOL\n";
        msg = traduccion(config, &msg);
        cout << msg;
        cout << "=================================\n";

        msg = "1  - Estado de cuenta\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "2  - Acciones\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "3  - CEDEARs\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "4  - Bonos\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "5  - Opciones\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "6  - Cauciones\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "7  - FCI\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "8  - ON\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "9  - Portafolios\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "10 - Dolar MEP\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "11 - Licitaciones\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "12 - Configuracion\n";
        msg = traduccion(config, &msg);
        cout << msg;

        msg = "13 - Salir\n";
        msg = traduccion(config, &msg);
        cout << msg;

        cout << "---------------------------------\n";
        msg = "Seleccione una opcion: ";
        msg = traduccion(config, &msg);
        cout << msg;
        cin >> opcion;

        switch (opcion) {
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
                menuActivo(10, "DolarMEP"); 
                break;
            case 11: 
                menuActivo(11, "Licitaciones"); 
                break;
            case 12: 
                menuConfiguracion(); 
                break;
            case 13:
                msg = "Cerrando sistema...\n";
                msg = traduccion(config, &msg);
                cout << msg;
                break;

            default:
                msg = "Opcion invalida\n";
                msg = traduccion(config, &msg);
                cout << msg;
        }

    } while (opcion != 13);
}

//##### Modulo (funcion principal). #####
//Se ejecutan los comandos necesarios para que el program se ejecute y funcione
int main(){
    string msg;

    // Inicializar configuración y APIs
    inicializarSistema(&config, &configurar, &listApis, listaApis);

    // Pedir credenciales
    msg = "Ingrese usuario: ";
    cout << traduccion(config, &msg);
    cin >> usuario;

    msg = "Ingrese password: ";
    cout << traduccion(config, &msg);
    cin >> password;

    // Login
    if (!login(usuario, password)) {
        msg = "No se pudo iniciar sesion\n";
        cout << traduccion(config, &msg);
        return 1;
    }

    // Lanzar menú principal
    menuPrincipal();

    return 0;
}