#include "labE.h"

void glowLeds(unsigned int right,unsigned int left);
unsigned int calcDif(unsigned int right,unsigned int left);
int calibrateSensors(analog_chan_t channel,int samples);
void blinkLeds(int mode);
void turnLeds(int mode);

int main (void)
{
  /*Channel mapping*/
  int right,rightRef;//data from right diode
  int left,leftRef ; //data from left diode
  int threshold;  //limit
  initPIC32 ();

  while(TRUE){
  	if(START==1)
  	{
        	//obtain the reference value       
        	leftRef = 1023- calibrateSensors(Analog7,100);
        	rightRef = 1023 - calibrateSensors(Analog6,100);
        	blinkLeds(1); //LED Animation, when over the robot is ready to follow the light

		while(STOP==0)
		{
          		right = 1023 - analog(Analog6);
          		delay_ms(1);
          		left  = 1023 - analog(Analog7);
          		delay_ms(1);

          		threshold = calcDif(right,left);

          		//robot turns right
          		if (left > right && threshold > 45)
          		{
            			glowLeds(right,left);
            			setSpeed(90,20);               
          		}//robot turns left
          		else if (left < right && threshold > 45)
          		{                                 
        	 		glowLeds(right,left);
            			setSpeed(20,90);                           
          		}//robot doesnt move
          		else if(right>(rightRef-50) && left>(leftRef-50))
          		{
            			glowLeds(right,left);
              			setSpeed(0,0);
          		}//robot move forward
          		else{         
            			setSpeed(60,65);                               
          		}         
        	}
        	turnLeds(0);
      	}
      	setSpeed(0,0);		
  }  
  return (0);
}

void glowLeds(unsigned int right,unsigned int left){
	led(1,0);
	led(2,0);
    	led(3,0);
    	led(4,0);
    
  	if(right>left)
  	{
    		led(1,1);
    		led(2,1);
    		led(3,0);
    		led(4,0);
  	}
  	if(right<left)
  	{
    		led(1,0);
    		led(2,0);
    		led(3,1);
    		led(4,1);
  	}
  	else
  	{
    		led(1,0);
    		led(2,1);
    		led(3,1);
    		led(4,0);
  	} 
}

//returns the absolute value
unsigned int calcDif(unsigned int right,unsigned int left){
	if(right>left)  
    		return right - left;
  	else
    		return left - right;
}



//return average of measures, given the number os sampes wanted
int calibrateSensors(analog_chan_t channel,int samples){
	int count=0;
	int measure=0;
  	while(count<samples)
  	{
  		measure+=analog(channel);
    		count++;    
  	} 
  	return measure/count;
}

void blinkLeds(int mode){
	int count;
  	led(1,0);
  	led(2,0);
  	led(3,0);
  	led(4,0);
  	switch(mode)
  	{
    		case 0 :
      			for(count = 0; count < 5; count++)
      			{
			        led(1,1);
			        led(2,1);
			        led(3,1);
			        led(4,1);
			        delay_ms(500);
			        led(1,0);
			        led(2,0);
			        led(3,0);
			        led(4,0);
			        delay_ms(500);
			}
			break;
    		case 1 :
			for(count = 0; count < 2; count++)
			{
				led(1,1);
			        led(2,0);
			        led(3,0);
			        led(4,0);
			        delay_ms(500);
			        led(1,0);
			        led(2,1);
			        led(3,0);
			        led(4,0);
			        delay_ms(500);
			        led(1,0);
			        led(2,0);
			        led(3,1);
			        led(4,0);
			        delay_ms(500);
			        led(1,0);
			        led(2,0);
			        led(3,0);
			        led(4,1);
			        delay_ms(500);
			}
			break;
		default:
		      led(1,1);
		      led(2,1);
		      led(3,1);
		      led(4,1);
		      delay_ms(500);
		      led(1,0);
		      led(2,0);
		      led(3,0);
		      led(4,0);
		      delay_ms(500);
		      break; 
  	}  
}

void turnLeds(int mode){
	int p;
	for(p=1;p<=4;p++)
	{
    		led(p,mode);
  	}
}

