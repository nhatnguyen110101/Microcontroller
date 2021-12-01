#include "main.h"

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

typedef unsigned char tByte;
typedef unsigned int tWord;


enum Type_error {
	NORMAL,
	ERROR_SCH_TOO_MANY_TASKS ,
	ERROR_SCH_WAITING_FOR_SLAVE_TO_ACK,
	ERROR_SCH_WAITING_FOR_START_COMMAND_FROM_MASTER ,
	ERROR_SCH_ONE_OR_MORE_SLAVES_DID_NOT_START ,
	ERROR_SCH_LOST_SLAVE ,
	ERROR_SCH_CAN_BUS_ERROR,
	ERROR_I2C_WRITE_BYTE_AT24C64,
	ERROR_SCH_CANNOT_DELETE_TASK,
};

enum Type_error Error_code_G = NORMAL;


typedef struct {
 void ( * pTask) ( void ); // con trỏ tới task
 // Thời gian chờ của task
 uint32_t Delay ;
 // Khoảng thời gian chạy của task
 uint32_t Period ;
 // Biến tăng ( được tăng bởi Sch) khi task muốn chạy.
 uint8_t RunMe;
 uint32_t TaskID ;
 } sTask ;

 // Cần được thay đổi cho từng project riêng biệt khác nhau
#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0
sTask SCH_tasks_G[SCH_MAX_TASKS] ;




void SCH_Init( void );
void SCH_Update( void );
tByte SCH_Add_Task( void ( * pFunction) () , tWord DELAY, tWord PERIOD);
void SCH_Dispatch_Tasks( void );
tByte SCH_Delete_Task( const tByte TASK_INDEX);
void SCH_Go_To_Sleep (); // Optional
void SCH_Report_Status ( void );



struct Node {
    int time_data;
    int index_data;
    struct Node* next;
    struct Node* prev;
};

struct Node* head, * tail; // Khởi tạo Node head global của dslk đôi.


struct Node* GetNewNode(int time, int index) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->time_data = time;
    newNode->index_data = index;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void Swap_Node(struct Node* root) {
    int tmp_time_data = root->next->time_data;
    int tmp_index_data = root->next->index_data;
    root->next->time_data = root->time_data;
    root->time_data = tmp_time_data;
    root->next->index_data = root->index_data;
    root->index_data = tmp_index_data;
}
int Sorting() {
    struct Node* tmpNode = tail;
    int flag_sort = 1;
    while (flag_sort && tmpNode->next != NULL) {
        if (tmpNode->time_data < tmpNode->next->time_data) {
            Swap_Node(tmpNode);
            tmpNode = tmpNode->next;
        }
        else flag_sort = 0;
    }
    return 1;
}

void InsertAtTail(int time, int data) {
    struct Node* newNode = GetNewNode(time, data);
    if (head == NULL) {
        head = newNode;
        tail = newNode;
        return;
    }
    tail->prev = newNode;
    newNode->next = tail;
    tail = newNode;

    Sorting();
}


void DeleteAtHead() {
    if (head == NULL) {
        return;
    }
    struct Node* tmp = head;
    head = head->prev;
    head->next = NULL;
    free(tmp);
}



#endif /* INC_SCHEDULER_H_ */
