#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct Tarea {
    int TareaID; //numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; //entre 10 -100
} typedef Tarea;

void cargarTareas(Tarea **Tareas, int cantidadTareas);
void listarTareas(Tarea **Tareas, int cantidadTareas, Tarea **TareasRealizadas);
void listarTareasPorEstado(Tarea **Tareas, int cantidadTareas, Tarea **TareasRealizadas);
Tarea * BusquedaPorPalabra (Tarea **Tareas, int cantidadTareas, Tarea **TareasRealizadas, char *palabraclave);
Tarea* BusquedaPorID(Tarea **Tareas, int cantidadTareas,Tarea **TareasRealizadas,int idTarea);
void liberarMemoria (Tarea **Tareas,int cantidadTareas);

int main() {
    int cantidadTareas;

    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d",&cantidadTareas);

    Tarea **Tareas;
    Tareas = (Tarea **)malloc(sizeof(Tarea ) * cantidadTareas);
    Tarea **TareasRealizadas;
    TareasRealizadas = (Tarea **)malloc(sizeof(Tarea ) * cantidadTareas);

    cargarTareas(Tareas,cantidadTareas);
    listarTareas(Tareas,cantidadTareas,TareasRealizadas);
    listarTareasPorEstado(Tareas,cantidadTareas,TareasRealizadas);

    char *palabraclave = "hola";
    Tarea * TareaSolicitadaPorPalabra;
    TareaSolicitadaPorPalabra = (Tarea*)malloc(sizeof(Tarea));
    TareaSolicitadaPorPalabra = BusquedaPorPalabra(Tareas, cantidadTareas,TareasRealizadas, palabraclave);
     printf("------------TAREA SOLICITADA [%d]-------------\n",TareaSolicitadaPorPalabra->TareaID);
        printf("Descripción:\n ");
        puts(TareaSolicitadaPorPalabra->Descripcion);
        printf("\nDuración: %d\n", TareaSolicitadaPorPalabra->Duracion);    
    
    Tarea *TareaSolicitadaPorID;
    TareaSolicitadaPorID = (Tarea * )malloc(sizeof(Tarea));
    TareaSolicitadaPorID = BusquedaPorID(Tareas,cantidadTareas,TareasRealizadas,1);
     printf("------------TAREA SOLICITADA [%d]-------------\n",TareaSolicitadaPorID->TareaID);
        printf("Descripción:\n ");
        puts(TareaSolicitadaPorID->Descripcion);
        printf("\nDuración: %d\n", TareaSolicitadaPorID->Duracion);   
    liberarMemoria(Tareas,cantidadTareas);
    liberarMemoria(TareasRealizadas,cantidadTareas);

}

void cargarTareas(Tarea **Tareas, int cantidadTareas) {
    srand((unsigned)time(NULL));
    char *Buffer = (char *)malloc(sizeof(char) * 500);

    for (int i = 0; i < cantidadTareas; i++)
    {
        Tareas[i] = (Tarea *)malloc(sizeof(Tarea)) ;
        printf("------------CARGAR TAREA [%d]-------------\n",i);
        fflush(stdin);
        Tareas[i]->TareaID = i;

        printf("Ingrese la descripcion de la tarea: ");
        gets(Buffer);
        Tareas[i]->Descripcion = (char *)malloc(strlen(Buffer) +1);
        strcpy(Tareas[i]->Descripcion,Buffer);

        Tareas[i]->Duracion = rand()%101+10;
    }
    
}
void listarTareas(Tarea **Tareas, int cantidadTareas, Tarea **TareasRealizadas) {

    int realizada;
    for (int i = 0; i < cantidadTareas; i++)
    {
        printf("------------TAREA [%d]-------------\n",Tareas[i]->TareaID);
        printf("Descripción:\n ");
        puts(Tareas[i]->Descripcion);
        printf("\nDuración: %d", Tareas[i]->Duracion );
        printf("\nIngrese 1 si la tarea ya fue realizada. De lo contrario presione cualquier numero: ");
        scanf("%d",&realizada);
        TareasRealizadas[i] = NULL ;
        if (realizada == 1)
        {
            TareasRealizadas[i]= Tareas[i];
            Tareas[i] = NULL;
        }
    }
    
}
void listarTareasPorEstado(Tarea **Tareas, int cantidadTareas, Tarea **TareasRealizadas) {
  printf("\n---------------TAREAS PENDIENTES---------------\n"); 
    for (int i = 0; i < cantidadTareas; i++)
    {
        
        if (Tareas[i] != NULL)
        {
            printf("TAREA [%d]\n",Tareas[i]->TareaID);
            printf("Descripción:\n ");
            puts(Tareas[i]->Descripcion);
            printf("\nDuración: %d", Tareas[i]->Duracion );
        }
    }
    printf("\n---------------TAREAS REALIZADAS---------------\n");
    for (int j= 0; j< cantidadTareas; j++)
    {
        
        if (TareasRealizadas[j] != NULL)
        {
            printf("TAREA [%d]\n",TareasRealizadas[j]->TareaID);
            printf("Descripción:\n ");
            puts(TareasRealizadas[j]->Descripcion);
            printf("\nDuración: ", TareasRealizadas[j]->Duracion );
        }
    }
    
}

Tarea * BusquedaPorPalabra (Tarea **Tareas, int cantidadTareas, Tarea **TareasRealizadas, char *palabraclave){
   
    for (int i = 0; i < cantidadTareas; i++)
    {
        if (TareasRealizadas[i]!=NULL)
        {
            if (strstr(TareasRealizadas[i]->Descripcion,palabraclave) != NULL) 
            {
                return TareasRealizadas[i];
            }    
        }else {
                if (Tareas[i] != NULL)
                {
                    if (strstr(Tareas[i]->Descripcion,palabraclave) != NULL)
                    {
                        return Tareas[i];
                    }
                 }
            
            }
      
    }
    printf("NULL");
    return NULL;
}  
Tarea* BusquedaPorID(Tarea **Tareas, int cantidadTareas,Tarea **TareasRealizadas,int idTarea){
    for (int i = 0; i < cantidadTareas; i++)
    {
        if (TareasRealizadas[i]!=NULL)
        {
            if (TareasRealizadas[i]->TareaID == idTarea) 
            {
                return TareasRealizadas[i];
            } 
        }else {
                if (Tareas[i] != NULL)
                {
                    if (Tareas[i]->TareaID == idTarea) 
                    {
                        return Tareas[i];
                    }
                 }
            
            }
    }
    printf("NULL");
     return NULL;
}

void liberarMemoria (Tarea **Tareas,int cantidadTareas) {

    for (int i = 0; i < cantidadTareas; i++)
    {
        if (Tareas[i] != NULL) free(Tareas[i]->Descripcion);
        free(Tareas[i]);
    }
    free(Tareas);
}
