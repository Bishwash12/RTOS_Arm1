#include "timebase.h"
#include "stm32f4xx.h"

#define ONE_SEC_LOAD       16000000

#define CTRL_ENABLE        (1U<<0)
#define CTRL_TICKINT       (1U<<1)
#define CTRL_CLCKSRC       (1U<<2)
#define CTRL_COUNTFLAG     (1U<<16)

volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;
volatile uint32_t tick_freq = 1;

void timebase_init(void)
{
	/* Initialize systick timer to operate in interrupt mode and create
	 * a delay
	 */
	/* Reload the timer with number of cycles per second */
	SysTick->LOAD = ONE_SEC_LOAD - 1;
	/* Clear Systick current value register */
	SysTick->VAL = 0;
	/* Select internal clock source */
	SysTick->CTRL = CTRL_CLCKSRC;
	/* Enable interrupt */
	SysTick->CTRL |= CTRL_TICKINT;
	/* Enable systick */
	SysTick->CTRL |= CTRL_ENABLE;
	/* Enable global interrupts */
	__enable_irq();
}
