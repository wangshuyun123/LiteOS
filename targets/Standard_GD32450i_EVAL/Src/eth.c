#include "eth.h"
#include "usb_conf.h"




/* Private variables ---------------------------------------------------------*/
//#if defined ( __ICCARM__ ) /*!< IAR Compiler */
//#pragma data_alignment=4
//#endif
//__ALIGN_BEGIN ETH_DMADescTypeDef  DMARxDscrTab[ETH_RXBUFNB] __ALIGN_END;/* Ethernet Rx MA Descriptor */

//#if defined ( __ICCARM__ ) /*!< IAR Compiler */
//#pragma data_alignment=4
//#endif
//__ALIGN_BEGIN ETH_DMADescTypeDef  DMATxDscrTab[ETH_TXBUFNB] __ALIGN_END;/* Ethernet Tx DMA Descriptor */

//#if defined ( __ICCARM__ ) /*!< IAR Compiler */
//#pragma data_alignment=4
//#endif
//__ALIGN_BEGIN uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE] __ALIGN_END; /* Ethernet Receive Buffer */

//#if defined ( __ICCARM__ ) /*!< IAR Compiler */
//#pragma data_alignment=4
//#endif
//__ALIGN_BEGIN uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE] __ALIGN_END; /* Ethernet Transmit Buffer */

/* Global Ethernet handle */
typedef struct
{
    int e;                

} ETH_HandleTypeDef;
static ETH_HandleTypeDef heth;
static uint8_t MACAddr[6];

/* Os ethernet interrupt handler */
void ETH_IRQHandler(void)
{
//    HAL_ETH_IRQHandler(&heth);
}


/**
  * @brief  Ethernet Rx Transfer completed callback
  * @param  heth: ETH handle
  * @retval None
  */
void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *pheth)
{
    (void)pheth;
	ethernetif_rxcb();
}

/* Private functions ---------------------------------------------------------*/

void HAL_ETH_MspInit(ETH_HandleTypeDef* ethHandle)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOG);
    rcu_periph_clock_enable(RCU_GPIOH);
    rcu_periph_clock_enable(RCU_GPIOI);
  
    gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_8);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_8);
  
    /* enable SYSCFG clock */
    rcu_periph_clock_enable(RCU_SYSCFG);
  
#ifdef MII_MODE 
  
#ifdef PHY_CLOCK_MCO
    /* output HXTAL clock (25MHz) on CKOUT0 pin(PA8) to clock the PHY */
    rcu_ckout0_config(RCU_CKOUT0SRC_HXTAL, RCU_CKOUT0_DIV1);
#endif /* PHY_CLOCK_MCO */

    syscfg_enet_phy_interface_config(SYSCFG_ENET_PHY_MII);

#elif defined RMII_MODE
    /* choose DIV2 to get 50MHz from 200MHz on CKOUT0 pin (PA8) to clock the PHY */
    rcu_ckout0_config(RCU_CKOUT0SRC_PLLP, RCU_CKOUT0_DIV4);
    syscfg_enet_phy_interface_config(SYSCFG_ENET_PHY_RMII);

#endif

#ifdef MII_MODE

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_1);
    
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_2);
    
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_7);   
    
    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_1);
    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_2);
    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_7);
    
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_11);
    
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_13);
    
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_14);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_14);   
    
    gpio_af_set(GPIOG, GPIO_AF_11, GPIO_PIN_11);
    gpio_af_set(GPIOG, GPIO_AF_11, GPIO_PIN_13);
    gpio_af_set(GPIOG, GPIO_AF_11, GPIO_PIN_14);

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_1);
    
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_2);
    
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_3);  

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_4);
    
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_5); 
    
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_1);
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_2);
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_3);
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_4);
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_5);

    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_2);
    
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_3);
    
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_6);  

    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_7);
    
    gpio_af_set(GPIOH, GPIO_AF_11, GPIO_PIN_2);
    gpio_af_set(GPIOH, GPIO_AF_11, GPIO_PIN_3);
    gpio_af_set(GPIOH, GPIO_AF_11, GPIO_PIN_6);
    gpio_af_set(GPIOH, GPIO_AF_11, GPIO_PIN_7);

    gpio_mode_set(GPIOI, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);
    gpio_output_options_set(GPIOI, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_8);  

    gpio_mode_set(GPIOI, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_output_options_set(GPIOI, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_10);
    
    gpio_af_set(GPIOI, GPIO_AF_11, GPIO_PIN_8);
    gpio_af_set(GPIOI, GPIO_AF_11, GPIO_PIN_10);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_8);
    
    gpio_af_set(GPIOB, GPIO_AF_11, GPIO_PIN_8);
      
