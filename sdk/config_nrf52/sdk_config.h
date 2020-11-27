/*

Make sure to define all sdk_config.h differences before including sdk_config.h
This makes the process of upgrading to a new sdk_config.h much simpler. It
will also make it much easier to get an overview of what is changed from
the sdk_config.h defaults.

*/

// By intention, everything here is defined without #ifndef to make the compiler exit
// with an error if it's already defined.  Everything should be set here, not elsewhere!

//Includes a header file for the used featureset
//This allows us to enable certain modules in the featureset directly
#ifdef FEATURESET_NAME
#include FEATURESET_NAME
#endif

#ifndef __SDK_CONFIG_H
#define __SDK_CONFIG_H

// BLE_DB_DISCOVERY_ENABLED  - ble_db_discovery - Database discovery module
#define BLE_DB_DISCOVERY_ENABLED 1

// GPIOTE_ENABLED - nrf_drv_gpiote - GPIOTE peripheral driver
#define GPIOTE_ENABLED 1

// SAADC_ENABLED - nrf_drv_saadc - SAADC peripheral driver
#define SAADC_ENABLED 1

// <o> SAADC_CONFIG_RESOLUTION  - Resolution 
// <0=> 8 bit 
// <1=> 10 bit 
// <2=> 12 bit 
// <3=> 14 bit 
#define SAADC_CONFIG_RESOLUTION 0

// SPI_ENABLED - nrf_drv_spi - SPI/SPIM peripheral driver
#define SPI_ENABLED 1

// SPI_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority
// Priorities 0,2 (nRF51) and 0,1,4,5 (nRF52) are reserved for SoftDevice
// <0=> 0 (highest) 
// <1=> 1 
// <2=> 2 
// <3=> 3 
// <4=> 4 
// <5=> 5 
// <6=> 6 
// <7=> 7 
#define SPI_DEFAULT_CONFIG_IRQ_PRIORITY 6

// SPI0_ENABLED - Enable SPI0 instance
#define SPI0_ENABLED 1

// SPI0_USE_EASY_DMA  - Use EasyDMA
#define SPI0_USE_EASY_DMA 0

/* LAB5E
// TWI_ENABLED - nrf_drv_twi - TWI/TWIM peripheral driver
#define TWI_ENABLED 1
*/

// TWI_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority
// <i> Priorities 0,2 (nRF51) and 0,1,4,5 (nRF52) are reserved for SoftDevice
// <0=> 0 (highest) 
// <1=> 1 
// <2=> 2 
// <3=> 3 
// <4=> 4 
// <5=> 5 
// <6=> 6 
// <7=> 7 
#define TWI_DEFAULT_CONFIG_IRQ_PRIORITY 6

/* LAB5E
// TWI1_ENABLED - Enable TWI1 instance
#define TWI1_ENABLED 1
*/

// USBD_CONFIG_IRQ_PRIORITY  - Interrupt priority
// <i> Priorities 0,2 (nRF51) and 0,1,4,5 (nRF52) are reserved for SoftDevice
// <0=> 0 (highest) 
// <1=> 1 
// <2=> 2 
// <3=> 3 
// <4=> 4 
// <5=> 5 
// <6=> 6 
// <7=> 7 
#define USBD_CONFIG_IRQ_PRIORITY 6

// APP_TIMER_ENABLED - app_timer - Application timer functionality
#define APP_TIMER_ENABLED 1


// HARDFAULT_HANDLER_ENABLED - hardfault_default - HardFault default handler for debugging and release
#define HARDFAULT_HANDLER_ENABLED 1

// NRF_SECTION_ITER_ENABLED  - nrf_section_iter - Section iterator
#define NRF_SECTION_ITER_ENABLED 1

// NRF_SDH_BLE_ENABLED - nrf_sdh_ble - SoftDevice BLE event handler
#define NRF_SDH_BLE_ENABLED 1

// NRF_SDH_BLE_PERIPHERAL_LINK_COUNT - Maximum number of peripheral links. 
#define NRF_SDH_BLE_PERIPHERAL_LINK_COUNT 1

// NRF_SDH_BLE_CENTRAL_LINK_COUNT - Maximum number of central links. 
#define NRF_SDH_BLE_CENTRAL_LINK_COUNT 3

// NRF_SDH_BLE_GATT_MAX_MTU_SIZE - Static maximum MTU size. 
#define NRF_SDH_BLE_GATT_MAX_MTU_SIZE 63

// NRF_SDH_BLE_VS_UUID_COUNT - The number of vendor-specific UUIDs. (0 is default)
#define NRF_SDH_BLE_VS_UUID_COUNT 10

// NRF_SDH_BLE_SERVICE_CHANGED  - Include the Service Changed characteristic in the Attribute Table.
#define NRF_SDH_BLE_SERVICE_CHANGED 1

// NRF_SDH_ENABLED - nrf_sdh - SoftDevice handler
#define NRF_SDH_ENABLED 1


// These settings are given through the Boardconfig
// This was defined as *** to throw a warning once this is used somewhere
//==========================================================
// <o> NRF_SDH_CLOCK_LF_SRC  - SoftDevice clock source.
// <0=> NRF_CLOCK_LF_SRC_RC 
// <1=> NRF_CLOCK_LF_SRC_XTAL 
// <2=> NRF_CLOCK_LF_SRC_SYNTH 
#ifndef NRF_SDH_CLOCK_LF_SRC
#define NRF_SDH_CLOCK_LF_SRC ***
#endif

// <o> NRF_SDH_CLOCK_LF_RC_CTIV - SoftDevice calibration timer interval. 
#ifndef NRF_SDH_CLOCK_LF_RC_CTIV
#define NRF_SDH_CLOCK_LF_RC_CTIV ***
#endif

// <o> NRF_SDH_CLOCK_LF_RC_TEMP_CTIV - SoftDevice calibration timer interval under constant temperature. 
// <i> How often (in number of calibration intervals) the RC oscillator shall be calibrated
// <i>  if the temperature has not changed.
#ifndef NRF_SDH_CLOCK_LF_RC_TEMP_CTIV
#define NRF_SDH_CLOCK_LF_RC_TEMP_CTIV ***
#endif

// <o> NRF_SDH_CLOCK_LF_XTAL_ACCURACY  - External crystal clock accuracy used in the LL to compute timing windows.
 // <0=> NRF_CLOCK_LF_XTAL_ACCURACY_250_PPM 
// <1=> NRF_CLOCK_LF_XTAL_ACCURACY_500_PPM 
// <2=> NRF_CLOCK_LF_XTAL_ACCURACY_150_PPM 
// <3=> NRF_CLOCK_LF_XTAL_ACCURACY_100_PPM 
// <4=> NRF_CLOCK_LF_XTAL_ACCURACY_75_PPM 
// <5=> NRF_CLOCK_LF_XTAL_ACCURACY_50_PPM 
// <6=> NRF_CLOCK_LF_XTAL_ACCURACY_30_PPM 
// <7=> NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM 
#ifndef NRF_SDH_CLOCK_LF_XTAL_ACCURACY
#define NRF_SDH_CLOCK_LF_XTAL_ACCURACY ***
#endif
//==========================================================


// NRF_SDH_SOC_ENABLED - nrf_sdh_soc - SoftDevice SoC event handler
#define NRF_SDH_SOC_ENABLED 1

#include "original_sdk14_config.h"

#endif // __SDK_CONFIG_H