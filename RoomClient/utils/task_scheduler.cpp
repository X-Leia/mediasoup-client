/**
 * This file is part of janus_client project.
 * Author:    Jackie Ou
 * Created:   2021-3-13s
 **/

#include "task_scheduler.h"
#include "rtc_base/thread.h"

namespace vi {
	std::shared_ptr<TaskScheduler> TaskScheduler::create()
	{
		return std::shared_ptr<TaskScheduler>(new TaskScheduler(), [thread = rtc::Thread::Current()](TaskScheduler* ptr){
            thread->PostTask([ptr]() {
				delete ptr;
			});
		});
	}
}