#include "gassp72.h"
#include <stdio.h>

//extern int dft(unsigned short *,int);


extern int sommecarre(int);
extern int m2(int,short*);
extern short TabSig2[];
short int dma_buf[64];
int M2k[64];

int M2TIR=3936256/4;

int SYSTICK_PER=360000; 

int k[6] = {17, 18, 19, 20, 23, 24};
int compteur_occurences[6]= {0,0,0,0,0,0};
int M2[6];

int fanion = 0;


void sys_callback(void)
{

	// D�marrage DMA pour 64 points
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	int score[6];
	for (int i=0; i<6; i++)
	{
		M2[i]=m2(k[i], dma_buf); // calcul DFT M2(k) //anciennemtn dft � la place de m2
		if (M2[i]>=M2TIR){ // si le seuil est d�pass�
			compteur_occurences[i] ++;
			GPIO_Set(GPIOB, 14);
		}
		else{
			compteur_occurences[i]=0;
			GPIO_Clear(GPIOB,14);
		}
		if (compteur_occurences[i] >= 15) {
			score[i]++;
			compteur_occurences[i] =0;
		}
	}
	
}



int main(void)
{
	

	for(int k=0;k<64;k++)
	{
		M2k[k]=m2(k,TabSig2);
	}

	


	
		// activation de la PLL qui multiplie la fr�quence du quartz par 9
	CLOCK_Configure();
	// PA2 (ADC voie 2) = entr�e analog
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
	// PB1 = sortie pour profilage � l'oscillo
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// PB14 = sortie pour LED
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);

	// activation ADC, sampling time 1us
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	// D�clenchement ADC par timer2, periode (72MHz/320kHz)ticks
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	// Config DMA pour utilisation du buffer dma_buf (a cr��r)
	Init_ADC1_DMA1( 0, dma_buf );

	// Config Timer, p�riode exprim�e en p�riodes horloge CPU (72 MHz)
	Systick_Period_ff( SYSTICK_PER );
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 3 est la priorit�, sys_callback est l'adresse de cette fonction, a cr��r en C
	Systick_Prio_IT( 3, sys_callback );
	SysTick_On;
	SysTick_Enable_IT;	
	
	
	
	
	
	
	
	
	
while	(1)
	{

	}
	
}