#elif defined RMII_MODE

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_1);
    
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_2);
    
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_7);   
    
    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_1);
    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_2);
    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_7);
    
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_11);
    
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_12);
    
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_13);   
    
    gpio_af_set(GPIOB, GPIO_AF_11, GPIO_PIN_11);
    gpio_af_set(GPIOB, GPIO_AF_11, GPIO_PIN_12);
    gpio_af_set(GPIOB, GPIO_AF_11, GPIO_PIN_13);

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_1);

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_4);
    
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ,GPIO_PIN_5); 
    
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_1);
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_4);
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_5);
#endif /* MII_MODE */
}

void HAL_ETH_MspDeInit(ETH_HandleTypeDef* ethHandle)
{
//    if (ethHandle->Instance == ETH)
//    {
//        /* USER CODE BEGIN ETH_MspDeInit 0 */

//        /* USER CODE END ETH_MspDeInit 0 */
//        /* Peripheral clock disable */
//        __HAL_RCC_ETH_CLK_DISABLE();

//        /**ETH GPIO Configuration
//             PC1     ------> ETH_MDC
//             PA1     ------> ETH_REF_CLK
//             PA2     ------> ETH_MDIO
//             PA7     ------> ETH_CRS_DV
//             PC4     ------> ETH_RXD0
//             PC5     ------> ETH_RXD1
//             PB11     ------> ETH_TX_EN
//             PG13     ------> ETH_TXD0
//             PG14     ------> ETH_TXD1
//             */
//        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5);

//        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7);

//        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_11);
//        HAL_GPIO_DeInit(GPIOG, GPIO_PIN_13 | GPIO_PIN_14);

//        /* USER CODE BEGIN ETH_MspDeInit 1 */

//        /* USER CODE END ETH_MspDeInit 1 */
//    }
}

static int8_t eth_init(struct netif* netif)
{
        ErrStatus reval_state = ERROR;
        
        /* enable ethernet clock  */
        rcu_periph_clock_enable(RCU_ENET);
        rcu_periph_clock_enable(RCU_ENETTX);
        rcu_periph_clock_enable(RCU_ENETRX);
        
        /* reset ethernet on AHB bus */
        enet_deinit();
    
        reval_state = enet_software_reset();
        if(reval_state == ERROR){
            while(1){}
        }
      
    //  enet_initpara_config(HALFDUPLEX_OPTION, ENET_CARRIERSENSE_ENABLE|ENET_RECEIVEOWN_ENABLE|ENET_RETRYTRANSMISSION_DISABLE|ENET_BACKOFFLIMIT_10|ENET_DEFERRALCHECK_DISABLE);
    //  enet_initpara_config(DMA_OPTION, ENET_FLUSH_RXFRAME_ENABLE|ENET_SECONDFRAME_OPT_ENABLE|ENET_NORMAL_DESCRIPTOR);
    
#ifdef CHECKSUM_BY_HARDWARE
        enet_init(ENET_AUTO_NEGOTIATION, ENET_AUTOCHECKSUM_DROP_FAILFRAMES, ENET_BROADCAST_FRAMES_PASS);
#else  
        enet_init(ENET_AUTO_NEGOTIATION, ENET_NO_AUTOCHECKSUM, ENET_BROADCAST_FRAMES_PASS);
#endif

    
}

static int8_t eth_set_mac(struct netif* netif)
{
//    /* set MAC hardware address */
//    netif->hwaddr[0] =  heth.Init.MACAddr[0];
//    netif->hwaddr[1] =  heth.Init.MACAddr[1];
//    netif->hwaddr[2] =  heth.Init.MACAddr[2];
//    netif->hwaddr[3] =  heth.Init.MACAddr[3];
//    netif->hwaddr[4] =  heth.Init.MACAddr[4];
//    netif->hwaddr[5] =  heth.Init.MACAddr[5];

//    return 0;
}

