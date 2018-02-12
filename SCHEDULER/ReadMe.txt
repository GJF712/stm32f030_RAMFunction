The code in the Scheduler folder is the generic scheduler code. 

The code in Delay.c/h, DelayInt.c/h, Event.c/h, Synch.c/h and SynchInt.c/h is the specialization code for a specific implementation, 
defining the task lists and then interfacing in to the generic scheule code. These filesare are provided as examples, and will need modification for a specific implementation.
// 1 EXECUTABLE FUNCION CALLED IN MAIN ROUTINE
The function Sched_Exec() is what runs the scheduler. It would be used something like this:

INT16_T                         main
    ( VOID_T
    )
{
    System_Init();

    // start scheduler timer tick
    Timer0_SchedTimerStart();

    // run the scheduler
    Sched_Exec();

    // scheduler should never exit
    Assert(FALSE);

    return 0;
}




// 2 EXECUTABLE FUCTION CALLED IN INTERRUPT SERVICE ROUTINE 

The function
SynchInt_Exec();
needs to be called on aby the regular timer tick, and is called in this example code at an interval of TIMER0_SYNCHINT_INTERVAL_MS. 

Note the definition

#define SYNCHINT_TASK_INTERVAL_MS       TIMER0_SYNCHINT_INTERVAL_MS

in SynchInt.h to give access to this data to SynchInt.



// 3 TASKS,
It is a good idea to name tasks in a consistent manner. Example task defintions are:
/******************************************************************************
Synch_SynchTask
Update rate: 1/second. Records on time.
*******************************************************************************
******************************************************************************/

LOCAL_FUNC VOID_T               Synch_SynchTask
    ( VOID_T
    )
{
	...
}


/******************************************************************************
RTC_EventTask
Event task on operations completion. All opertions will terminate with either a
delay task or event task call.
*******************************************************************************
    data                        Event data
******************************************************************************/

VOID_T                          RTC_EventTask
    ( CONST EVENT_DATA_T        data
    )
{
	...
}


/****************************************************************************
RTC_DelayTask
Delay for timing of TWI RTC operations. All opertions will terminate with
either a delay task or event task call.
*****************************************************************************
    retval                      re-trigger time,  or 0 for no re-trigger
****************************************************************************/

DELAY_S_INTERVAL_T              RTC_DelayTask
    ( VOID_T
    )
{
	...
	// return delay task re-trigger time (0 = no automatic re-trigger)
    	return 0uL;
}
