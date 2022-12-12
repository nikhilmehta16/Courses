#include <gthread.h>
#include <ulib.h>

static struct process_thread_info tinfo __attribute__((section(".user_data"))) = {};
/*XXX 
      Do not modifiy anything above this line. The global variable tinfo maintains user
      level accounting of threads. Refer gthread.h for definition of related structs.
 */


/* Returns 0 on success and -1 on failure */
/* Here you can use helper system call "make_thread_ready" for your implementation */

int gthread_exit_handler();

int gthread_create(int *tid, void *(*fc)(void *), void *arg) {
	/* You need to fill in your implementation here*/
	if(tinfo.num_threads >= MAX_THREADS) return -1;
	// printf("Error Check1\n");
	void *stack_all = mmap(NULL, TH_STACK_SIZE, PROT_READ|PROT_WRITE, 0);
	if(stack_all == NULL || stack_all == MAP_ERR) return -1;

	long pid;
	struct thread_info *thread;

	for(int i = 0;i<MAX_THREADS;i++) {
		if(tinfo.threads[i].status==TH_STATUS_UNUSED){
			thread = &tinfo.threads[i];	
			// printf("INCREASED %d",i);
			tinfo.num_threads=tinfo.num_threads+1;
			break;
		}
	}
	*(u64*)((u64)stack_all + TH_STACK_SIZE -8) = (u64)(&gthread_exit_handler);

	// printf("Error Check3\n");
	pid = clone(*fc, ((u64)stack_all)+TH_STACK_SIZE-8, arg);
	if(pid<0) return -1;
	// printf("Error Check4\n");
	*tid = tinfo.num_threads - 1;
	thread->tid = tinfo.num_threads - 1;
	thread->status = TH_STATUS_USED;
	thread->stack_addr = stack_all + TH_STACK_SIZE -8;
	thread->pid = (u8)pid;
	// printf("Error Check5\n");
	make_thread_ready(pid);
	thread->status = TH_STATUS_ALIVE;
	return 0;
}

int gthread_exit(void *retval) {

	/* You need to fill in your implementation here*/
	
	u8 pid = getpid();

	for(int i =0;i<MAX_THREADS;i++){
		if(tinfo.threads[i].pid == pid){
			struct  thread_info *thread;
			thread = &tinfo.threads[i];
			thread->ret_addr = retval;
			thread->status = TH_STATUS_DEAD;
			exit(0);
			};
	}
	//call exit
	exit(0);
}

void* gthread_join(int tid) {
        
     /* Here you can use helper system call "wait_for_thread" for your implementation */
       
     /* You need to fill in your implementation here*/

	 for(int i = 0;i<MAX_THREADS;i++){
		if((u8)tinfo.threads[i].tid==(u8)tid){
			struct thread_info *thread = &tinfo.threads[i];
			
			if(thread->status == TH_STATUS_UNUSED) return NULL;
			if(thread->status = TH_STATUS_ALIVE) wait_for_thread(thread->pid);
			
			thread->status = TH_STATUS_UNUSED;
			tinfo.num_threads--;
			
			for(int i = 0;i<MAX_GALLOC_AREAS;i++){
				if(thread->priv_areas->owner == thread){
					munmap((void*)thread->priv_areas[i].start, (int)thread->priv_areas[i].length);
					thread->priv_areas[i].owner=NULL;
				}
			}

			munmap((void*)((long)thread->stack_addr-TH_STACK_SIZE + 8), TH_STACK_SIZE);
			
			return thread->ret_addr;
		} 
		if(i==(MAX_THREADS-1)) return NULL; 
	 }

	return NULL;
}


/*Only threads will invoke this. No need to check if its a process
 * The allocation size is always < GALLOC_MAX and flags can be one
 * of the alloc flags (GALLOC_*) defined in gthread.h. Need to 
 * invoke mmap using the proper protection flags (for prot param to mmap)
 * and MAP_TH_PRIVATE as the flag param of mmap. The mmap call will be 
 * handled by handle_thread_private_map in the OS.
 * */

void* gmalloc(u32 size, u8 alloc_flag)
{
   
	/* You need to fill in your implementation here*/

}
/*
   Only threads will invoke this. No need to check if the caller is a process.
*/
int gfree(void *ptr)
{
   
    /* You need to fill in your implementation here*/


     	return 0;
}

int gthread_exit_handler(){
	void *retval;
	asm volatile("mov %%rax, %0;" : "=r" (retval) : : "memory");
	gthread_exit((void*)retval);
	return 0;	
}