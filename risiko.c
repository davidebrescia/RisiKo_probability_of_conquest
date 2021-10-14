//MODALITA' FORTINO (l'attacco può usare solo 2 carri alla volta)

#define N_SIMULAZIONI 200000

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

float samyCalc(int attacco, int difesa, float sogliaStop, int nSim); //Stima probabilità che l'attacco elimini la difesa entro la soglia prefissata
int simBattaglia(int attacco, int difesa, float sogliaStop); //restituisce 1 se attacco ha successo, 0 altrimenti
int dado(void);
int singoloScontro(int attaccanti, int difensori); //simula il singolo scontro di dadi, restituisce il numero di carri persi dalla difesa

int main(){
	int difesa, attacco, nSim;
	float sogliaStop, ris;

	system("title Risiko - Probabilita` di conquista");

	srand(time(NULL));
	
	while(1){
		printf("\n Attacco: ");  //si intende il numero di carri nel territorio attaccante, quindi in realtà gli attaccanti sono = attacco-1
		scanf("%d", &attacco);
		printf(" Difesa:  ");
		scanf("%d", &difesa);
		printf(" Soglia:  "); //Quando Att/Dif in un momento < sogliaStop, l'attacco si blocca (quindi non ha successo), 0 se si vuole attaccare a sfinimento
		scanf("%f", &sogliaStop);
		
		nSim=N_SIMULAZIONI;
		ris=samyCalc(attacco, difesa, sogliaStop, nSim);
		
		printf("\n Prob. di conquista: %.3f %%\n\n-----------------------------\n", ris*100);
	}
	
	return 0;
}

float samyCalc(int attacco, int difesa, float sogliaStop, int nSim){
	float prob;
	int nSuccessi=0;
	int i;
	for(i=nSim;i>0;i--){
		nSuccessi=nSuccessi+simBattaglia(attacco, difesa, sogliaStop);
	}
	
	prob=((float)(nSuccessi))/((float)(nSim));
	return prob;
}

int simBattaglia(int attacco, int difesa, float sogliaStop){ //1: attacco andato a buon fine (difesa eliminata)
	float sogliaEffettiva=9999999;
	int a,d, perseDifesa;
	
	if(sogliaStop==0){
		do{
			if(attacco>2){
				a=2;
			}else{
				a=attacco-1;
			}
			if(difesa>3){
				d=3;
			}else{
				d=difesa;
			}
			perseDifesa=singoloScontro(a,d);
			attacco=attacco-(a-perseDifesa);
			difesa=difesa-perseDifesa;
		}while(attacco>1 && difesa>0);
	}else{
		do{
			if(attacco>2){
				a=2;
			}else{
				a=attacco-1;
			}
			if(difesa>3){
				d=3;
			}else{
				d=difesa;
			}
			perseDifesa=singoloScontro(a,d);
			attacco=attacco-(a-perseDifesa);
			difesa=difesa-perseDifesa;
			
			sogliaEffettiva=((float)(attacco))/((float)(difesa));		
		}while(sogliaEffettiva>=sogliaStop && attacco>1 && difesa>0);
	}
	
	if(sogliaEffettiva<sogliaStop || attacco<=1){ //condizioni di attacco di non successo
		return 0;
	} else {
		return 1;
	}
	
}

int dado(void){
	int random;
	
	do{
		random=rand();
	}while(random==32767);
	
	return (random%6+1);
}

int singoloScontro(int attaccanti, int difensori){
	int risAttacco[3];
	int risDifesa[3];
	int i, j, temp, persiDifesa=0;
	
	for(i=0;i<attaccanti;i++){
		risAttacco[i]=dado();
	}
	for(i=0;i<difensori;i++){
		risDifesa[i]=dado();
	}
	
	for(j=0; j<attaccanti; j++){
		for(i=0; i<attaccanti-j-1; i++){  //riordina array Att
			if(risAttacco[i+1]>risAttacco[i]){
				temp=risAttacco[i];
				risAttacco[i]=risAttacco[i+1];
				risAttacco[i+1]=temp;
			}
		}
	}
	for(j=0; j<difensori; j++){
		for(i=0; i<difensori-j-1; i++){  //riordina array Dif
			if(risDifesa[i+1]>risDifesa[i]){
				temp=risDifesa[i];
				risDifesa[i]=risDifesa[i+1];
				risDifesa[i+1]=temp;
			}
		}
	}
	
	if(attaccanti>difensori){
		i=difensori;
	}else{
		i=attaccanti;
	}
	
	for(j=0; j<i; j++){
		if(risAttacco[j]>risDifesa[j]){
			persiDifesa++;
		}
	}

	return persiDifesa;
}
