/*
 *--------------------------------------------------------------------------------
 *	FileName		accelerometer.h	
 *	Brief			Accelerometer(MMA8452Q) driver header
 *	Microchip		KEA128
 *	Author			YTom
 *	E-mail			ybb331082@126.com
 *	ModifyTime		
 *	Copyright 		2017 TU-Smart. All Rights Reserved.
 *	Info			
 *--------------------------------------------------------------------------------
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "common.h"
#include "i2c.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/* Register Map */
#define MMA_STATUS				0x00	/* Real time status */
#define MMA_OUT_X_MSB			0x01 	/* [7:0] are 8 MSBs of 12-bit sample. */
#define MMA_OUT_X_LSB			0x02 	/* [7:4] are 4 LSBs of 12-bit sample. */
#define MMA_OUT_Y_MSB			0x03 	/* [7:0] are 8 MSBs of 12-bit sample. */
#define MMA_OUT_Y_LSB			0x04 	/* [7:4] are 4 LSBs of 12-bit sample. */
#define MMA_OUT_Z_MSB			0x05 	/* [7:0] are 8 MSBs of 12-bit sample. */
#define MMA_OUT_Z_LSB			0x06 	/* [7:4] are 4 LSBs of 12-bit sample. */
#define MMA_SYSMOD				0x0B 	/* Current System Mode */
#define MMA_INT_SOURCE			0x0C 	/* Interrupt status */
#define MMA_WHO_AM_I			0x0D 	/* Device ID (0x2A) */
#define MMA_XYZ_DATA_CFG		0x0E 	/* HPF Data Out and Dynamic Range Settings */
#define MMA_HP_FILTER_CUTOFF	0x0F 	/* Cut-off frequency is set to 16 Hz@ 800 Hz */
#define MMA_PL_STATUS			0x10 	/* Landscape/Portrait orientation status */
#define MMA_PL_CFG				0x11 	/* Landscape/Portrait configuration. */
#define MMA_PL_COUNT			0x12 	/* Landscape/Portrait debounce counter */
#define MMA_PL_BF_ZCOMP			0x13 	/* Back-Front, Z-Lock Trip threshold */
#define MMA_PL_THS_REG			0x14	/* Portrait to Landscape Trip Angle is 29 */
#define MMA_FF_MT_CFG			0x15 	/* Freefall/Motion functional block configuration */
#define MMA_FF_MT_SRC			0x16 	/* Freefall/Motion event source register */
#define MMA_FF_MT_THS			0x17 	/* Freefall/Motion threshold register */
#define MMA_FF_MT_COUNT			0x18 	/* Freefall/Motion debounce counter */
#define MMA_TRANSIENT_CFG		0x1D 	/* Transient functional block configuration */
#define MMA_TRANSIENT_SRC		0x1E 	/* Transient event status register */
#define MMA_TRANSIENT_THS		0x1F 	/* Transient event threshold */
#define MMA_TRANSIENT_COUNT		0x20 	/* Transient debounce counter */
#define MMA_PULSE_CFG			0x21 	/* ELE, Double_XYZ or Single_XYZ */
#define MMA_PULSE_SRC			0x22 	/* EA, Double_XYZ or Single_XYZ */
#define MMA_PULSE_THSX			0x23 	/* X pulse threshold */
#define MMA_PULSE_THSY			0x24 	/* Y pulse threshold */
#define MMA_PULSE_THSZ			0x25 	/* Z pulse threshold */
#define MMA_PULSE_TMLT			0x26 	/* Time limit for pulse */
#define MMA_PULSE_LTCY			0x27 	/* Latency time for 2nd pulse */
#define MMA_PULSE_WIND			0x28 	/* Window time for 2nd pulse */
#define MMA_ASLP_COUNT			0x29 	/* Counter setting for Auto-SLEEP */
#define MMA_CTRL_REG1			0x2A 	/* ODR = 800 Hz, STANDBY Mode. */
#define MMA_CTRL_REG2			0x2B  	/* Sleep Enable, OS Modes, RST, ST */
#define MMA_CTRL_REG3			0x2C 	/* Wake from Sleep, IPOL, PP_OD */
#define MMA_CTRL_REG4			0x2D 	/* Interrupt enable register */
#define MMA_CTRL_REG5			0x2E  	/* Interrupt pin (INT1/INT2) map */
#define MMA_OFF_X				0x2F 	/* X-axis offset adjust */
#define MMA_OFF_Y				0x30 	/* Y-axis offset adjust */
#define MMA_OFF_Z				0x31 	/* Z-axis offset adjust */

