#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_CAR 50
#define MIN_DUR 10
#define MAX_DUR 100

//Estructuras
typedef struct Tarea Tarea;
typedef struct Nodo Nodo;

struct Tarea
{
    int TareaID; // Empieza en 1000
    char *Descripcion;
    int Duracion; // entre 10 – 100
};

struct Nodo
{
    Tarea Tarea;
    struct Nodo *Siguiente;
};

//Funciones
int insertarMenu();
Nodo *crearNodo(int ID, char *descripcion, int duracion);
void insertarNodo(Nodo **Start, Nodo *NNodo);
Nodo buscarNodo(Nodo **Start, int buscarID);
void mostarTareas(Nodo **Start);
void eliminarNodo(Nodo **Start, int id);
void buscarTareaPorId(Nodo **lista1, Nodo **lista2, int id);
void buscarTareaPorPalabraClave(Nodo **lista1, Nodo **lista2, char * palabraClave);
//Main
int main(){
    //Crear lista vacia de tareas
    Nodo *startPendiente = NULL;
    Nodo *startRealizada = NULL;
    //Variables
    int ID = 1000, menu, duracion, respuesta, idCambiar;
    char descripcion[MAX_CAR];
    do
    {
        menu=insertarMenu();
        switch (menu)
        {
        //Cargar Tareas
        case 1:
            do
            {
                printf("----------INGRESAR TAREA----------\n");
                do
                {
                    printf("Duracion de la tarea: ");
                    scanf("%d", &duracion);
                    fflush(stdin);
                } while (duracion < 10 || duracion > 100);
                printf("\nDescripcion de la tarea: ");
                gets(descripcion);
                fflush(stdin);
                insertarNodo(&startPendiente, crearNodo(ID, descripcion, duracion));
                puts("Desea Cargar mas Datos? 1:SI 0:NO");
                fflush(stdin);
                scanf("%d", &respuesta);
            } while (respuesta != 0);
            break;

        //Cambiar Tareas de Pendientes a Realizadas
        case 2:
            //Ingresar ID de tarea a cambiar
            puts("Ingresar el ID de la tarea que cambiara");
            scanf("%d", &idCambiar);
            fflush(stdin);
            //buscarNodo devuelve el Nodo a cambiar en tareaCambiar
            Nodo tareaCambiar = buscarNodo(&startPendiente, idCambiar);
            //Inserto tareaCambiar en tareas realizadas
            insertarNodo(&startRealizada, &tareaCambiar);
            //Elimino la tarea de pendientes
            eliminarNodo(&startPendiente, idCambiar);
            puts("Operacion Exitosa");
            break;

        //Mostrar Tareas Pendientes
        case 3:
            if (startPendiente == NULL)
            {
                puts("No hay tareas pendientes");
            }else
            {
                puts("---------Tareas Pendientes---------");
                mostarTareas(&startPendiente);
            }
            break;

        //Mostrar Tareas Realizadas
        case 4: 
            if (startRealizada == NULL)
            {
                puts("No hay tareas realizadas");
            }else{
                puts("---------Tareas Realizadas---------");
                mostarTareas(&startRealizada);
            }    
            break;

        //Buscar Tarea por ID
        case 5:
            puts("Ingresar el ID de la tarea a buscar: ");
            fflush(stdin);
            scanf("%d", idCambiar);
            buscarTareaPorId(&startPendiente, &startRealizada, idCambiar);
            break;
        
        //Buscar Tarea por Palabra Clave
        case 6:
            puts("Ingresar palabra clave para buscar: ");
            //Asignacion dinamica de memoria de palabra a buscar
            char *palabraClave = (char*)malloc(MAX_CAR * sizeof(char));
            fflush(stdin);
            gets(palabraClave);
            buscarTareaPorPalabraClave(&startPendiente, &startRealizada, palabraClave);
            free(palabraClave);
            break;
        //Cerrar Sesion
        case 7:
            puts("*******Sesion Cerrada*******");
            break;            
        default:
            break;
        }
    } while (menu != 7);
    
    return 0;
}

//Insertar Menu
int insertarMenu(){
    int menu;
    printf("---------Menu---------");
    printf("\n\t1.- Ingresar Tarea");
    printf("\n\t2.- Cambiar tarea pendiente a realizada");
    printf("\n\t3.- Listar Tareas Pendientes");
    printf("\n\t4.- Ingresar Tareas Realizadas");
    printf("\n\t5.- Buscar Tarea por su ID");
    printf("\n\t6.- Buscar Tarea por palabra clave");
    printf("\n\t7.- Cerrar Sesion");
    printf("\n\tSeleccione: ");
    scanf("%d", &menu);
    return menu;
}

//Crear Nodo
Nodo *crearNodo(int ID, char *descripcion, int duracion){
    //Creo Nuevo Nodo
    Nodo * NNodo = (Nodo *)malloc(sizeof(Nodo));
    //Guarda ID y lo incrementa
    NNodo->Tarea.TareaID = ID;
    ID++;
    NNodo->Tarea.Descripcion=(char*)malloc(MAX_CAR * sizeof(char));
    strcpy(NNodo->Tarea.Descripcion, descripcion);
    NNodo->Tarea.Duracion = duracion;
    NNodo->Siguiente = NULL;
    return NNodo;
}

//Insertar Nodo
void insertarNodo(Nodo **Start, Nodo *NNodo){
    NNodo->Siguiente = *Start;
    *Start = NNodo;
}

