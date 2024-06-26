/*
 * drv8323.c
 *
 *  Created on: 26 Oct 2020
 *      Author: zandor
 */


#include "drv8323_spi.h"

#include "stdio.h"
#include "drv8232_io.h"

volatile SPIStruct s_drv832xSPI;

//void SPI1Process(void)
//{
//	if(s_drv832xSPI.SPI_RX_Flag == 1){
//		//Check whats in the TX register to see what we asked from the DRV. Once its set up we interact through 3xPWM
//		s_drv832xSPI.SPI_RX_Flag = 0;
//		printf("spi2Tx: 0x%x, spi2Rx: 0x%x\n\r", s_drv832xSPI.SPI_TX_Data[0],s_drv832xSPI.SPI_RX_Data[0]);
//	}
//}


void DRV832x_initSPIInterface(SPI_HandleTypeDef* pspi){
//	DRV832x_enable(Enable_GPIOx,Enable_GPIO_Pin);
//	s_drv832xSPI.PORT_GPIOx = GPIOx;
//	s_drv832xSPI.CS_GPIO_Pin = GPIO_Pin;
	s_drv832xSPI.pSPI_Handle = pspi;
	s_drv832xSPI.SPI_TX_Flag = 0;
	s_drv832xSPI.SPI_RX_Flag = 0;

}

