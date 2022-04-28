#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Tarea {
    int TareaID; //numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; //entre 10 -100
} typedef Tarea;

void cargarTareas(Tarea **Tareas, int cantidadTareas);
void listarTareas(Tarea **Tareas, int cantidadTareas, Tarea **TareasRealizadas);
void listarTareasPorEstado(Tarea **Tareas, int cantidadTareas, Tarea **TareasRealizadas);
Tarea* BuscarTarea(Tarea **Tareas, int cantidadTareas,Tarea **TareasRealizadas,int idTarea);
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
    // listarTareasPorEstado(Tareas,cantidadTareas,TareasRealizadas);
    Tarea *TareaSolicitada;
    TareaSolicitada = (Tarea * )malloc(sizeof(Tarea));
    TareaSolicitada = BuscarTarea(Tareas,cantidadTareas,TareasRealizadas,1);
     printf("------------TAREA SOLICITADA [%d]-------------\n",TareaSolicitada->TareaID);
        printf("Descripción:\n ");
        puts(TareaSolicitada->Descripcion);
        printf("\nDuración: ", TareaSolicitada->Duracion );

    

    
}

void cargarTareas(Tarea **Tareas, int cantidadTareas) {
    srand((unsigned)time(NULL));

    for (int i = 0; i < cantidadTareas; i++)
    {
        Tareas[i] = (Tarea *)malloc(sizeof(Tarea)) ;
        printf("------------CARGAR TAREA [%d]-------------\n",i);
        fflush(stdin);
        Tareas[i]->TareaID = i;
        printf("Ingrese la descripcion de la tarea: ");
        Tareas[i]->Descripcion = (char *)malloc(sizeof(char)*500);
        gets(Tareas[i]->Descripcion);
        Tareas[i]->Duracion = rand()%101+10;
        
        Tareas++;
    }
    
}
void listarTareas(Tarea **Tareas, int cantidadTareas, Tarea **TareasRealizadas) {

    int realizada;
    for (int i = 0; i < cantidadTareas; i++)
    {
        printf("------------TAREA [%d]-------------\n",Tareas[i]->TareaID);
        printf("Descripción:\n ");
        puts(Tareas[i]->Descripcion);
        printf("\nDuración: ", Tareas[i]->Duracion );
        printf("\nIngrese 1 si la tarea ya fue realizada. De lo contrario presione cualquier numero: ");
        scanf("%d",&realizada);
        TareasRealizadas[i] = (Tarea *)malloc(sizeof(Tarea)) ;
        if (realizada == 1)
        {
            TareasRealizadas[i]->TareaID = Tareas[i]->TareaID;
            TareasRealizadas[i]->Duracion = Tareas[i]->Duracion;
            TareasRealizadas[i]->Descripcion = Tareas[i]->Descripcion;
            Tareas[i] = NULL;
        } else {
            TareasRealizadas[i] = NULL;
        }
        Tareas++;
        TareasRealizadas++;
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
            printf("\nDuración: ", Tareas[i]->Duracion );
        }
        Tareas++;
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
        TareasRealizadas++;
    }
    
}
Tarea* BuscarTarea(Tarea **Tareas, int cantidadTareas,Tarea **TareasRealizadas,int idTarea){
    for (int i = 0; i < cantidadTareas; i++)
    {
        if (TareasRealizadas[i] != NULL && TareasRealizadas[i]->TareaID == idTarea )
        {
            return TareasRealizadas[i];
        }else {
            if (Tareas[i] != NULL && Tareas[i]->TareaID == idTarea )
            {
                return Tareas[i];
            } else {
                return NULL;
            }
        }
    }
    
}

