/* Juego de 3 en raya para un jugador contra la máquina. 
   Por Emilio J. */

#include <stdio.h>
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

/* Datos y procedimientos */

char Estado[9]= {'A','B','C','D','E','F','G','H','I'};

typedef char TipoMatriz[3][3];

void IniciarMatriz(TipoMatriz M){

     int aux=0;
     
     for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            
            M[i][j]=Estado[aux];
            aux++;
        }    
    } 
}

void LeerMatriz (TipoMatriz M){
     
     for (int i=0; i<3; i++){
     	
     	printf("                                    ");
        for (int j=0; j<3; j++){
            
            printf(" %c ", M[i][j]);
        }
        printf("\n");    
    }
}

void ModificarCampo (TipoMatriz M, char x, char z){
     
     switch(x){
            case 'A':M[0][0]=z; break;
            case 'B':M[0][1]=z; break; 
            case 'C':M[0][2]=z; break; 
            case 'D':M[1][0]=z; break; 
            case 'E':M[1][1]=z; break; 
            case 'F':M[1][2]=z; break; 
            case 'G':M[2][0]=z; break; 
            case 'H':M[2][1]=z; break; 
            case 'I':M[2][2]=z; break;
            default:
            ;          
    }
}

void buscarCampoF (TipoMatriz M, int a, int & e, int & as){
	
	/* "a" es la fila y "e" la columna */
	
	for (int i=0; i<3; i++){
		
		if (M[a][i]!='X' && M[a][i]!='*'){
			
			e++;
		}
			if (M[a][i]=='*'){
				
				as++;
			}
	}		
}

void buscarCampoC (TipoMatriz M, int & e, int a, int & as){
	
	/* "a" es la fila y "e" la columna */
	
	for (int i=0; i<3; i++){
		
		if (M[i][a]!='X' && M[i][a]!='*'){
			
			e++;
		}
			if (M[i][a]=='*'){
				
				as++;
			}
	}		
}

void buscarCampoD (TipoMatriz M, int & e, int & as){
	
	int a=0;
	
	for (int i=0; i<3; i++){
		
		if (M[i][a]!='X' && M[i][a]!='*'){
			
			e++;
		}
			
			if (M[i][a]=='*'){
				
				as++;
			}
	a++;
	}		
}

void buscarCampoD2 (TipoMatriz M, int & e, int & as){
	
	int a=2;
	
	for (int i=0; i<3; i++){
		
		if (M[i][a]!='X' && M[i][a]!='*'){
			
			e++;
		}
			
			if (M[i][a]=='*'){
				
				as++;
			}
	a--;
	}		
}


//* MAIN */

