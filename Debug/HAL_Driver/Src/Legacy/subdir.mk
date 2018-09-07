################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL_Driver/Src/Legacy/stm32f4xx_hal_can.c 

OBJS += \
./HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o 

C_DEPS += \
./HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
HAL_Driver/Src/Legacy/%.o: ../HAL_Driver/Src/Legacy/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407G_DISC1 -DDEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DINCLUDE_FATFS -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STemWin/Config" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/s25fl512s" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/cs43l22" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/ili9341" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/ampire480272" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/s5k5cag" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/mfxstm32l152" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/CMSIS/device" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/st7735" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STemWin/inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/otm8009a" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/stmpe1600" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/Common" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/FatFs/src" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/src/apps/httpd" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/l3gd20" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/test/fuzz" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LibJPEG/include" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/src/include/lwip" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/HAL_Driver/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/system/arch" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Host_Library/Class/Template/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/test/unit/udp" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/test/unit/mdns" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/stmpe811" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/lis3dsh" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/test/unit/core" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/n25q256a" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/ls016b8uy" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/STM32F4-Discovery" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/exc7200" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/src/include/netif/ppp/polarssl" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/src/include/netif" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/ampire640480" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/FatFs/src/drivers" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/CMSIS/core" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/src/include/posix" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/ili9325" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/test/unit/tcp" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/n25q512a" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/src/apps/snmp" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/ts3510" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/n25q128a" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/test/unit/ip4" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/HAL_Driver/Inc/Legacy" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/lis302dl" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/test/unit/etharp" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/test/unit" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/ov2640" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Device_Library/Class/Template/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/wm8994" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/ft6x06" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/doc/doxygen" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/st7789h2" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Utilities/Components/lsm303dlhc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/Third_Party/LwIP/test/unit/dhcp" -I"/Users/QianliMa-MAC/Documents/Purdue/2018 Fall/ECE477/GCB/Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

