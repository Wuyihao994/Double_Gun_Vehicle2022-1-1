#include "usart.h"
#include "dbus.h"

uint8_t USART1_RX_BUF[2][BSP_USART1_DMA_RX_BUF_LEN];

/*串口调试助手串口1初始化*/
void usart1_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStruct;
    DMA_InitTypeDef DMA_InitStruct;

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Low_Speed;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);

    USART_InitStructure.USART_BaudRate=100000;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_InitStructure.USART_Mode=USART_Mode_Rx;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_Parity=USART_Parity_Even;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_Init(USART1,&USART_InitStructure);

    USART_Cmd(USART1,ENABLE);

    DMA_DeInit(DMA2_Stream2);

    while (DMA_GetCmdStatus(DMA2_Stream2) != DISABLE) {}

    DMA_InitStruct.DMA_Channel=DMA_Channel_4;
    DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&(USART1->DR);
    DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)&USART1_RX_BUF[0][0];
    DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralToMemory;
    DMA_InitStruct.DMA_BufferSize=BSP_USART1_DMA_RX_BUF_LEN;
    DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
    DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
    DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;
    DMA_InitStruct.DMA_Priority=DMA_Priority_Medium;
    DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Disable;
    DMA_InitStruct.DMA_FIFOThreshold=DMA_FIFOThreshold_1QuarterFull;
    DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;
    DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream2,&DMA_InitStruct);

    DMA_DoubleBufferModeConfig(DMA2_Stream2,(uint32_t)&USART1_RX_BUF[1][0],DMA_Memory_0);
    DMA_DoubleBufferModeCmd(DMA2_Stream2,ENABLE);

    DMA_Cmd(DMA2_Stream2,ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
}
/*DBUS遥控器数据DMA双通道接收中断*/
void USART1_IRQHandler(void)
{
    static uint32_t this_time_rx_len = 0;
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
        {
            //clear the idle pending flag
            (void)USART1->SR;
            (void)USART1->DR;
//            RC_CtrlData.online_flag=1;
            if(DMA_GetCurrentMemoryTarget(DMA2_Stream2) == 0)
                {
                    DMA_Cmd(DMA2_Stream2, DISABLE);
                    this_time_rx_len = BSP_USART1_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
                    DMA2_Stream2->NDTR = (uint16_t)BSP_USART1_DMA_RX_BUF_LEN;
                    DMA2_Stream2->CR |= (uint32_t)(DMA_SxCR_CT);
                    DMA_Cmd(DMA2_Stream2, ENABLE);
                    if(this_time_rx_len == RC_FRAME_LENGTH)
                        {
                            dbus_data_process(USART1_RX_BUF[0]);
                        }
                }
            else
                {
                    DMA_Cmd(DMA2_Stream2, DISABLE);
                    this_time_rx_len = BSP_USART1_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
                    DMA2_Stream2->NDTR = (uint16_t)BSP_USART1_DMA_RX_BUF_LEN;
                    DMA2_Stream2->CR &= ~(uint32_t)(DMA_SxCR_CT);
                    DMA_Cmd(DMA2_Stream2, ENABLE);
                    if(this_time_rx_len == RC_FRAME_LENGTH)
                        {
                            dbus_data_process(USART1_RX_BUF[1]);
                        }
                }
        }
}