int main(){
	
	system("color 0A"); 
    
    TipoMatriz Matriz;
    char letra='S';
    char jug;
    int game;
    int aux, aux2, aux3, pa, cont;
    int f1,f2,f3,c1,c2,c3,d1,d2; /* Para contabilizar campos disponibles */
    int astF1, astF2, astF3, astC1, astC2, astC3, astD1, astD2; /*  Para contabilizar los asteriscos en cada línea */
    
    srand(time(NULL));

    
do {
    
    game=0;
    cont=0;
	system("cls");
	IniciarMatriz(Matriz);
    
    
    /* Turno del Jugador 1 */
    
    do{
    
    printf("\n\n\n                              JUEGO DEL TRES EN RAYA\n\n"
			"                        Tu simbolo: X      Simbolo rival: *\n\n");
    LeerMatriz(Matriz);
    printf("\n\n                     Jugador 1, introduce una letra disponible: ");
    
		scanf(" %c", &letra);
		letra = toupper(letra);
	
	jug='X';
    
    printf("\n");
    
    ModificarCampo(Matriz, letra, jug);
    
    system("cls");
    
    
    /* Condiciones de victoria en el juego */
    
    if (Matriz[0][0]=='X' && Matriz[0][1]=='X' && Matriz[0][2]=='X' ||
        Matriz[1][0]=='X' && Matriz[1][1]=='X' && Matriz[1][2]=='X' || 
        Matriz[2][0]=='X' && Matriz[2][1]=='X' && Matriz[2][2]=='X' ||
        Matriz[0][0]=='X' && Matriz[1][0]=='X' && Matriz[2][0]=='X' ||
        Matriz[0][1]=='X' && Matriz[1][1]=='X' && Matriz[2][1]=='X' ||
        Matriz[0][2]=='X' && Matriz[1][2]=='X' && Matriz[2][2]=='X' ||
        Matriz[0][0]=='X' && Matriz[1][1]=='X' && Matriz[2][2]=='X' ||
        Matriz[2][0]=='X' && Matriz[1][1]=='X' && Matriz[0][2]=='X'){
                          
                         game=1;
                         continue;
        }

     /* Condición de terminación del juego sin victoria */ 
      
	if ( (Matriz[0][0]=='*' ||  Matriz[0][0]=='X') && (Matriz[0][1]=='*' ||  Matriz[0][1]=='X') && 
	     (Matriz[0][2]=='*' ||  Matriz[0][2]=='X') && (Matriz[1][0]=='*' ||  Matriz[1][0]=='X') &&
	     (Matriz[1][1]=='*' ||  Matriz[1][1]=='X') && (Matriz[1][2]=='*' ||  Matriz[1][2]=='X') && 
	     (Matriz[2][0]=='*' ||  Matriz[2][0]=='X') && (Matriz[2][1]=='*' ||  Matriz[2][1]=='X') &&
		 (Matriz[2][2]=='*' ||  Matriz[2][2]=='X') ) {
		 	
		 	game=4;
		 	continue;
		 }
		 
	/* Comprobar la ocupación de filas y columnas con sumatorios para cada una, 
	   de esta forma será posible ocupar las más saturadas */
	   
    f1=0; 
	astF1=0;
	buscarCampoF(Matriz, 0, f1, astF1); /* fila 0 */
	f2=0;
	astF2=0;
	buscarCampoF(Matriz, 1, f2, astF2); /* fila 1 */
	f3=0;
	astF3=0;
	buscarCampoF(Matriz, 2, f3, astF3); /* fila 2 */
	c1=0;
	astC1=0;
	buscarCampoC(Matriz, c1, 0, astC1); /* Columna 0 */
	c2=0;
	astC2=0;
	buscarCampoC(Matriz, c2, 1, astC2); /* Columna 1 */
	c3=0;
	astC3=0;
	buscarCampoC(Matriz, c3, 2, astC3); /* Columna 2 */
	d1=0;
	astD1=0;
	buscarCampoD(Matriz, d1, astD1); /*  Diagonal 1 */
	d2=0;
	astD2=0;
	buscarCampoD2(Matriz, d2, astD2); /* Diagonal 2 */
	                     
    
	/* Turno del Jugador Máquina */
    
    
    	do {
    		
    			/* He añadido un contador para saber si en la línea en cuestión no hay asteriscos */
		
		aux=rand()%3;
		aux2=rand()%3;
		
			if (f1==1 && astF1==2){
				
				aux=0;
				aux2=rand()%3;
				continue;
				
			} else if (f2==1 && astF2==2){
						
				aux=1;
			    aux2=rand()%3;
				continue;
			    	
			} else if (f3==1 && astF3==2){
				
				aux=2;
			    aux2=rand()%3;
			    continue;
			    
			} else if (c1==1 && astC1==2){
				
				aux=rand()%3;
				aux2=0;
				continue;
				
			} else if (c2==1 && astC2==2){
						
				aux=rand()%3;
			    aux2=1;
				continue;	
			    	
			} else if (c3==1 && astC3==2){
				
				aux=rand()%3;
			    aux2=2;
			    continue;
			    
			} else if (d1==1 && astD1==2){
				
				aux=rand()%3;
				aux2=aux;
				continue;	
				
			} else if (d2==1 && astD2==2){
				
				aux=rand()%3;
				
				if (aux==0){
					aux2=2;
				} else if (aux==1){
					aux2=aux;
				} else if (aux==2){
					aux2=0;
				} 
				
				continue;
			}
			
			 /* Opciones si no ha ganado el rival */
			
			if (f1==1 && astF1==0){
				
				aux=0;
				aux2=rand()%3;
				continue;
				
			} else if (f2==1 && astF2==0){
						
				aux=1;
			    aux2=rand()%3;
				continue;
			    	
			} else if (f3==1 && astF3==0){
				
				aux=2;
			    aux2=rand()%3;
			    continue;
			    
			} else if (c1==1 && astC1==0){
				
				aux=rand()%3;
				aux2=0;
				continue;
				
			} else if (c2==1 && astC2==0){
						
				aux=rand()%3;
			    aux2=1;
				continue;	
			    	
			} else if (c3==1 && astC3==0){
				
				aux=rand()%3;
			    aux2=2;
			    continue;
			    
			} else if (d1==1 && astD1==0){
				
				aux=rand()%3;
				aux2=aux;
				continue;
				
			} else if (d1==1 && astD1==0){
				
				aux=rand()%3;
				aux2=aux;
				continue;
				
			} else if (d2==1 && astD2==0){
				
				aux=rand()%3;
				
				if (aux==0){
					aux2=2;
				} else if (aux==1){
					aux2=aux;
				} else if (aux==2){
					aux2=0;
				} 
				
				continue;
				
			}
		
			/* Opciones tras la primera jugada */
			
			/* El jugador usuario NO empieza desde el centro */
			
				if (cont==0 && Matriz[1][1]=='E'){
				
				aux=1;
				aux2=1;
				continue;
				}
			
			/* El jugador usuario empieza desde el centro */
			
			pa=0;
			
			if (f1==2 && astF1==1 || f2==2 && astF2==1 || f3==2 && astF3==1 || c1==2 && astC1==1 || c2==2 && astC2==1 || c3==2 && astC3==1 || d1==2 && astD1==1 || d2==2 && astD2==1){
			
			while (pa==0){
			
				aux3=rand()%8;
			
				if (f1==2 && astF1==1 && aux3==0){
				
					aux=0;
					aux2=rand()%3;
					pa=1;
					continue;
				
				} else if (f2==2 && astF2==1 && aux3==1){
						
					aux=1;
				    aux2=rand()%3;
				    pa=1;
					continue;
			    	
				} else if (f3==2 && astF3==1 && aux3==2){
				
					aux=2;
			    	aux2=rand()%3;
			    	pa=1;
				    continue;
			    
				} else if (c1==2 && astC1==1 && aux3==3){
				
					aux=rand()%3;
					aux2=0;
					pa=1;
					continue;
				
				} else if (c2==2 && astC2==1 && aux3==4){
						
					aux=rand()%3;
				    aux2=1;
				    pa=1;
					continue;	
			    	
				} else if (c3==2 && astC3==1 && aux3==5){
				
					aux=rand()%3;
				    aux2=2;
				    pa=1;
				    continue;
			    
				} else if (d1==2 && astD1==1 && aux3==6){
				
					aux=rand()%3;
					aux2=aux;
					pa=1;
					continue;
				
				} else if (d2==2 && astD2==1 && aux3==7){
				
					aux=rand()%3;
				
				if (aux==0){
						aux2=2;
					} else if (aux==1){
						aux2=aux;
					} else if (aux==2){
						aux2=0;
					} 
					pa=1;
					continue;
				}
			
			}
			}
					
		
		} while ( Matriz[aux][aux2]=='*' || Matriz[aux][aux2]=='X');
    
	Matriz[aux][aux2]='*';
	cont++;
    
    /* Aquí termina el turno del jugador 2 */
    
    
    /* Condiciones de victoria en el juego */
    
    if (Matriz[0][0]=='*' && Matriz[0][1]=='*' && Matriz[0][2]=='*' ||
        Matriz[1][0]=='*' && Matriz[1][1]=='*' && Matriz[1][2]=='*' || 
        Matriz[2][0]=='*' && Matriz[2][1]=='*' && Matriz[2][2]=='*' ||
        Matriz[0][0]=='*' && Matriz[1][0]=='*' && Matriz[2][0]=='*' ||
        Matriz[0][1]=='*' && Matriz[1][1]=='*' && Matriz[2][1]=='*' ||
        Matriz[0][2]=='*' && Matriz[1][2]=='*' && Matriz[2][2]=='*' ||
        Matriz[0][0]=='*' && Matriz[1][1]=='*' && Matriz[2][2]=='*' ||
        Matriz[2][0]=='*' && Matriz[1][1]=='*' && Matriz[0][2]=='*'){
                          
                         game=2;
                         continue;
        }
        
    /* Condición de terminación del juego sin victoria */ 
      
	if ( (Matriz[0][0]=='*' ||  Matriz[0][0]=='X') && (Matriz[0][1]=='*' ||  Matriz[0][1]=='X') && 
	     (Matriz[0][2]=='*' ||  Matriz[0][2]=='X') && (Matriz[1][0]=='*' ||  Matriz[1][0]=='X') &&
	     (Matriz[1][1]=='*' ||  Matriz[1][1]=='X') && (Matriz[1][2]=='*' ||  Matriz[1][2]=='X') && 
	     (Matriz[2][0]=='*' ||  Matriz[2][0]=='X') && (Matriz[2][1]=='*' ||  Matriz[2][1]=='X') &&
		 (Matriz[2][2]=='*' ||  Matriz[2][2]=='X') ) {
		 	
		 	game=4;
		 	continue;
		 }
    
    } while (game == 0);
    
   
	/* Juego Terminado */

	
	if(game==4){
		
		printf("\n\n\n                                 No ha ganado nadie");
		
	} else if (game==1) {
		   
		printf("\n\n\n                                   Has ganado!"); 
	} else {
	
		printf("\n\n\n                               Ha ganado la maquina!");
		
	} 
    
    printf("\n\n\n\n");
    
    LeerMatriz(Matriz);
    printf("\n\n\n\n                            ");
    

	printf("\n\n               Quieres jugar otra partida? (S/N): ");
    
		scanf(" %c", &letra);
		letra = toupper(letra);


} while (letra!='N');

}
