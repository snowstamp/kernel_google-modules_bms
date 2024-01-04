/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright 2023 Google LLC
 */

#ifndef MAX77779_I2CM_H_
#define MAX77779_I2CM_H_
#include <linux/regmap.h>

#define DONEI_SET(v) (((v) << MAX77779_I2CM_INTERRUPT_DONEI_SHIFT) & \
		MAX77779_I2CM_INTERRUPT_DONEI_MASK)
#define DONEI_GET(v) (((v) & MAX77779_I2CM_INTERRUPT_DONEI_MASK) >> \
		MAX77779_I2CM_INTERRUPT_DONEI_SHIFT)
#define ERRI_SET(v) (((v) << MAX77779_I2CM_INTERRUPT_ERRI_SHIFT) & \
		MAX77779_I2CM_INTERRUPT_ERRI_MASK)
#define ERRI_GET(v) (((v) & MAX77779_I2CM_INTERRUPT_ERRI_MASK) >> \
		MAX77779_I2CM_INTERRUPT_ERRI_SHIFT)

#define DONEIM_SET(v) (((v) << MAX77779_I2CM_INTMASK_DONEIM_SHIFT) & \
		MAX77779_I2CM_INTMASK_DONEIM_MASK)
#define DONEIM_GET(v) (((v) & MAX77779_I2CM_INTMASK_DONEIM_MASK) >> \
		MAX77779_I2CM_INTMASK_DONEIM_SHIFT)
#define ERRIM_SET(v) (((v) << MAX77779_I2CM_INTMASK_ERRIM_SHIFT) & \
		MAX77779_I2CM_INTMASK_ERRIM_MASK)
#define ERRIM_GET(v) (((v) & MAX77779_I2CM_INTMASK_ERRIM_MASK) >> \
		MAX77779_I2CM_INTMASK_ERRIM_SHIFT)

#define ERROR_SET(v) (((v) << MAX77779_I2CM_STATUS_ERROR_SHIFT) & \
		MAX77779_I2CM_STATUS_ERROR_MASK)
#define ERROR_GET(v) (((v) & MAX77779_I2CM_STATUS_ERROR_MASK) >> \
		MAX77779_I2CM_STATUS_ERROR_SHIFT)

#define I2CEN_SET(v) (((v) << MAX77779_I2CM_CONTROL_I2CEN_SHIFT) & \
		MAX77779_I2CM_CONTROL_I2CEN_MASK)
#define I2CEN_GET(v) (((v) & MAX77779_I2CM_CONTROL_I2CEN_MASK) >> \
		MAX77779_I2CM_CONTROL_I2CEN_SHIFT)
#define CLOCK_SPEED_SET(v) (((v) << MAX77779_I2CM_CONTROL_CLOCK_SPEED_SHIFT) & \
		MAX77779_I2CM_CONTROL_CLOCK_SPEED_MASK)
#define CLOCK_SPEED_GET(v) (((v) & MAX77779_I2CM_CONTROL_CLOCK_SPEED_MASK) >> \
		MAX77779_I2CM_CONTROL_CLOCK_SPEED_SHIFT)

#define SID_SET(v) (((v) << MAX77779_I2CM_SLADD_SLAVE_ID_SHIFT) & \
		MAX77779_I2CM_SLADD_SLAVE_ID_MASK)
#define SID_GET(v) (((v) & MAX77779_I2CM_SLADD_SLAVE_ID_MASK) >> \
		MAX77779_I2CM_SLADD_SLAVE_ID_SHIFT)

#define TXCNT_SET(v) (((v) << MAX77779_I2CM_TXDATA_CNT_TXCNT_SHIFT) & \
		MAX77779_I2CM_TXDATA_CNT_TXCNT_MASK)
#define TXCNT_GET(v) (((v) & MAX77779_I2CM_TXDATA_CNT_TXCNT_MASK) >> \
		MAX77779_I2CM_TXDATA_CNT_TXCNT_SHIFT)

#define I2CMWRITE_SET(v) (((v) << MAX77779_I2CM_CMD_I2CMWRITE_SHIFT) & \
		MAX77779_I2CM_CMD_I2CMWRITE_MASK)
#define I2CMWRITE_GET(v) (((v) & MAX77779_I2CM_CMD_I2CMWRITE_MASK) >> \
		MAX77779_I2CM_CMD_I2CMWRITE_SHIFT)

#define I2CMREAD_SET(v) (((v) << MAX77779_I2CM_CMD_I2CMREAD_SHIFT) & \
		MAX77779_I2CM_CMD_I2CMREAD_MASK)
#define I2CMREAD_GET(v) (((v) & MAX77779_I2CM_CMD_I2CMREAD_MASK) >> \
		MAX77779_I2CM_CMD_I2CMREAD_SHIFT)

#define I2CM_ERR_ARBITRATION_LOSS(status_err)	(!!((status_err) & BIT(0)))
#define I2CM_ERR_TIMEOUT(status_err)		(!!((status_err) & BIT(1)))
#define I2CM_ERR_ADDRESS_NACK(status_err)	(!!((status_err) & BIT(2)))
#define I2CM_ERR_DATA_NACK(status_err)		(!!((status_err) & BIT(3)))
#define I2CM_ERR_RX_FIFO_NA(status_err)		(!!((status_err) & BIT(4)))
#define I2CM_ERR_START_OUT_SEQ(status_err)	(!!((status_err) & BIT(5)))
#define I2CM_ERR_STOP_OUT_SEQ(status_err)	(!!((status_err) & BIT(6)))

#define I2CM_MAX_REGISTER			MAX77779_I2CM_RX_BUFFER_31

#define MAX77779_TIMEOUT_DEFAULT		0xff
#define MAX77779_MAX_TIMEOUT			0xff
#define MAX77779_COMPLETION_TIMEOUT_MS_DEFAULT	20
#define MAX77779_MAX_SPEED			0x03
#define MAX77779_SPEED_DEFAULT			0x00

#define MAX77779_I2CM_MAX_WRITE \
		(MAX77779_I2CM_TX_BUFFER_33 - MAX77779_I2CM_TX_BUFFER_0 + 1)
#define MAX77779_I2CM_MAX_READ \
		(MAX77779_I2CM_RX_BUFFER_31 - MAX77779_I2CM_RX_BUFFER_0 + 1)

struct max77779_i2cm_info {
	struct i2c_adapter	adap;  /* bus */
	struct i2c_client	*client;
	int			irq;
	struct device		*dev;
	struct regmap		*regmap;
	struct completion	xfer_done;
	unsigned int		timeout;
	unsigned int		completion_timeout_ms;
	unsigned int		speed;
	u8			reg_vals[I2CM_MAX_REGISTER + 1];
};

int max77779_i2cm_init(struct max77779_i2cm_info *info);
void max77779_i2cm_remove(struct max77779_i2cm_info *info);

extern const struct regmap_config max77779_i2cm_regmap_cfg;
#endif
