#include "labE.h"

void rotate(void);

int main (void)
{
  /*Channel mapping*/
	  unsigned int right;//feed from right diode
    unsigned int left ; //feed from left diode
    int difference;  
    initPIC32 ();
      



    while(TRUE){

      if(START==1){
        
        spinL();
        delay_ms(50);
        stopSpinL();
        while(STOP==0){

          right = 1023 - analog(Analog6);
          delay_ms(1);
          left  = 1023 - analog(Analog7);
          delay_ms(1);

          difference = calcDif(right,left);

          if (left > right && difference > 75){
            printStr("\nTURNING RIGTH");    
            glowLeds(right,left);
            setSpeed(50,0);               
          }
          else if (left < right && difference > 75){                                  
            printStr("\nTURNING LEFT");
            glowLeds(right,left);
            setSpeed(0,50);                           
          }
          else if (difference < 75){
            printStr("\nMoving Forward");          
            setSpeed(50,52);                               
          }          
        }
      }
      setSpeed(0,0);		
    }  
  return (0);
}