static int8_t eth_start(struct netif* netif)
{
//    (void)netif;
//    /* Enable MAC and DMA transmission and reception */
//    (void)HAL_ETH_Start(&heth);
//    return 0;
}

static int8_t eth_output(struct netif* netif, struct pbuf* p)
{
//    err_t errval;
//    struct pbuf* q;
//    uint8_t* buffer = (uint8_t*)(heth.TxDesc->Buffer1Addr);
//    __IO ETH_DMADescTypeDef* DmaTxDesc;
//    uint32_t framelength = 0;
//    uint32_t bufferoffset = 0;
//    uint32_t byteslefttocopy = 0;
//    uint32_t payloadoffset = 0;
//    DmaTxDesc = heth.TxDesc;
//    bufferoffset = 0;

//    /* copy frame from pbufs to driver buffers */
//    for (q = p; q != NULL; q = q->next)
//    {
//        /* Is this buffer available? If not, goto error */
//        if ((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
//        {
//            errval = ERR_USE;
//            goto error;
//        }

//        /* Get bytes in current lwIP buffer */
//        byteslefttocopy = q->len;
//        payloadoffset = 0;

//        /* Check if the length of data to copy is bigger than Tx buffer size*/
//        while ( (byteslefttocopy + bufferoffset) > ETH_TX_BUF_SIZE )
//        {
//            /* Copy data to Tx buffer*/
//            memcpy( (uint8_t*)((uint8_t*)buffer + bufferoffset), (uint8_t*)((uint8_t*)q->payload + payloadoffset), (ETH_TX_BUF_SIZE - bufferoffset) );

//            /* Point to next descriptor */
//            DmaTxDesc = (ETH_DMADescTypeDef*)(DmaTxDesc->Buffer2NextDescAddr);

//            /* Check if the buffer is available */
//            if ((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
//            {
//                errval = ERR_USE;
//                goto error;
//            }

//            buffer = (uint8_t*)(DmaTxDesc->Buffer1Addr);

//            byteslefttocopy = byteslefttocopy - (ETH_TX_BUF_SIZE - bufferoffset);
//            payloadoffset = payloadoffset + (ETH_TX_BUF_SIZE - bufferoffset);
//            framelength = framelength + (ETH_TX_BUF_SIZE - bufferoffset);
//            bufferoffset = 0;
//        }

//        /* Copy the remaining bytes */
//        memcpy( (uint8_t*)((uint8_t*)buffer + bufferoffset), (uint8_t*)((uint8_t*)q->payload + payloadoffset), byteslefttocopy );
//        bufferoffset = bufferoffset + byteslefttocopy;
//        framelength = framelength + byteslefttocopy;
//    }

//    /* Prepare transmit descriptors to give to DMA */
//    (void)HAL_ETH_TransmitFrame(&heth, framelength);
//    ErrStatus enet_frame_transmit(uint8_t *buffer, uint32_t length)

//    errval = ERR_OK;

//error:

//    /* When Transmit Underflow flag is set, clear it and issue a Transmit Poll Demand to resume transmission */
//    if ((heth.Instance->DMASR & ETH_DMASR_TUS) != (uint32_t)RESET)
//    {
//        /* Clear TUS ETHERNET DMA flag */
//        heth.Instance->DMASR = ETH_DMASR_TUS;

//        /* Resume DMA transmission*/
//        heth.Instance->DMATPDR = 0;
//    }

//    return errval;
}

static struct pbuf* eth_input(struct netif* netif)
{
    struct pbuf* p = NULL;
    uint16_t len = 0;
    uint8_t* buffer;


    len = enet_rxframe_size_get();
    /* get received frame */
    if (enet_frame_receive(buffer, len))
    { 
	    return NULL;
    }

    return p;
}

struct eth_api g_eth_api = {
    .init     = eth_init,
    .set_mac  = eth_set_mac,
    .start    = eth_start,
    .output   = eth_output,
    .input    = eth_input
};



