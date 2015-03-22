/*
 * Copyright (C) 2011
 * Stefano Babic, DENX Software Engineering, sbabic@denx.de.
 *
 * Copyright (C) 2009 TechNexion Ltd.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "tam3517-common.h"

#define MACH_TYPE_TAM3517	2818
#define CONFIG_MACH_TYPE	MACH_TYPE_TAM3517

#define CONFIG_TAM3517_SW3_SETTINGS
#define CONFIG_XR16L2751

#define CONFIG_BOOTDELAY	10

#define CONFIG_BOOTFILE		"uImage"

#define CONFIG_HOSTNAME		bpp3

/*
 * Since the console can also be used by external devices, the
 * U-boot autoboot will be prevented if any character is transmitted
 * during the bootdelay. This prevents for example the system recovery
 * from being properly executed. Hence the bootdelay is completely
 * disabled unless the left function keys is pressed. So only by pressing
 * the left button and the left function button the u-boot shell can now
 * be reached. The former to load u-boot at all, the latter to not start the
 * autoboot directly.
 */
#define CONFIG_PREBOOT					\
		"if gpio input 26; then " 		\
			"setenv bootdelay -1; " 	\
		"else "					\
			"setenv bootdelay 0; " 		\
		"fi"

#define CONFIG_OMAP3_GPIO_2

#define CONFIG_VIDEO
#ifdef CONFIG_VIDEO
# define CONFIG_VIDEO_OMAP3
# define CONFIG_CFB_CONSOLE
# define CONFIG_VRAM			(16 * 1024 * 1024)
# define CONFIG_FB_ADDR			(0x90000000 - CONFIG_VRAM)
# define CONFIG_VGA_AS_SINGLE_DEVICE

# define CONFIG_SPLASH_SCREEN
# define CONFIG_SPLASH_SCREEN_NAND_OFF	0x340000
# ifndef CONFIG_SPL_BUILD
#  define CONFIG_VIDEO_CONSOLE
#  define CONFIG_VIDEO_SW_CURSOR
# endif
# define CONFIG_VIDEO_BMP_RLE8
# define CONFIG_CMD_BMP
# define CONFIG_SYS_CONSOLE_IS_IN_ENV
#endif

#define CONFIG_CMD_BOOTZ

/* #define CONFIG_USB_KEYBOARD */
#ifdef CONFIG_USB_KEYBOARD
# define CONFIG_SYS_USB_EVENT_POLL
# define CONFIG_PREBOOT "usb start"
#endif

#ifdef MTDPARTS_DEFAULT
# undef MTDPARTS_DEFAULT
#endif
#define MTDPARTS_DEFAULT	"mtdparts=omap2-nand.0:512k(MLO),"\
		"1m(u-boot),256k(env1),256k(env2),1m(u-boot2),256k(bootparms),"\
		"768k(splash),6m(kernel),200m(data),-(rootfs)"

#define	CONFIG_EXTRA_ENV_SETTINGS \
	"mmcdev=0\0" \
	"loadbootscript=fatload mmc ${mmcdev} 80004000 boot.scr\0" \
	"bootcmd=" \
		"if mmc rescan ${mmcdev}; then " \
			"echo SD/MMC found on device ${mmcdev};" \
			"if run loadbootscript; then " \
				"echo Running bootscript from mmc ...;" \
				"source 80004000;" \
			"fi;" \
		"fi;" \
		"run nandboot;\0" \
		"loadaddr=80300000\0" \
		"nandboot=nand read ${loadaddr} kernel && bootm ${loadaddr}\0"

/* SPL OS boot options */
#define CONFIG_CMD_SPL
#define CONFIG_CMD_SPL_WRITE_SIZE	0x400 /* 1024 byte */
#define CONFIG_SYS_NAND_SPL_KERNEL_OFFS	0x00400000
#define CONFIG_CMD_SPL_NAND_OFS		0x00300000

#define CONFIG_SPL_OS_BOOT
#define CONFIG_SPL_OS_BOOT_KEY	29 /* left button */

#define CONFIG_SYS_SPL_ARGS_ADDR	(PHYS_SDRAM_1 + 0x100)
#define CONFIG_SPL_BOARD_INIT
#ifdef CONFIG_VIDEO
# define CONFIG_SPL_CFB_CONSOLE
# define CONFIG_SPL_VIDEO_SUPPORT
# define CONFIG_SPL_VIDEO_OMAP3
#endif

#define CONFIG_SPL_MMC_SUPPORT
#define CONFIG_SYS_MMC_SD_FAT_BOOT_PARTITION		1
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR	0x300 /* address 0x60000 */

/* FAT */
#define CONFIG_SPL_FAT_SUPPORT
#define CONFIG_SPL_FS_LOAD_KERNEL_NAME          "uImage.img"
#define CONFIG_SPL_FS_LOAD_ARGS_NAME            "args"
#define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME			"u-boot.img"

/* RAW SD card / eMMC */
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION	1
#define CONFIG_SYS_MMCSD_RAW_MODE_KERNEL_SECTOR 0x900   /* address 0x120000 */
#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTOR   0x80    /* address 0x10000 */
#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTORS  0x80    /* 64KiB */

#endif /* __CONFIG_H */
