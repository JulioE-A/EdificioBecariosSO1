#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <ctime>


using namespace std;
sem_t tareas;
sem_t imprimir;
int tareasTerminadas = 0;
int tareasTotales = 10;
int listaTareas[20][2];
bool entorpecedor = false;

void resolverTarea(){

    int i, j;

    for(i = 0; i < 20000; i++){
        for(j = 0; j < 10000; j++){
        ;
	    }
    }

}


void *becario(void *dato){
	int *id;

	id=(int *)dato;
	int horasTrabajadas = 0;
	while((horasTrabajadas+listaTareas[tareasTerminadas][1])<8){
		int tareaActual = tareasTerminadas;
		tareasTerminadas++;
		bool pegado = false;
		int molestado = 0;
		
		sem_wait(&tareas);
		
		if(!entorpecedor){
			entorpecedor = true;
			pegado = true;
			sem_wait(&imprimir);
			cout<<"Entorpecedor pegado a becario "<<*id<<endl;
			sem_post(&imprimir);	
		}
		
		sem_wait(&imprimir);
		cout<<"Becario "<<*id<<" escogiendo tarea"<<endl;
		resolverTarea();
		sem_post(&imprimir);
		
		sem_post(&tareas);	
		
		
		//resolviendo problema
		for(int i=0; i<listaTareas[tareaActual][1];i++){
			resolverTarea();
			if(pegado){
				resolverTarea();
				molestado++;
				horasTrabajadas++;
			}
			horasTrabajadas++;
		}
		//resolviendo problema
		
		if(pegado){
			entorpecedor = false;
		}
		
		sem_wait(&imprimir);
		cout<<"Becario "<<*id<<" resolvio tarea "<<endl;
		sem_post(&imprimir);
		
	}
	sem_wait(&imprimir);
	cout<<"Becario: "<<*id<<" horas trabajadas: "<<horasTrabajadas<<endl;
	sem_post(&imprimir);
}


int main(int argc, char *argv[])
{
	int status;
	int ids[5]={1,2,3,4,5};
    sem_init(&tareas,0, 1);
    sem_init(&imprimir,0,1);
    srand(time(NULL));
    
    for (int i =0; i<20;i++){
		
		int random = rand()%(3-1+1)+1;
		listaTareas[i][0]=i;
		listaTareas[i][1]=random;
	}
    
    // creating thread objects
    pthread_t thrd_1;
    pthread_t thrd_2;
    pthread_t thrd_3;
    pthread_t thrd_4;
    pthread_t thrd_5;
    pthread_t thrd_6;
 	
    
    // create thread
    pthread_create(&thrd_1,NULL,&becario,&ids[0]);
    
    pthread_create(&thrd_2,NULL,&becario,&ids[1]);
    
	pthread_create(&thrd_3,NULL,&becario,&ids[2]);
	
	pthread_create(&thrd_4,NULL,&becario,&ids[3]);
	   
    pthread_create(&thrd_5,NULL,&becario,&ids[4]);
    
	pthread_create(&thrd_6,NULL,&becario,&ids[5]);
    
    

    pthread_join(thrd_1, (void **)&status);
	pthread_join(thrd_2, (void **)&status);
    //pthread_join(thrd_3, (void **)&status);
    //pthread_join(thrd_4, (void **)&status);
    //pthread_join(thrd_5, (void **)&status);
    //pthread_join(thrd_6, (void **)&status);



    system("PAUSE");
    return 0;
}
