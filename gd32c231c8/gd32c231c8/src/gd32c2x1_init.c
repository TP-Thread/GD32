/*
    \file  gd32c2x1_init.c
*/
/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32c2x1_init.h"

/* External Includes*/
/* user code [External Includes] begin */

/* user code [External Includes] end */

/* Private Type Definitions */
/* user code [Private Type Definitions] begin */

/* user code [Private Type Definitions] end */

/* Private Macros */
/* user code [Private Macros] begin */

/* user code [Private Macros] end */


/* Private Constants */
/* user code [Private Constants] begin */

/* user code [Private Constants] end */


/* Private Variables */
/* user code [Private Variables] begin */

/* user code [Private Variables] end */


/* Private Function Declaration */
/* user code [Private Function Declaration] begin */

/* user code [Private Function Declaration] end */


/* Extern Variables */
/* user code [Extern Variables] begin */

/* user code [Extern Variables] end */



/*!
    \brief      SYSTEM initialization function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void msd_system_init(void)
{
/* user code [system_init local 0] begin */

/* user code [system_init local 0] end */




    rcu_periph_clock_enable(RCU_SYSCFG);

    nvic_irq_enable(NonMaskableInt_IRQn, 0);
    nvic_irq_enable(HardFault_IRQn, 0);
    nvic_irq_enable(SVCall_IRQn, 0);
    nvic_irq_enable(PendSV_IRQn, 0);
    nvic_irq_enable(SysTick_IRQn, 0);


/* user code [system_init local 1] begin */

/* user code [system_init local 1] end */
}


/*!
    \brief      CLOCK initialization function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void msd_clock_init(void)
{
/* user code [clock_init local 0] begin */

/* user code [clock_init local 0] end */






    rcu_osci_on(RCU_IRC48M);
    while(rcu_osci_stab_wait(RCU_IRC48M) != SUCCESS);
    rcu_irc48m_adjust_value_set(16);

        fmc_wscnt_set(FMC_WAIT_STATE_1);
    rcu_ahb_clock_config(RCU_AHB_CKSYS_DIV1);
    rcu_apb_clock_config(RCU_APB_CKAHB_DIV1);

    rcu_irc48mdiv_sys_clock_config(RCU_IRC48MDIV_SYS_1);
    rcu_system_clock_source_config(RCU_CKSYSSRC_IRC48MDIV_SYS);
    while(RCU_SCSS_IRC48MDIV != rcu_system_clock_source_get());













/* update SystemCoreClock value */
SystemCoreClockUpdate();

/* setup systick timer for 1000Hz interrupts */
if (SysTick_Config(SystemCoreClock / 1000U)){
    /* capture error */
    while (1);
}

systick_clksource_set(SYSTICK_CLKSOURCE_HCLK);


/* user code [clock_init local 1] begin */

/* user code [clock_init local 1] end */
}


/* user code [Public Functions Implementations] begin */

/* user code [Public Functions Implementations] end */

/* user code [Private Functions Implementations] begin */

/* user code [Private Functions Implementations] end */

