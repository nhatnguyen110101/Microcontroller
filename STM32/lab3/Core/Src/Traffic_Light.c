#include <main.h>

int  Time_in_state_NGANG = 1;
int  Time_in_state_DOC = 1;

typedef enum {RED, GREEN, AMBER } eLightState;
eLightState Light_state_G_DOC = RED;
eLightState Light_state_G_NGANG = GREEN;



extern int RED_DURATION;
extern int GREEN_DURATION;
extern int AMBER_DURATION;

extern int initial_green;
extern int initial_red ;

void Traffic_Light_Update_DOC( ){
	 if (initial_red == 1 ) {
		 Time_in_state_DOC = RED_DURATION;
		 Light_state_G_DOC = RED;
	 }
	 switch (Light_state_G_DOC){
	 	 case RED:
	 		 initial_red++;
	 		 display7SEG_DOC(Time_in_state_DOC);
	 		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
		 	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
		 	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1);
	 		 if (--Time_in_state_DOC == 0){
	 			Light_state_G_DOC = GREEN;
	 			Time_in_state_DOC = GREEN_DURATION;
	 		 }

	 		 break;
	 	case GREEN:
	 		display7SEG_DOC(Time_in_state_DOC);
	 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
	 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
	 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0);
	 		if (--Time_in_state_DOC == 0){
	 			Light_state_G_DOC = AMBER;
	 			Time_in_state_DOC = AMBER_DURATION  ;
	 		}

	 		break;
	 	case AMBER:
	 		 display7SEG_DOC(Time_in_state_DOC);
	 		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
	 		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
	 		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1);
	 		if (--Time_in_state_DOC == 0 ){
	 			Light_state_G_DOC = RED;
	 			Time_in_state_DOC = RED_DURATION  ;
	 		}

	 		break;
	 }
}



void Traffic_Light_Update_NGANG( ){
	 if (initial_green == 1 ) {
		 Time_in_state_NGANG = GREEN_DURATION;
		 Light_state_G_NGANG = GREEN;
	 }
	 switch (Light_state_G_NGANG){
	 	 case RED:
	 		 initial_red++;
	 		 display7SEG_NGANG(Time_in_state_NGANG);
	 		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0); // RED
		 	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1);
		 	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); // GREEN
	 		 if (--Time_in_state_NGANG == 0){
	 			 Light_state_G_NGANG = GREEN;
	 			Time_in_state_NGANG = GREEN_DURATION;
	 		 }

	 		 break;
	 	case GREEN:
	 		initial_green++;
	 		display7SEG_NGANG(Time_in_state_NGANG);
	 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
	 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1);
	 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
	 		if (--Time_in_state_NGANG == 0){
	 			Light_state_G_NGANG = AMBER;
	 			Time_in_state_NGANG = AMBER_DURATION  ;
	 		}

	 		break;
	 	case AMBER:
	 		display7SEG_NGANG(Time_in_state_NGANG);
	 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
	 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0);
	 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
	 		if (--Time_in_state_NGANG == 0 ){
	 			Light_state_G_NGANG = RED;
	 			Time_in_state_NGANG = RED_DURATION  ;
	 		}
	 		break;
	 }
}
