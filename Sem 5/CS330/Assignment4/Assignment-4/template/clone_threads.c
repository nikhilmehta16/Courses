#include<clone_threads.h>
#include<entry.h>
#include<context.h>
#include<memory.h>
#include<lib.h>
#include<mmap.h>

/*
  system call handler for clone, create thread like 
  execution contexts. Returns pid of the new context to the caller. 
  The new context starts execution from the 'th_func' and 
  use 'user_stack' for its stack
*/
long do_clone(void *th_func, void *user_stack, void *user_arg) 
{
  


  struct exec_context *new_ctx = get_new_ctx();
  struct exec_context *ctx = get_current_ctx();

  u32 pid = new_ctx->pid;
  
  if(!ctx->ctx_threads){  // This is the first thread
          ctx->ctx_threads = os_alloc(sizeof(struct ctx_thread_info));
          bzero((char *)ctx->ctx_threads, sizeof(struct ctx_thread_info));
          ctx->ctx_threads->pid = ctx->pid;
  }
     
 /* XXX Do not change anything above. Your implementation goes here*/
  
  
  // allocate page for os stack in kernel part of process's VAS
  // The following two lines should be there. The order can be 
  // decided depending on your logic.

  if(pid>=MAX_THREADS+3) return -1;

   struct thread new_thread;

   setup_child_context(new_ctx);
   new_thread.parent_ctx = ctx;
   new_thread.pid = pid;
   new_thread.status = TH_USED;
   *(find_unused_thread(ctx)) = new_thread;

   new_ctx->type = EXEC_CTX_USER_TH;    // Make sure the context type is thread
   new_ctx->state = WAITING;
   new_ctx->ppid = ctx->pid;


  //copying most of the parts of parent_ctx to ctx for new thread
	 for(int i=0; i<CNAME_MAX; i++) new_ctx->name[i] = ctx->name[i];
   for(int i=0; i<MAX_MM_SEGS; i++) new_ctx->mms[i] = ctx->mms[i];
	 for(int i=0; i<MAX_OPEN_FILES; i++) new_ctx->files[i] = ctx->files[i];
	 for(int i=0; i<MAX_SIGNALS; i++) new_ctx->sighandlers[i] = ctx->sighandlers[i];
   new_ctx->ticks_to_alarm = ctx->ticks_to_alarm;
   new_ctx->ticks_to_sleep = ctx->ticks_to_sleep;
   new_ctx->alarm_config_time = ctx->alarm_config_time;
   new_ctx->pending_signal_bitmap = ctx->pending_signal_bitmap;
   new_ctx->used_mem = ctx->used_mem;
   new_ctx->vm_area = ctx->vm_area;
   new_ctx->os_rsp = ctx->os_rsp;
   new_ctx->regs = ctx->regs;
   new_ctx->pgd = ctx->pgd;
   new_ctx->regs.entry_rip = (u64)th_func; // instruction pointer
	 new_ctx->regs.entry_rsp = (u64)user_stack; //top of stack 
	 new_ctx->regs.rbp = (u64)user_stack; // base of stack
	 new_ctx->regs.rdi = (u64)user_arg; // function argument

	


  return pid;
	
  return -1;

}

/*This is the page fault handler for thread private memory area (allocated using 
 * gmalloc from user space). This should fix the fault as per the rules. If the the 
 * access is legal, the fault handler should fix it and return 1. Otherwise it should
 * invoke segfault_exit and return -1*/

int handle_thread_private_fault(struct exec_context *current, u64 addr, int error_code)
{
  
   /* your implementation goes here*/
   
    segfault_exit(current->pid, current->regs.entry_rip, addr);
    return -1;
}

/*This is a handler called from scheduler. The 'current' refers to the outgoing context and the 'next' 
 * is the incoming context. Both of them can be either the parent process or one of the threads, but only
 * one of them can be the process (as we are having a system with a single user process). This handler
 * should apply the mapping rules passed in the gmalloc calls. */

int handle_private_ctxswitch(struct exec_context *current, struct exec_context *next)
{
  
   /* your implementation goes here*/
   return 0;	

}
