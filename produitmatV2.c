/*   RAHMANI TAHA ABDELAZIZ */





#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

#define ROW 8 // number of rows of the first matrix
#define COL 10 // number of coloumns of the first matrix and the rows of the second matrix
#define COL2 20 // number of colomns of the second matrix
#define NUM_COL 3 // number  of blocks in colomns  the matrix result
#define NUM_ROW 8 // number of blocks in rows of the matrix result

int mat1 [ROW][COL]; // the first matrix
int  mat2 [COL][COL2] ; // the second matrix
int mat [ROW][COL2]; // the matrix resut : mat = mat1 * mat2



void *  multiplication(void *th){
	long k = (long) th ;
	int remainder = k % NUM_COL;
	int quotient = k / NUM_COL;
	
	int debut,fin;debut=fin=0;
	int debut2, fin2; debut2 = fin2 = 0;
  	debut=remainder*(COL2/NUM_COL);
	debut2 = quotient* (ROW/NUM_ROW);

   	
   	if(remainder== NUM_COL-1){
     		fin= COL2-1;
     	
     	}	
	else{ 
		fin=debut+(COL2/NUM_COL)-1;
		
         }

         if(quotient == NUM_ROW-1){
       
                fin2 =  ROW - 1;
         }
         else{
                
                fin2 = debut2 + (ROW/NUM_ROW)-1;

          }

   int sum;
   for(int i = debut2; i <= fin2; i++){ 

	
	for(int j = debut; j <= fin; j++){

		sum = 0;

		for (int k= 0; k < COL; k++)
			sum += mat1 [i][k] * mat2 [k][j];

		mat [i][j] = sum;

	}
	
   }

	

	pthread_exit(0);


	
}


int main(){
	pthread_t threads[NUM_COL * NUM_ROW]; 
   	int rc; 
      	long th; 
      	double debut,fin;
      	srand(time(NULL));
	

	
	

	printf("------------matrice 1 -----------\n");	
 	for(int i = 0 ; i < ROW ; i++){
		for (int j = 0 ; j < COL ; j++){
			mat1 [i][j] = rand()%10;
			printf("%d ",mat1 [i][j]);
		}
		printf(" \n");
	}

   	printf("------------matrice 2 -----------\n");
	for(int i = 0 ; i < COL ; i++){
	        for (int j = 0 ; j < COL2 ; j++){
                        mat2 [i][j] = rand()%10;
                        printf("%d ",mat2 [i][j]);

                }
                printf(" \n");
	}

	printf("--------------------le calcul du produit matricielle parallele--------------------------\n");
	debut = clock();

	for(th = 0; th < NUM_COL * NUM_ROW ; th++){ 
		
	      rc = pthread_create(&threads[th], NULL, multiplication, (void *)th); 	
	      (void)pthread_join(threads[th],NULL);
	      if (rc){ 
                    	printf("Erreur de creation de thread; code erreur = %d\n", rc); 
	            	exit(-1); 
              } 
	 }
	 
	 
	 for(th = 0; th < NUM_COL * NUM_ROW ; th++){ 
	      (void)pthread_join(threads[th],NULL);
         }

         fin =  clock();
         
 
	printf("------------matrice resultat -----------\n");

	for(int i = 0 ; i < ROW ; i++){
		 for (int j = 0 ; j < COL2 ; j++) 
	                printf("%d ",mat [i][j]);
	         printf(" \n");                  
	}

	printf("temps parallele=%f\n", (double)(fin-debut)/CLOCKS_PER_SEC);
		

	printf("--------------------le calcul du produit matricielle sequentielle-----------------------\n");
	debut =  clock();
	for(int i=0; i<ROW; i++){
		int sum=0;
		for(int j=0; j<COL2; j++){
	            	sum = 0;
			for(int k=0; k<COL; k++)
	                  	 sum = sum + mat1[i][k] * mat2[k][j];
	                 mat[i][j] = sum;
	        }
	 }
	fin =  clock();
	printf("------------matrice resultat -----------\n");

	        for(int i = 0 ; i < ROW ; i++){
	        	for (int j = 0 ; j < COL2 ; j++) 
	                	printf("%d ",mat [i][j]);
	        	printf(" \n");
	         }
	 printf("temps sequentielle=%f\n", (double)(fin-debut)/CLOCKS_PER_SEC);


	return 0;

} 
