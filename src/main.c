#include "gd32e10x.h"
/* change as needed */
#define LEDPORT     GPIOC
#define LEDPIN      GPIO_PIN_13
#define LED_CLOCK   RCU_GPIOC

void systick_config(void);
void delay_1ms(uint32_t count);

int main(void)
{
    systick_config();

    rcu_periph_clock_enable(LED_CLOCK);

    /* set output as output */
    gpio_init(LEDPORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LEDPIN);
    while (1)
    {
        gpio_bit_set(LEDPORT, LEDPIN);
        delay_1ms(1000);
        gpio_bit_reset(LEDPORT, LEDPIN);
        delay_1ms(1000);
    }
}

volatile static uint32_t delay;

void systick_config(void)
{
    /* setup systick timer for 1000Hz interrupts */
    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        /* capture error */
        while (1)
        {
        }
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

void delay_1ms(uint32_t count)
{
    delay = count;

    while (0U != delay)
    {
    }
}

void delay_decrement(void)
{
    if (0U != delay)
    {
        delay--;
    }
}

void NMI_Handler(void) {}

void HardFault_Handler(void)
{
    while (1)
        ;
}

void MemManage_Handler(void)
{
    while (1)
        ;
}

void BusFault_Handler(void)
{
    while (1)
        ;
}

void UsageFault_Handler(void)
{
    while (1)
        ;
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
    delay_decrement();
}