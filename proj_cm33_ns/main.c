/*****************************************************************************
* File Name        : main.c
*
* Description      : This source file contains the main routine for non-secure
*                    application in the CM33 CPU
*
* Related Document : See README.md
*
*******************************************************************************
* (c) 2023-2025, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
* 
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/

#include "cybsp.h"
#include "retarget_io_init.h"

/*******************************************************************************
* Macros
*******************************************************************************/
#define BLINKY_LED_DELAY_MSEC       (1000U)

/* The timeout value in microseconds used to wait for CM55 core to be booted */
#define CM55_BOOT_WAIT_TIME_USEC    (10U)

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function of the CM33 non-secure application. 
* 
* It initializes the device and board peripherals. It also initializes the 
* retarget-io middleware to be used with the debug UART port. The LED pin is 
* initialized with * default configurations. The CM55 core is enabled and then
* the programs enters * an infinite while loop which toggles the LED with a 
* frequency of 1 Hz. 
*
* Parameters:
*  none
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board initialization failed. Stop program execution */
    if (CY_RSLT_SUCCESS != result)
    {
        handle_app_error();
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize retarget-io middleware */
    init_retarget_io();

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");

    printf("****************** "
           "PSOC Edge MCU: Basic Secure Application "
           "****************** \r\n\n");

    printf("Welcome to Basic Secure Application!!!\r\n\n");
    printf("For more projects, "
           "visit our code examples repositories:\r\n\n");

    printf("https://github.com/Infineon/"
           "Code-Examples-for-ModusToolbox-Software\r\n\n");


    /* Enable CM55. CY_CM55_APP_BOOT_ADDR must be updated if CM55 memory layout is changed. */
    Cy_SysEnableCM55(MXCM55, CY_CM55_APP_BOOT_ADDR, CM55_BOOT_WAIT_TIME_USEC);

    for(;;)
    {
        Cy_GPIO_Inv(CYBSP_USER_LED1_PORT, CYBSP_USER_LED1_PIN);
        Cy_SysLib_Delay(BLINKY_LED_DELAY_MSEC);
    }

}


/* [] END OF FILE */