/* Register MASK */
/* XYZ_DATA_CFG Register MASK */
#define MMA_XYZDATACFG_FS_MASK			0x03u
#define MMA_XYZDATACFG_FS_SHIFT			0
#define MMA_XYZDATACFG_FS(x)			(((uint8_t)(((uint8_t)(x))<<MMA_XYZDATACFG_FS_SHIFT))&MMA_XYZDATACFG_FS_MASK)
#define MMA_XYZDATACFG_HPFOUT_MASK		0x10u
#define MMA_XYZDATACFG_HPFOUT_SHIFT		4

/* HP_FILTER_CUTOFF Register MASK */
#define MMA_HPFILTERCUTOFF_SEL_MASK		0x30u
#define MMA_HPFILTERCUTOFF_SEL_SHIFT	0
#define MMA_HPFILTERCUTOFF_SEL(x)		(((uint8_t)(((uint8_t)(x))<<MMA_HPFILTERCUTOFF_SEL_SHIFT))&MMA_HPFILTERCUTOFF_SEL_MASK)
#define MMA_HPFILTERCUTOFF_LPFEN_MASK	0x10u
#define MMA_HPFILTERCUTOFF_LPFEN_SHIFT	4
#define MMA_HPFILTERCUTOFF_HPFBYP_MASK	0x20u
#define MMA_HPFILTERCUTOFF_HPFBYP_SHIFT	5

/* PL_CFG Register MASK */
#define MMA_PLCOUNT_BAFRO_MASK			0x01u
#define MMA_PLCOUNT_BAFRO_SHIFT			0
#define MMA_PLCOUNT_LAPO_MASK			0x06u
#define MMA_PLCOUNT_LAPO_SIHFT			1
#define MMA_PLCOUNT_LAPO(x)				(((uint8_t)(((uint8_t)(x))<<MMA_PLCOUNT_LAPO_SIHFT))&MMA_PLCOUNT_LAPO_MASK)
#define MMA_PLCOUNT_LO_MASK				0x40u
#define MMA_PLCOUNT_LO_SHIFT			6
#define MMA_PLCOUNT_NEWLP_MASK			0x80u
#define MMA_PLCOUNT_NEWLP_SHIFT			7

/* PL_BF_ZCOMP Register MASK */
#define MMA_PLBFZCOMP_ZLOCK_MASK		0x07u
#define MMA_PLBFZCOMP_ZLOCK_SHIFT		0
#define MMA_PLBFZCOMP_ZLOCK(x)			(((uint8_t)(((uint8_t)(x))<<MMA_PLBFZCOMP_ZLOCK_SHIFT))&MMA_PLBFZCOMP_ZLOCK_MASK)
#define MMA_PLBFZCOMP_BKFR_MASK			0xc0u
#define MMA_PLBFZCOMP_BKFR_SHIFT		6
#define MMA_PLBFZCOMP_BKFR(x)			(((uint8_t)(((uint8_t)(x))<<MMA_PLBFZCOMP_BKFR_SHIFT))&MMA_PLBFZCOMP_BKFR_MASK)

