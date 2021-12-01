#include "Scheduler.h"

extern int get_time ;
int task_min_delay = 0;
int min_delay = 100;
int flag_taskmin = 0;
int num_task =0;
int flag_list = 0;

void SCH_Init(void){
	unsigned char i ;
	for ( i = 0 ; i < SCH_MAX_TASKS; i ++) {
		SCH_Delete_Task (i) ;
	}
	Error_code_G = NORMAL;
}


unsigned char SCH_Delete_Task( const tByte TASK_INDEX) {
	 unsigned char Return_code;
	 	 if ( SCH_tasks_G[TASK_INDEX ].TaskID == 0) {
	 		// Nếu như không có task trong location này
	 		// Thì set lỗi cho biến toàn cục hiển thị lỗi.
	 		 Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
	 		// Trả về lỗi.
	 		Return_code = 1;
	 	 } else {
	 		 // Không có lỗi trả về bình thường.
	 		 Return_code = 0;
	 	 }
	 SCH_tasks_G[TASK_INDEX ].pTask = 0x0000 ;
	 SCH_tasks_G[TASK_INDEX ].Delay = 0;
	 SCH_tasks_G[TASK_INDEX ].Period = 0;
	 SCH_tasks_G[TASK_INDEX ].RunMe = 0;

	 return Return_code ; // return status
}

unsigned char SCH_Add_Task( void ( * pFunction) () , unsigned int DELAY, unsigned int PERIOD){
	unsigned char Index = 0;
	// Đầu tiên tìm một vùng trống trong mảng ( nếu còn)
	while ((SCH_tasks_G[Index].pTask != 0) && ( Index < SCH_MAX_TASKS)){
		Index++;
	}
	// Khi duyệt toàn bộ mảng nhưng không có vùng trống.
	if ( Index == SCH_MAX_TASKS){
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		return SCH_MAX_TASKS;
	}
	// Nếu chương trình chạy tới đây, thì có một vùng trống trong mảng.
	SCH_tasks_G[ Index ].pTask = pFunction ;
	SCH_tasks_G[ Index ].Delay = DELAY;
	SCH_tasks_G[ Index ].Period = PERIOD;

	if (SCH_tasks_G[ Index ].Delay == 0){
		SCH_tasks_G[ Index ].RunMe = 1;
	} else SCH_tasks_G[ Index ].RunMe = 0;

	// Tìm task có delay nhỏ nhất
	 if (min_delay > SCH_tasks_G[Index ].Delay ){
		 min_delay = SCH_tasks_G[Index ].Delay;
		 task_min_delay = Index;
	 }

	num_task++;
	return Index;
}

void SCH_Dispatch_Tasks( void ) {

	if (flag_list == 0){
		for (int i = 0; i < num_task ; i++ ){
			if (i != task_min_delay ){
				InsertAtTail(SCH_tasks_G [ i ].Delay, i);
			}
		}
		flag_list++;
	}
	unsigned char Index;
// Giải ngố 1 task khi nó tới lúc chạy.
	for ( Index = 0; Index < num_task; Index++) {
		if ( SCH_tasks_G[Index].RunMe > 0) {
			(*SCH_tasks_G[Index].pTask) () ; // Chạy task tới lượt
			SCH_tasks_G[Index].RunMe = SCH_tasks_G[Index].RunMe - 1;
		// Tải lại / giảm cờ kiểm tra task chạy
		// Nếu flag ktra task chạy vẫn còn thì sẽ tự động chạy tiếp
			if ( SCH_tasks_G[Index].Period == 0){
			 		SCH_Delete_Task(Index);
			} else SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
		}
	}
}







void SCH_Update( void ) {
	if ( SCH_tasks_G [ task_min_delay ] . pTask ) {
		 SCH_tasks_G [ task_min_delay ].Delay -- ;
		 if (SCH_tasks_G [task_min_delay ] . Delay == 0){
			 SCH_tasks_G [ task_min_delay ] . RunMe++;
		 }
	}
	if (get_time + 1 == head->time_data){
		SCH_tasks_G [ head->index_data ].RunMe++;
		if (SCH_tasks_G [ head->index_data ].Period != 0){
			int new_val  = get_time + 1 + SCH_tasks_G [ head->index_data ].Period;
			InsertAtTail(new_val,  head->index_data);
		}
		DeleteAtHead();
	}
}
