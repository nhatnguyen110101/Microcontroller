#include "main.h"
#include "input_reading.h"

#define DURATION_TIMER_INTERRUPT 10
#define DURATION_FOR_BLINKING_LED (250/DURATION_TIMER_INTERRUPT)
#define DURATION_FOR_DISPLAYING_LED (1000/DURATION_TIMER_INTERRUPT)

enum ModeState{MODE_1, MODE_2, MODE_3 , MODE_4 } ;
enum ModeState mode_present = MODE_1;
int initial_mode1 = 1;
int initial_mode2 = 1;
int initial_mode3 = 1;
int initial_mode4 = 1;

int flag_button1 = 1;


int RED_DURATION = 1;
int GREEN_DURATION = 2;
int AMBER_DURATION = 3;


extern int timer0_counter;
extern int timer0_flag;
extern int timer1_counter;
extern int timer1_flag;

int buffer_RED_DURATION ;
int buffer_GREEN_DURATION;
int buffer_AMBER_DURATION;

enum Button_State {BUTTON_PRESSED, BUTTON_RELEASE};
enum Button_State but1_state = BUTTON_RELEASE;


enum Button_State but2_state = BUTTON_RELEASE;


enum Button_State but3_state = BUTTON_RELEASE;

int initial_green = 1;
int initial_red = 1;


void fsm_for_input_processing(void){
	switch (but1_state){
	case BUTTON_RELEASE:
		if (is_button_pressed(0)) {
			flag_button1++;
			if (flag_button1 == 5) flag_button1 = 1;
			but1_state = BUTTON_PRESSED;
		}
		Selector();
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(0)) {
			but1_state = BUTTON_RELEASE;
		}
		break;
	}

}
void Selector(){
	if (RED_DURATION == GREEN_DURATION + AMBER_DURATION ) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
	else HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
	switch (flag_button1){
	case 1:
		initial_mode4 = 1;
		if (initial_mode1 == 1) {
				initial_mode1++;
				Traffic_Light_Update_NGANG();
				Traffic_Light_Update_DOC();
				setTimer0(DURATION_FOR_DISPLAYING_LED);
		}
		if (timer0_flag == 1) {
			Traffic_Light_Update_NGANG();
			Traffic_Light_Update_DOC();
				setTimer0(DURATION_FOR_DISPLAYING_LED);
		}
		break;
	case 2:
		initial_green = 1;
		initial_red = 1;
		initial_mode1 = 1;
		if (initial_mode2 == 1 ) {
			buffer_RED_DURATION = RED_DURATION;
			setTimer1(DURATION_FOR_BLINKING_LED);
			initial_mode2++;
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0); // RED
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); // GREEN

			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);// RED
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1); // GREEN
		}

		display7SEG_NGANG(2);
		display7SEG_DOC(buffer_RED_DURATION);
		if (timer1_flag == 1 ){
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
			setTimer1(DURATION_FOR_BLINKING_LED);
		}
		switch (but2_state){
		case BUTTON_RELEASE:
			if (is_button_pressed(1)) {
				buffer_RED_DURATION++;
				but2_state = BUTTON_PRESSED;
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(1)) {
				but2_state = BUTTON_RELEASE;
			}
			break;
		}
		switch (but3_state){
		case BUTTON_RELEASE:
			if (is_button_pressed(2)) {
				RED_DURATION = buffer_RED_DURATION;
				but3_state = BUTTON_PRESSED;
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(2)) {
				but3_state = BUTTON_RELEASE;
			}
			break;
		}
		break;

	case 3:
		initial_mode2 = 1;
		if (initial_mode3 == 1 ) {
			buffer_AMBER_DURATION = AMBER_DURATION;
			setTimer1(DURATION_FOR_BLINKING_LED);
			initial_mode3++;
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1); // RED
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); // GREEN

			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);// RED
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1); // GREEN
		}
			display7SEG_NGANG(3);
			display7SEG_DOC(buffer_AMBER_DURATION);
		if (timer1_flag == 1 ){
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
			setTimer1(DURATION_FOR_BLINKING_LED);
		}

		switch (but2_state){
		case BUTTON_RELEASE:
			if (is_button_pressed(1)) {
				buffer_AMBER_DURATION++;
				but2_state = BUTTON_PRESSED;
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(1)) {
				but2_state = BUTTON_RELEASE;
			}
			break;
		}
		switch (but3_state){
		case BUTTON_RELEASE:
			if (is_button_pressed(2)) {
				AMBER_DURATION = buffer_AMBER_DURATION;
				but3_state = BUTTON_PRESSED;
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(2)) {
				but3_state = BUTTON_RELEASE;
			}
			break;
		}
		break;
	case 4:
				initial_mode3 = 1;
				if (initial_mode4 == 1 ) {
					buffer_GREEN_DURATION = GREEN_DURATION;
					setTimer1(DURATION_FOR_BLINKING_LED);
					initial_mode4++;
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1); // RED
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0); // GREEN

					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);// RED
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0); // GREEN
				}
				display7SEG_NGANG(4);
				display7SEG_DOC(buffer_GREEN_DURATION);
				if (timer1_flag == 1 ){
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
					setTimer1(DURATION_FOR_BLINKING_LED);
				}

				switch (but2_state){
				case BUTTON_RELEASE:
					if (is_button_pressed(1)) {
						buffer_GREEN_DURATION++;
						but2_state = BUTTON_PRESSED;
					}
					break;
				case BUTTON_PRESSED:
					if (!is_button_pressed(1)) {
						but2_state = BUTTON_RELEASE;
					}
					break;
				}
				switch (but3_state){
				case BUTTON_RELEASE:
					if (is_button_pressed(2)) {
						GREEN_DURATION = buffer_GREEN_DURATION;
						but3_state = BUTTON_PRESSED;
					}
					break;
				case BUTTON_PRESSED:
					if (!is_button_pressed(2)) {
						but3_state = BUTTON_RELEASE;
					}
					break;
				}

				break;
	}

}


int NUM[10][4] = {
		{0, 0, 0, 0}, // 0
		{0, 0, 0, 1}, // 1
		{0, 0, 1, 0}, // 2
		{0, 0, 1, 1}, // 3
		{0, 1, 0, 0}, // 4
		{0, 1, 0, 1}, // 5
		{0,	1, 1, 0}, // 6
		{0, 1, 1, 1}, // 7
		{1, 0, 0, 0}, // 8
		{1, 0, 0, 1}  // 9
};

void display7SEG_NGANG( int num ) {
	 	 int hang_chuc = num/10;
	 	 int hang_donvi = num%10;
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,NUM[hang_chuc][0]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,NUM[hang_chuc][1]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,NUM[hang_chuc][2]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,NUM[hang_chuc][3]);
	  	 //
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,NUM[hang_donvi][0]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,NUM[hang_donvi][1]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,NUM[hang_donvi][2]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,NUM[hang_donvi][3]);

}
void display7SEG_DOC( int num ) {
		 int hang_chuc = num/10;
		 int hang_donvi = num%10;
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,NUM[hang_chuc][0]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,NUM[hang_chuc][1]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,NUM[hang_chuc][2]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,NUM[hang_chuc][3]);
	  	 //
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,NUM[hang_donvi][0]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_13,NUM[hang_donvi][1]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_14,NUM[hang_donvi][2]);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,NUM[hang_donvi][3]);

}