/* PL_THS_REG Register MASK */
#define MMA_PLTHSREG_HYS_MASK			0x07u
#define MMA_PLTHSREG_HYS_SHIFT			0
#define MMA_PLTHSREG_HYS(x)				(((uint8_t)(((uint8_t)(x))<<MMA_PLTHSREG_HYS_SHIFT))&MMA_PLTHSREG_HYS_MASK)
#define MMA_PLTHSREG_PLTHS_MASK			0xf1u
#define MMA_PLTHSREG_PLTHS_SHIFT		6
#define MMA_PLTHSREG_PLTHS(x)			(((uint8_t)(((uint8_t)(x))<<MMA_PLTHSREG_PLTHS_SHIFT))&MMA_PLTHSREG_PLTHS_MASK)

/* FF_MT_CFG Register MASK */
#define MMA_FFMTCFG_XEFE_MASK			0x08u
#define MMA_FFMTCFG_XEFE_SHIFT			3
#define MMA_FFMTCFG_YEFE_MASK			0x10u
#define MMA_FFMTCFG_YEFE_SHIFT			4
#define MMA_FFMTCFG_ZEFE_MASK			0x20u
#define MMA_FFMTCFG_ZEFE_SHIFT			5
#define MMA_FFMTCFG_OAE_MASK			0x40u
#define MMA_FFMTCFG_OAE_SHIFT			6
#define MMA_FFMTCFG_ELE_MASK			0x80u
#define MMA_FFMTCFG_ELE_SHIFT			7

/* FF_MT_THS Register MASK */

#define MMA_FFMTCFG_DBCNTM_MASK			0x80u
#define MMA_FFMTCFG_DBCNTM_SHIFT		7

/* TRANSIENT_CFG Register MASK */
#define MMA_TRANSIENTCFG_HPFBYP_MASK		0x01u
#define MMA_TRANSIENTCFG_HPFBYP_SHIFT		0
#define MMA_TRANSIENTCFG_XTEFE_MASK			0x02u
#define MMA_TRANSIENTCFG_XTEFE_SHIFT		1
#define MMA_TRANSIENTCFG_YTEFE_MASK			0x04u
#define MMA_TRANSIENTCFG_YTEFE_SHIFT		2
#define MMA_TRANSIENTCFG_ZTEFE_MASK			0x08u
#define MMA_TRANSIENTCFG_ZTEFE_SHIFT		3
#define MMA_TRANSIENTCFG_ELE_MASK			0x10u
#define MMA_TRANSIENTCFG_ELE_SHIFT			4

/* TRANSIENT_THS Register MASK */

#define MMA_TRANSIENTCFG_DBCNTM_MASK		0x80u
#define MMA_TRANSIENTCFG_DBCNTM_SHIFT		7

/* PULSE_CFG Register MASK */
#define MMA_PULSECFG_XSPEFE_MASK		0x01u
#define MMA_PULSECFG_XSPEFE_SHIFT		0
#define MMA_PULSECFG_XDPEFE_MASK		0x02u
#define MMA_PULSECFG_XDPEFE_SHIFT		1
#define MMA_PULSECFG_YSPEFE_MASK		0x04u
#define MMA_PULSECFG_YSPEFE_SHIFT		2
#define MMA_PULSECFG_YDPEFE_MASK		0x08u
#define MMA_PULSECFG_YDPEFE_SHIFT		3
#define MMA_PULSECFG_ZSPEFE_MASK		0x10u
#define MMA_PULSECFG_ZSPEFE_SHIFT		4
#define MMA_PULSECFG_ZDPEFE_MASK		0x20u
#define MMA_PULSECFG_ZDPEFE_SHIFT		5
#define MMA_PULSECFG_ELE_MASK			0x40u
#define MMA_PULSECFG_ELE_SHIFT			6
#define MMA_PULSECFG_DPA_MASK			0x80u
#define MMA_PULSECFG_DPA_SHIFT			7

/* PULSE_THSX Register MASK */
/* PULSE_THSY Register MASK */
/* PULSE_THSZ Register MASK */
/* PULSE_LTCY Register MASK */
/* PULSE_WIND Register MASK */