//Buscar Nodo con ID
Nodo buscarNodo(Nodo **Start, int buscarID){
    Nodo *aux = *Start;
    //El bucle recorre hasta encontrar el ID de la tarea
    while (aux && aux->Tarea.TareaID != buscarID)
    {
        aux = aux->Siguiente;
    }

    //Una vez encontrada la tarea, se retorna aux
    return *aux;
}

//Eliminar Nodo
void eliminarNodo(Nodo **Start, int id){
    Nodo **aux = Start;
    //Recorrer tareas hasta encontrar la tarea con el ID indicado
    while (*aux != NULL && (*aux)->Tarea.TareaID != id)
    {
        aux = &(*aux)->Siguiente;
    }
    
    //Si aux no es NULL
    if (*aux)
    {
        Nodo *temp = *aux; //Copio aux en variable temporal
        *aux = (*aux)->Siguiente; //aux toma el valor del siguiente nodo
        free(temp);
    }
}

//Mostrar Tareas
void mostarTareas(Nodo **Start){
    Nodo *aux = *Start;
    //Controlo que el nodo no esté vacío
    while (aux != NULL)
    {
        printf("\nTarea ID: %d", aux->Tarea.TareaID);
        puts("Descripcion de la tarea: ");
        puts(aux->Tarea.Descripcion);
        printf("\nDuracion de la tarea: %d", aux->Tarea.Duracion);

        //Paso al siguiente Nodo
        aux = aux->Siguiente;
    }
}

//Buscar Tarea por ID
void buscarTareaPorId(Nodo **lista1, Nodo **lista2, int id){
    //Creo Bandera para pendientes o realizadas
    int bandera = 0;
    //Guardo listas en auxiliares
    Nodo **aux1 = lista1, **aux2 = lista2;
    
    //Controlo que las listas no estén vacías
    if (*aux1 == NULL && *aux2 == NULL)
    {
        puts("No hay listas de tareas disponibles");
    }else
    {
        while (*aux1 != NULL && bandera == 0)
        {
            if ((*aux1)->Tarea.TareaID == id)
            {
                puts("********RESULTADOS TAREAS PENDIENTES********");
                printf("Tarea ID: %d", (*aux1)->Tarea.TareaID);
                puts("Descripcion de la tarea: ");
                puts((*aux1)->Tarea.Descripcion);
                printf("Duracion de la tarea: %d", (*aux1)->Tarea.Duracion);

                //Cambio la bandera a 1
                bandera = 1;
            }

            //Paso al siguiente nodo
            *aux1 = (*aux1)->Siguiente;
        }  
    }

    //En caso de no haberse encontrado en las tareas pendientes
    if (bandera == 0)
    {
        while (*aux2 != NULL && bandera == 0)
        {
            if ((*aux2)->Tarea.TareaID == id)
            {
                puts("********RESULTADOS TAREAS REALIZADAS********");
                printf("Tarea ID: %d", (*aux2)->Tarea.TareaID);
                puts("Descripcion de la tarea: ");
                puts((*aux2)->Tarea.Descripcion);
                printf("Duracion de la tarea: %d", (*aux2)->Tarea.Duracion);
                bandera == 1;
            }

            //Paso al siguiente nodo
            *aux2 = (*aux2)->Siguiente;
        }  
    }

    //En caso de no haberse encontrado en ninguna lista
    if(bandera == 0)
    {
        puts("No hay resultados vinculados con este ID");
    }
}

//Buscar Tarea por palabra clave
void buscarTareaPorPalabraClave(Nodo **lista1, Nodo **lista2, char * palabraClave){
    //Creo Bandera para pendientes o realizadas
    int bandera = 0;
    //Guardo listas en auxiliares
    Nodo **aux1 = lista1, **aux2 = lista2;
    
    //Controlo que las listas no estén vacías
    if (*aux1 == NULL && *aux2 == NULL)
    {
        puts("No hay listas de tareas disponibles");
    }else
    {
        while (*aux1 != NULL && bandera == 0)
        {
            if (strstr((*aux1)->Tarea.Descripcion, palabraClave))
            {
                puts("********RESULTADOS TAREAS PENDIENTES********");
                printf("Tarea ID: %d", (*aux1)->Tarea.TareaID);
                puts("Descripcion de la tarea: ");
                puts((*aux1)->Tarea.Descripcion);
                printf("Duracion de la tarea: %d", (*aux1)->Tarea.Duracion);

                //Cambio la bandera a 1
                bandera = 1;
            }

            //Paso al siguiente nodo
            *aux1 = (*aux1)->Siguiente;
        }  
    }

    //En caso de no haberse encontrado en las tareas pendientes
    if (bandera == 0)
    {
        while (*aux2 != NULL && bandera == 0)
        {
            if (strstr((*aux2)->Tarea.Descripcion, palabraClave))
            {
                puts("********RESULTADOS TAREAS REALIZADAS********");
                printf("Tarea ID: %d", (*aux2)->Tarea.TareaID);
                puts("Descripcion de la tarea: ");
                puts((*aux2)->Tarea.Descripcion);
                printf("Duracion de la tarea: %d", (*aux2)->Tarea.Duracion);

                //Cambio la bandera a 1
                bandera = 1;
            }

            //Paso al siguiente nodo
            *aux2 = (*aux2)->Siguiente;
        }  
    }

    //En caso de no haberse encontrado en ninguna lista
    if (bandera == 0)
    {
        puts("No hay resultados que contengan la palabra clave");
    }
}