void DRV832x_enableHiZState(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

void DRV832x_disableHiZState(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}

void DRV832x_enable(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}

void DRV832x_disable(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}


uint16_t DRV832x_trigger_spi_write(uint16_t val)
{
	s_drv832xSPI.SPI_TX_Data[0] = val;
	drv8323io_set_cs(0);
	HAL_SPI_TransmitReceive(s_drv832xSPI.pSPI_Handle, (uint8_t*)s_drv832xSPI.SPI_TX_Data, (uint8_t*)s_drv832xSPI.SPI_RX_Data,1,1000);
	drv8323io_set_cs(1);
	return s_drv832xSPI.SPI_RX_Data[0] & 0x7FF;
}

uint16_t DRV832x_read_FSR1(void)
{
    uint16_t val = READ_CMD | (FSR1 << 11);
    DRV832x_trigger_spi_write(val);
    return s_drv832xSPI.SPI_RX_Data[0] & 0x7FF;
}

uint16_t DRV832x_read_FSR2(void)
{
    uint16_t val = READ_CMD | (FSR2 << 11);
    DRV832x_trigger_spi_write(val);
    return s_drv832xSPI.SPI_RX_Data[0] & 0x7FF;
}

uint16_t DRV832x_trigger_read_register(int reg)
{
    return DRV832x_trigger_spi_write(READ_CMD | (reg<<11));
}

void DRV832x_write_register(int reg, int val)
{
	DRV832x_trigger_spi_write((reg<<11) | val);
}

void DRV832x_write_DCR(int DIS_CPUV, int DIS_GDF, int OTW_REP, int PWM_MODE, int PWM_COM, int PWM_DIR, int COAST, int BRAKE, int CLR_FLT)
{
    uint16_t val = (DCR<<11) | (DIS_CPUV<<9) | (DIS_GDF<<8) | (OTW_REP<<7) | (PWM_MODE<<5) | (PWM_COM<<4) | (PWM_DIR<<3) | (COAST<<2) | (BRAKE<<1) | CLR_FLT;
    DRV832x_trigger_spi_write(val);
}
void DRV832x_write_HSR(int LOCK, int IDRIVEP_HS, int IDRIVEN_HS)
{
    uint16_t val = (HSR<<11) | (LOCK<<8) | (IDRIVEP_HS<<4) | IDRIVEN_HS;
    DRV832x_trigger_spi_write(val);
    }
void DRV832x_write_LSR(int CBC, int TDRIVE, int IDRIVEP_LS, int IDRIVEN_LS)
{
    uint16_t val = (LSR<<11) | (CBC<<10) | (TDRIVE<<8) | (IDRIVEP_LS<<4) | IDRIVEN_LS;
    DRV832x_trigger_spi_write(val);
    }
void DRV832x_write_OCPCR(int TRETRY, int DEAD_TIME, int OCP_MODE, int OCP_DEG, int VDS_LVL)
{
    uint16_t val = (OCPCR<<11) | (TRETRY<<10) | (DEAD_TIME<<8) | (OCP_MODE<<6) | (OCP_DEG<<4) | VDS_LVL;
    DRV832x_trigger_spi_write(val);
    }
void DRV832x_write_CSACR(int CSA_FET, int VREF_DIV, int LS_REF, int CSA_GAIN, int DIS_SEN, int CSA_CAL_A, int CSA_CAL_B, int CSA_CAL_C, int SEN_LVL)
{
    uint16_t val = (CSACR<<11) | (CSA_FET<<10) | (VREF_DIV<<9) | (LS_REF<<8) | (CSA_GAIN<<6) | (DIS_SEN<<5) | (CSA_CAL_A<<4) | (CSA_CAL_B<<3) | (CSA_CAL_C<<2) | SEN_LVL;
    DRV832x_trigger_spi_write(val);
}

void DRV832x_print_faults(void)
{
	printf("DRV832x_print_faults => \n");
	uint16_t val1 = DRV832x_trigger_read_register(FSR1);
	uint16_t val2 = DRV832x_trigger_read_register(FSR2);
	if((val1 & 0x3FF) == 0) {
		printf("no faults in FSR1\n");
	} else {
		if(val1 & (1<<10)){printf("\n\rFAULT\n\r");}

		if(val1 & (1<<9)){printf("VDS_OCP\n\r");}
		if(val1 & (1<<8)){printf("GDF\n\r");}
		if(val1 & (1<<7)){printf("UVLO\n\r");}
		if(val1 & (1<<6)){printf("OTSD\n\r");}
		if(val1 & (1<<5)){printf("VDS_HA\n\r");}
		if(val1 & (1<<4)){printf("VDS_LA\n\r");}
		if(val1 & (1<<3)){printf("VDS_HB\n\r");}
		if(val1 & (1<<2)){printf("VDS_LB\n\r");}
		if(val1 & (1<<1)){printf("VDS_HC\n\r");}
		if(val1 & (1)){printf("VDS_LC\n\r");}
	}
	if((val1 & 0x3FF) == 0) {
		printf("no faults in FSR2");
	} else {
		if(val2 & (1<<10)){printf("SA_OC\n\r");}
		if(val2 & (1<<9)){printf("SB_OC\n\r");}
		if(val2 & (1<<8)){printf("SC_OC\n\r");}
		if(val2 & (1<<7)){printf("OTW\n\r");}
		if(val2 & (1<<6)){printf("CPUV\n\r");}
		if(val2 & (1<<5)){printf("VGS_HA\n\r");}
		if(val2 & (1<<4)){printf("VGS_LA\n\r");}
		if(val2 & (1<<3)){printf("VGS_HB\n\r");}
		if(val2 & (1<<2)){printf("VGS_LB\n\r");}
		if(val2 & (1<<1)){printf("VGS_HC\n\r");}
		if(val2 & (1)){printf("VGS_LC\n\r");}
	}
    }

void DRV832x_enable_gd(void)
{
	DRV832x_trigger_read_register(DCR);

    uint16_t val = (s_drv832xSPI.SPI_RX_Data[0]) & (~(0x1<<2));
    DRV832x_write_register(DCR, val);
}

void DRV832x_disable_gd(void)
{
	DRV832x_trigger_read_register(DCR);
    uint16_t val = (s_drv832xSPI.SPI_RX_Data[0]) | (0x1<<2);
    DRV832x_write_register(DCR, val);
}

void DRV832x_calibrate(void)
{
    uint16_t val = (0x1<<4) + (0x1<<3) + (0x1<<2);
    DRV832x_write_register(CSACR, val);
}

//TODO Use this method to configure the drv8323
void DRV832x_blocking_configure(void){
	printf("\n\rConfiguring DRV8323\n\r");
	printf("1:write DRV8323_CSAR\n\r");
	DRV832x_calibrate();
	HAL_Delay(5);
	//Driver Control Register config.
	printf("2:write DRV8323_DCR\n\r");
	DRV832x_write_DCR(DIS_CPUV_EN, DIS_GDF_DIS, OTW_REP_DIS, PWM_MODE_1X, 0x0, 0x0, 0x0, 0x0, 0x1);
	printf("spi2Tx: 0x%x, spi2Rx: 0x%x\n\r", s_drv832xSPI.SPI_TX_Data[0],s_drv832xSPI.SPI_RX_Data[0]);
	HAL_Delay(5);
	printf("3:read DRV8323_DCR : 0x%X\n\r",DRV832x_trigger_read_register(DCR));

	HAL_Delay(5);
	//Set Current Sense Register
    printf("4:write DRV8323_CSAR\n\r");
    DRV832x_write_CSACR(CSA_FET_SP, VREF_DIV_2, 0x0, CSA_GAIN_40, DIS_SEN_EN, 0x1, 0x1, 0x1, SEN_LVL_1_0);
    printf("spi2Tx: 0x%x, spi2Rx: 0x%x\n\r", s_drv832xSPI.SPI_TX_Data[0],s_drv832xSPI.SPI_RX_Data[0]);
    HAL_Delay(5);

}

uint16_t DRV8323regDrvCtrl =
  0 << 9  | //DIS_CPUV
  1 << 8  | //DIS_GDF
  0 << 7  | //OTW_REP
  2 << 5  | //PWM_MODE
  0 << 4  | //1PWM_COM
  0 << 3  | //1PWM_DIR
  0 << 2  | //COAST
  0 << 1  | //BRAKE
  0;        //CLR_FLT

uint16_t DRV8323regGateDrvHS =
  3 << 8  | //LOCK
  11 << 4 | //IDRIVEP_HS
  15;       //IDRIVEN_HS

uint16_t DRV8323regGateDrvLS =
  1 << 10 | //CBC
  2 << 8  | //TDRIVE
  15 << 4 | //IDRIVEP_LS
  15;       //IDRIVEN_LS

uint16_t DRV8323regOcpCtrl =
  0 << 10 | //TRETRY
  1 << 8  | //DEAD_TIME
  1 << 6  | //OCP_MODE
  2 << 4  | //OCP_DEG
  0;        //VDS_LVL

uint16_t DRV8323regCsaCtrl =
  1 << 10 | //CSA_FET
  1 << 9  | //VREF_DIV
  0 << 8  | //LS_REF
  2 << 6  | //CSA_GAIN
  0 << 5  | //DIS_SEN
  0 << 4  | //CSA_CAL_A
  0 << 3  | //CCSA_CAL_B
  0 << 2  | //CCSA_CAL_C
  3;        //CSEN_LVL

extern SPI_HandleTypeDef hspi1;

uint16_t DRV8323_readSpi(uint8_t regAdr)
{

	uint16_t controlword = 0x8000 | ((regAdr & 0x7) << 11); //MSbit =1 for read, address is 3 bits (MSbit is always 0), data is 11 bits
	uint16_t recbuff = 0xbeef;

	drv8323io_set_cs(0);
	HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)(&controlword), (uint8_t*)(&recbuff), 1, 1000);
	drv8323io_set_cs(1);
	return (0x7ff&recbuff);
}