/* CTRL_REG1 Register MASK */
#define MMA_CTRLREG1_ACTIVE_MASK		0x01u
#define MMA_CTRLREG1_ACTIVE_SHIFT		0		
#define MMA_CTRLREG1_FREAD_MASK			0x02u
#define MMA_CTRLREG1_FREAD_SHIFT		1
#define MMA_CTRLREG1_LNOISE_MASK		0x04u
#define MMA_CTRLREG1_LNOISE_SHIFT		2
#define MMA_CTRLREG1_DR_MASK			0x38u
#define MMA_CTRLREG1_DR_SHIFT			3
#define MMA_CTRLREG1_DR(x)				(((uint8_t)(((uint8_t)(x))<<MMA_CTRLREG1_DR_SHIFT))&MMA_CTRLREG1_DR_MASK)
#define MMA_CTRLREG1_ASLPRATE_MASK		0xc0u
#define MMA_CTRLREG1_ASLPRATE_SHIFT		6
#define MMA_CTRLREG1_ASLPRATE(x)		(((uint8_t)(((uint8_t)(x))<<MMA_CTRL_REG1_ASLPRATE_SHIFT))&MMA_CTRLREG1_ASLPRATE_MASK)

/* CTRL_REG2 Register MASK */
#define MMA_CTRLREG2_MODS_MASK			0x03u
#define MMA_CTRLREG2_MODS_SHIFT			0
#define MMA_CTRLREG2_MODS(x)			(((uint8_t)(((uint8_t)(x))<<MMA_CTRLREG2_MODE_SHIFT))&MMA_CTRLREG2_MODE_MASK)
#define MMA_CTRLREG2_SLPE_MASK			0x04u
#define MMA_CTRLREG2_SLPE_SHIFT			2
#define MMA_CTRLREG2_SMODS_MASK			0x18u
#define MMA_CTRLREG2_SMODS_SHIFT		2
#define MMA_CTRLREG2_SMODS(x)			(((uint8_t)(((uint8_t)(x))<<MMA_CTRLREG2_SMODS_SHIFT))&MMA_CTRLREG2_SMODS_MASK)
#define MMA_CTRLREG2_RST_MASK			0x40u
#define MMA_CTRLREG2_RST_SHIFT			6
#define MMA_CTRLREG2_ST_MASK			0x80u
#define MMA_CTRLREG2_ST_SHIFT			7

/* CTRL_REG3 Register MASK */
#define MMA_CTRLREG3_PPOD_MASK			0x01u
#define MMA_CTRLREG3_PPOD_SHIFT			0
#define MMA_CTRLREG3_IPOL_MASK			0x02u
#define MMA_CTRLREG3_IPOL_SHIFT			1
#define MMA_CTRLREG3_WAKEFFMT_MASK		0x08u
#define MMA_CTRLREG3_WAKEFFMT_SHIFT		3
#define MMA_CTRLREG3_WAKEPULSE_MASK		0x10u
#define MMA_CTRLREG3_WAKEPULSE_SHIFT	4
#define MMA_CTRLREG3_WAKELNDPRT_MASK	0x20u
#define MMA_CTRLREG3_WAKELNFPRT_SHIFT	5
#define MMA_CTRLREG3_WAKETRANS_MASK		0x40u
#define MMA_CTRLREG3_WAKETRANS_SHIFT	6

