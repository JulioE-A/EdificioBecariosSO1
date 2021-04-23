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
int listaTareas[20][2];
bool entorpecedor = false;
int horasBecarios[5];

void resolverTarea(){

    int i, j;

    for(i = 0; i < 20000; i++){
        for(j = 0; j < 10000; j++){
        ;
	    }
    }

}

void escogerTarea(){

    int i, j;

    for(i = 0; i < 10000; i++){
        for(j = 0; j < 5000; j++){
        ;
	    }
    }

}


void *becario(void *dato){
	int *id;

	id=(int *)dato;
	int horasTrabajadas = 0;
	bool abandona = false;
	
	while((horasTrabajadas+listaTareas[tareasTerminadas][1])<9){
		int tareaActual = tareasTerminadas;
		tareasTerminadas++;
		bool pegado = false;
		int molestado = 0;
		
		sem_wait(&tareas);
		
		//verificar si entorpecedor esta libre
		if(!entorpecedor){
			entorpecedor = true;
			pegado = true;
			sem_wait(&imprimir);
			cout<<"Entorpecedor pegado a becario "<<*id<<endl;
			sem_post(&imprimir);	
		}
		
		
		sem_wait(&imprimir);
		cout<<"Becario "<<*id<<" escogiendo tarea"<<endl;
		escogerTarea();
		sem_post(&imprimir);
		
		sem_post(&tareas);	
		
		
		//resolviendo problema
		
		for(int i=0; i<listaTareas[tareaActual][1];i++){
			if(!abandona){
				//si sobrepasa el limite de veces molestado abandona
				if(molestado<2){
					//si el entorpecedor esta pegado se tarda el doble
					if(pegado){
						resolverTarea();
						molestado++;
						horasTrabajadas++;
						if(horasTrabajadas>=8){
							//se acaba jornada, entorpecedor abandona
							pegado = false;
							entorpecedor = false;
						}
					}
					resolverTarea();
					horasTrabajadas++;	
				
				}else{
					sem_wait(&imprimir);
					cout<<"Becario "<<*id<<" abandono tarea"<<endl;
					sem_post(&imprimir);
					abandona = true;
					molestado = 0;
				}	
				
			}
			
		}
		//resolviendo problema
		
		if(pegado){
			entorpecedor = false;
			abandona = false;
		}
		
		sem_wait(&imprimir);
		cout<<"Becario "<<*id<<" resolvio tarea "<<endl;
		sem_post(&imprimir);
		
	}
	
	horasBecarios[*id] = horasTrabajadas;
	sem_wait(&imprimir);
	cout<<"Becario "<<*id<<" parcheando"<<endl;
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
    pthread_join(thrd_3, (void **)&status);
    pthread_join(thrd_4, (void **)&status);
    pthread_join(thrd_5, (void **)&status);
    pthread_join(thrd_6, (void **)&status);

	for(int i =0; i<6;i++){
		cout<<"Becario "<<i<<" horas trabajadas: "<<horasBecarios[i]<<endl;
		
	}

    system("PAUSE");
    return 0;
}