void DRV8323_writeSpi(uint8_t regAdr, uint16_t regVal)
{
	uint16_t controlword = ((regAdr & 0x7) << 11) | (regVal & 0x7ff); //MSbit =0 for write, address is 3 bits (MSbit is always 0), data is 11 bits

	uint16_t recbuff = 0xbeef;
	drv8323io_set_cs(0);
	HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)(&controlword), (uint8_t*)(&recbuff), 1, 1000);
	drv8323io_set_cs(1);
	return;
}

void DRV8323_setupSpi()
{
    volatile uint16_t temp;
    drv8323io_set_call(1);
    HAL_Delay(100);
    drv8323io_set_call(0);
	//In TI sample firmware http://www.ti.com/tool/tida-00774, DRV8323regGateDrvHS is written first, and it is written twice
	//In http://www.ti.com/tool/boostxl-drv8323rs, the 5 control register are just written once in order.
	DRV8323_writeSpi(ADR_DRV_CTRL, DRV8323regDrvCtrl);
	DRV832x_print_faults();
	printf("WRITE ADR_DRV_CTRL : %X\r\n",DRV8323regDrvCtrl);
	temp = DRV8323_readSpi(ADR_DRV_CTRL);
	printf("ADR_DRV_CTRL : %X\r\n",temp);
	HAL_Delay(1);
	DRV832x_write_DCR(DIS_CPUV_EN, DIS_GDF_DIS, OTW_REP_DIS, PWM_MODE_1X, 0x0, 0x0, 0x0, 0x0, 0x1);
	printf("spi2Tx: 0x%x, spi2Rx: 0x%x\n\r", s_drv832xSPI.SPI_TX_Data[0],s_drv832xSPI.SPI_RX_Data[0]);
	temp = DRV8323_readSpi(ADR_DRV_CTRL);
	printf("ADR_DRV_CTRL : %X\r\n",temp);
	DRV8323_writeSpi(ADR_DRV_CTRL, DRV8323regDrvCtrl);
	printf("WRITE ADR_DRV_CTRL : %X\r\n",DRV8323regDrvCtrl);
	printf("3:read DRV8323_DCR : 0x%X\n\r",DRV832x_trigger_read_register(DCR));


	DRV8323_writeSpi(ADR_GATE_DRV_HS, DRV8323regGateDrvHS);
	HAL_Delay(1);
	DRV8323_writeSpi(ADR_GATE_DRV_LS, DRV8323regGateDrvLS);
	HAL_Delay(1);
	DRV8323_writeSpi(ADR_OCP_CTRL, DRV8323regOcpCtrl);
	HAL_Delay(1);
	DRV8323_writeSpi(ADR_CSA_CTRL, DRV8323regCsaCtrl);
	HAL_Delay(1);

    temp = DRV8323_readSpi(ADR_FAULT_STAT);
    temp = DRV8323_readSpi(ADR_VGS_STAT);
    temp = DRV8323_readSpi(ADR_DRV_CTRL);
    printf("ADR_DRV_CTRL : %X\r\n",temp);
    temp = DRV8323_readSpi(ADR_GATE_DRV_HS);
    temp = DRV8323_readSpi(ADR_GATE_DRV_LS);
    temp = DRV8323_readSpi(ADR_OCP_CTRL);
    temp = DRV8323_readSpi(ADR_CSA_CTRL);
    temp = temp;
	return;
}