/* CTRL_REG4 Register MASK */
#define MMA_CTRLREG4_INTENDRDY_MASK		0x01u
#define MMA_CTRLREG4_INTENDRDY_SHIFT	0
#define MMA_CTRLREG4_INTENFFMT_MASK		0x04u
#define MMA_CTRLREG4_INTENFFMT_SHIFT	2
#define MMA_CTRLREG4_INTENPULSE_MASK	0x08u
#define MMA_CTRLREG4_INTENPULSE_SHIFT	3
#define MMA_CTRLREG4_INTENLNDPRT_MASK	0x10u
#define MMA_CTRLREG4_INTENLNDPRT_SHIFT	4
#define MMA_CTRLREG4_INTENTRANS_MASK	0x20u
#define MMA_CTRLREG4_INTENTRANS_SHIFT	5
#define MMA_CTRLREG4_INTENASLP_MASK		0x80u
#define MMA_CTRLREG4_INTENASLP_SHIFT	7

/* CTRL_REG5 Register MASK */
#define MMA_CTRLREG5_INTCFGDRDY_MASK	0x01u
#define MMA_CTRLREG5_INTCFGDRDY_SHIFT	0
#define MMA_CTRLREG5_INTCFGFFMT_MASK	0x04u
#define MMA_CTRLREG5_INTCFGFFMT_SHIFT	2
#define MMA_CTRLREG5_INTCFGPULSE_MASK	0x08u
#define MMA_CTRLREG5_INTCFGPULSE_SHIFT	3
#define MMA_CTRLREG5_INTCFGLNDPRT_MASK	0x10u
#define MMA_CTRLREG5_INTCFGLNDPRT_SHIFT	4
#define MMA_CTRLREG5_INTCFGTRANS_MASK	0x20u
#define MMA_CTRLREG5_INTCFGTRANS_SHIFT	5
#define MMA_CTRLREG5_INTCFGASLP_MASK	0x80u
#define MMA_CTRLREG5_INTCFGASLP_SHIFT	7

/* Gyroscope(MMA8452Q) slave address */
#define MMA_ADDR 		0x1c
#define MMA_Fail 		0xff
#define MMA_Succ 		0

/* Gyroscope(MMA8452Q) mode(normal or fast) */
typedef enum{
	MMA_12bit_Mode=0,
	MMA_8bit_Mode=1
} MMA_Mode;
extern MMA_Mode MMA_Mode_Val;

/* Gyroscope(MMA8452Q) sensi(2g, 4g, 8g) */
typedef enum{
	MMA_Sensi_2g=0,
	MMA_Sensi_4g=1,
	MMA_Sensi_8g=2
} MMA_Sensi;
extern MMA_Sensi MMA_Sensi_Val;

/*
* brief : 	Initialize accelerometer(MMA8452Q) module
* param : 	
* return:	Statuss: MMA_Fail or MMA_Succ
* note	:	
*/
uint_8 acceInit(MMA_Mode mode, MMA_Sensi sens);

/*
* brief : 	Read or write byte data from accelerometer(MMA8452Q)
* param : 	addr		Module slave address
*			subaddr		Register address of the module
* return:	Statuss: MMA_Fail or MMA_Succ
* note	:	
*/
//uint_8 gyro_readbyte(uint_8 addr, uint_8 subaddr);
uint_8 acceReadByte(uint_8 addr, uint_8 subaddr, uint_8* ret);
uint_8 acceWriteByte(uint_8 addr, uint_8 subaddr, uint_8 data);

/*
* brief : 	Read or write some datas from accelerometer(MMA8452Q)
* param : 	addr		Module slave address
*			subaddr		Register address of the module
*			len			Data length
*			ret			Return values
*			data		Data for writing
* return:	Statuss: MMA_Fail or MMA_Succ
* note	:	
*/
uint_8 acceReadL(uint_8 addr, uint_8 subaddr, uint_8 len, uint_8* ret);
uint_8 acceWriteL(uint_8 addr, uint_8 subaddr, uint_8 len, uint_8* data);
	
/*
* brief : 	Caculate the raw data to exact value
* param : 	input		Raw data array
*			output		Solved data array
* return:	None
* note	:	
*/
void acceSolveData(MMA_Mode mode, uint_8* input, int_16* output);


#ifdef  __cplusplus
}
#endif

#endif 		//GYRO_H_
