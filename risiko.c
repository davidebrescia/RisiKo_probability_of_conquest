/*

	Risiko. Prima di sferrare un attacco e cominciare una battaglia, sarebbe utile sapere 
	quante speranze avresti di conquistare il territorio nemico. Beh, usa sta roba. 
	  
	Un po' di nomi:
	
	'Battaglia' = Intera battaglia. Per esempio: 28 carri contro 19 carri. Ha esito '1' se
				  l'attacco ha la meglio. '0' se la difesa ha la meglio.
				   
	'Scontro'   = Singolo scontro con i dadi durante la battaglia. Tipo: 3 carri contro
				  3 carri. Oppure 3 carri contro 2 carri (capita alla fine della battaglia).
				  Lo dico subito: all'attacco e alla difesa conviene sempre impiegare il
				  massimo numero di carri che ha a disposizione. Non conviene mai difendere
				  con 2 dadi quando ne potresti usare 3. Queste simulazioni vengono fatte
				  supponendo che i duellanti seguano questo principio.
	
	PS: Questo simulatore rispetta a pieno le regole ufficiali. Per esempio: quando l'attacco
	rimane con 1 carro, non puo` piu` attaccare, perche` tale carro deve restare sul territorio.

	Created by Davide Brescia
	
*/


// Numero di simulazioni della battaglia. '200000' garantisce velocita` quasi istantanea di
// calcolo, e bassa incertezza statistica (circa 0.1%) sulla probabilita` finale calcolata.  
#define N_SIMULAZIONI 200000


#include <stdio.h>
#include <time.h>
#include <stdlib.h>


// Stima la probabilità di successo, simulando l'intera battaglia un grande numero di volte (N_SIMULAZIONI) 
float samyCalc(int attacco, int difesa, float sogliaStop, int nSim); 

// Simula un'intera battaglia. Restituisce 1 se l'attacco ha successo, 0 se la difesa ha successo
int simBattaglia(int attacco, int difesa, float sogliaStop); 

// Tira un dado
int dado(void);

// Simula un singolo scontro di dadi. Restituisce il numero di carri persi dalla difesa
int singoloScontro(int attaccanti, int difensori); 


int main(){
	int difesa, attacco;
	float sogliaStop, ris;

	system("title Risiko - Probabilita` di conquista");

	srand(time(NULL));
	
	while(1){
		// Si intende il numero di carri nel territorio attaccante
		printf("\n Attacco: ");  
		scanf("%d", &attacco);
		
		// Si intende il numero di carri nel territorio difendente
		printf(" Difesa:  ");
		scanf("%d", &difesa);
		
		// Quando Att/Dif < sogliaStop, l'attacco smette di attaccare (quindi non ha successo); 
		// metti 0 se vuoi attaccare a sfinimento (nel senso attacchi finche` non rimani con
		// 1 carro). L'attaccante di solito non attacca a sfinimento, ma si ferma se vede che
		// le proprie armate diventano uguali (in numero) a quelle della difesa, ovvero 
		// sogliaStop = 1.0.
		printf(" Soglia:  ");    
		scanf("%f", &sogliaStop);
		
		ris = samyCalc(attacco, difesa, sogliaStop, N_SIMULAZIONI);
		
		printf("\n Prob. di conquista: %.3f %%\n\n-----------------------------\n", ris*100);
	}
	
	return 0;
}


float samyCalc(int attacco, int difesa, float sogliaStop, int nSim){
	
	float prob;
	int nSuccessi = 0;
	int i;
	
	for(i = nSim; i>0; i--){
		nSuccessi = nSuccessi + simBattaglia(attacco, difesa, sogliaStop);
	}
	
	prob = ((float)(nSuccessi)) / ((float)(nSim));
	return prob;
}


int simBattaglia(int attacco, int difesa, float sogliaStop){ //1: attacco andato a buon fine (difesa eliminata)

	float sogliaEffettiva = 9999999.0;
	int a, d, perseDifesa;
	
	do{
		if(attacco > 3){
			a = 3;
		}else{
			a = attacco - 1;
		}
		if(difesa > 3){
			d = 3;
		}else{
			d = difesa;
		}
		perseDifesa = singoloScontro(a, d);
		attacco = attacco - (a - perseDifesa);
		difesa = difesa - perseDifesa;
		
		if(sogliaStop != 0){
			sogliaEffettiva = ((float)(attacco)) / ((float)(difesa));
		}
		
	}while(sogliaEffettiva >= sogliaStop && attacco > 1 && difesa > 0);

	
	if(sogliaEffettiva < sogliaStop || attacco <= 1){ //condizioni di attacco di non successo
		return 0;
	} else {
		return 1;
	}
}


int dado(void){
	int random;
	
	do{
		random = rand();
	}while(random == 32767);
	
	return (random % 6 + 1);
}


int singoloScontro(int attaccanti, int difensori){
	int risAttacco[3];
	int risDifesa[3];
	int i, j, temp, persiDifesa = 0;
	
	for(i = 0; i < attaccanti; i++){
		risAttacco[i] = dado();
	}
	for(i = 0; i < difensori; i++){
		risDifesa[i] = dado();
	}
	
	for(j = 0; j < attaccanti; j++){
		for(i = 0; i < attaccanti-j-1; i++){  //riordina array Att
			if(risAttacco[i+1] > risAttacco[i]){
				temp = risAttacco[i];
				risAttacco[i] = risAttacco[i+1];
				risAttacco[i+1] = temp;
			}
		}
	}
	for(j = 0; j < difensori; j++){
		for(i = 0; i < difensori-j-1; i++){  //riordina array Dif
			if(risDifesa[i+1] > risDifesa[i]){
				temp = risDifesa[i];
				risDifesa[i] = risDifesa[i+1];
				risDifesa[i+1] = temp;
			}
		}
	}
	
	if(attaccanti > difensori){
		i = difensori;
	}else{
		i = attaccanti;
	}
	
	for(j = 0; j < i; j++){
		if(risAttacco[j] > risDifesa[j]){
			persiDifesa++;
		}
	}

	return persiDifesa;
}
