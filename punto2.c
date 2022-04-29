#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct Tarea {
    int TareaID; //numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; //entre 10 -100
} typedef Tarea;
struct Nodo {
    Tarea T;
    struct Nodo *siguiente;
}typedef nodo;

int tareaspendientes = 0,tareasrealizadas = 0;

nodo *crearListaVacia(nodo **listaTareas);
nodo *cargarTarea(int i); //crearNodo
void cargaListaTareas(nodo **Tareas,int i); //insertar nodo a la lista
void listarTarea(nodo *Tareas);
void listarTareas(nodo **Tareas, int cantidadTareas, nodo **TareasRealizadas);
void listarTareasPorEstado(nodo *Tareas,int cantidadTareas);
nodo *BusquedaPorPalabra(nodo **Tareas, char *palabraclave);
nodo *BusquedaPorID(nodo **Tareas, int idTarea);

int main() {
    //si devuelvo un puntero simple, no mando nada como paramentro y trabajo sin * en la funcion
    //si devuelvo un void, mando un puntero doble y al puntero doble lo trabajo con * dentro de la fcion

    nodo *Tareas; //cabecera lista de tareas
    crearListaVacia(&Tareas);
    nodo *TareasRealizadas;
    crearListaVacia(&TareasRealizadas);
 
    int cantidadTareas;
    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d",&cantidadTareas);

    
    for (int i = 0; i < cantidadTareas; i++)
    {
        cargaListaTareas(&Tareas,i);
    }
    listarTareas(&Tareas, cantidadTareas, &TareasRealizadas);

    printf("\nTAREAS PENDIENTES\n");
    nodo *Aux = Tareas;
    while (Aux != NULL)
    {
        listarTarea(Aux);
        Aux = Aux->siguiente;
    }
    printf("\nTAREAS REALIZADAS\n");
    Aux = TareasRealizadas;
    while (Aux != NULL)
    {
        listarTarea(Aux);
        Aux = Aux->siguiente;
    }

    char *palabraclave = "hola";
    if(BusquedaPorPalabra(&Tareas, palabraclave)){
        printf("\n\nTAREA SOLICITADA");
        listarTarea(BusquedaPorPalabra(&Tareas, palabraclave));
    } else {
        if (BusquedaPorPalabra(&TareasRealizadas, palabraclave))
        {
            printf("\n\nTAREA SOLICITADA");
            listarTarea(BusquedaPorPalabra(&TareasRealizadas, palabraclave));
        } else {
            printf("\nNo se encontro la tarea solicitada\n");
        }      
    }   
    if(BusquedaPorID(&Tareas, 1)){
        printf("\n\nTAREA SOLICITADA");
        listarTarea(BusquedaPorID(&Tareas, 1));
    } else {
        if (BusquedaPorID(&TareasRealizadas, 1))
        {
            printf("\n\nTAREA SOLICITADA");
            listarTarea(BusquedaPorID(&TareasRealizadas, 1));
        } else {
            printf("\nNo se encontro la tarea solicitada\n");
        }      
    }   
}

nodo *crearListaVacia(nodo **listaTareas) {
    *listaTareas = NULL;
}
nodo * cargarTarea(int i) {
    srand((unsigned)time(NULL));

    nodo *nuevo;
    char *Buffer = (char *)malloc(sizeof(char)*500);

    nuevo = (nodo *)malloc(sizeof(nodo));
    printf("------------CARGAR TAREA [%d]-------------\n",i);

    nuevo->T.TareaID = i;

    fflush(stdin);
    printf("Ingrese la descripcion de la tarea: ");
    gets(Buffer);
    nuevo->T.Descripcion = (char *)malloc(strlen(Buffer)+1);
    strcpy(nuevo->T.Descripcion,Buffer);
    free(Buffer);

    nuevo->T.Duracion = rand()%101+10;

    nuevo->siguiente = NULL;
    return nuevo;
}
void cargaListaTareas(nodo **Tareas, int i){ 
    nodo *TareasAux = *Tareas;
    nodo *nuevo = cargarTarea(i);
    if (TareasAux != NULL)
    {
         while (TareasAux ->siguiente)
        {
            TareasAux = TareasAux->siguiente;
        }
        TareasAux->siguiente = nuevo;
    } else {
        *Tareas=nuevo;
    }
}
void listarTareas(nodo **Tareas, int cantidadTareas, nodo **TareasRealizadas) {
    nodo *TareasAux,*siguienteAux;
    crearListaVacia(&TareasAux);
    int realizada;
    
    while (*Tareas!=NULL)
    {
        listarTarea(*Tareas);
        printf("\nIngrese 1 si la tarea ya fue realizada. De lo contrario presione cualquier numero: ");
        scanf("%d",&realizada);
        siguienteAux = (*Tareas)->siguiente;
        if (realizada == 1)
        {
            (*Tareas)->siguiente = *TareasRealizadas;
            *TareasRealizadas = *Tareas; 
        } else {
            (*Tareas)->siguiente = TareasAux;
            TareasAux = *Tareas; 
        }
        *Tareas = siguienteAux;
    }
    *Tareas = TareasAux;
     
}
void listarTarea(nodo *Tareas) {
    if (Tareas != NULL)
    {
        printf("\n-------------TAREA[%d]-------------",Tareas->T.TareaID);
        printf("Descripcion: ");
        puts(Tareas->T.Descripcion);
        printf("Duracion: %d\n",Tareas->T.Descripcion);
    }  
}


nodo * BusquedaPorPalabra (nodo **Tareas, char *palabraclave){
   nodo *TareasAux = *Tareas;
    while (*Tareas != NULL)
    {
            if (strstr(TareasAux->T.Descripcion,palabraclave) != NULL) 
            {
                return TareasAux;
            } 
            TareasAux = TareasAux->siguiente;
    }
    return NULL;
}  
nodo *BusquedaPorID(nodo **Tareas, int idTarea) {
    nodo *TareasAux = *Tareas;
    while (*Tareas != NULL)
    {
            if (TareasAux->T.TareaID) 
            {
                return TareasAux;
            } 
            TareasAux = TareasAux->siguiente;
    }
    return NULL;
}
