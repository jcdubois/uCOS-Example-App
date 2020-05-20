When declaring your ISR Handler, please make sure to do the following:
- If your Handler will be using any of the Kernel services, such as Semaphores, flags, queues, etc.
  
  void ISR_Handler(void)
  {
      CPU_SR_ALLOC();
	  
      CPU_CRITICAL_ENTER();
      OSIntEnter();       /* Notify uC/OS-III or uCOS-II of ISR entry             */
      CPU_CRITICAL_EXIT();
	  
	  /* !!!!!!!SERVICE YOUR ISR HERE   */
	  /* !!!!!!!SERVICE YOUR ISR HERE   */
	  /* !!!!!!!SERVICE YOUR ISR HERE   */
	  
      OSIntExit();        /* Notify uC/OS-II or uC/OS-III of ISR exit             */
  }
  
  
- If your Handler will NOT be using any of the Kernel services.
  
  void ISR_Handler(void)
  {
	  /* !!!!!!!SERVICE YOUR ISR HERE   */
	  /* !!!!!!!SERVICE YOUR ISR HERE   */
	  /* !!!!!!!SERVICE YOUR ISR HERE   */
  }