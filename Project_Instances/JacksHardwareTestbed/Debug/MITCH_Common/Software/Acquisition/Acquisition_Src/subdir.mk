################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MITCH_Common/Software/Acquisition/Acquisition_Src/bmp_acquisition.c \
../MITCH_Common/Software/Acquisition/Acquisition_Src/gps_acquistion.c 

OBJS += \
./MITCH_Common/Software/Acquisition/Acquisition_Src/bmp_acquisition.o \
./MITCH_Common/Software/Acquisition/Acquisition_Src/gps_acquistion.o 

C_DEPS += \
./MITCH_Common/Software/Acquisition/Acquisition_Src/bmp_acquisition.d \
./MITCH_Common/Software/Acquisition/Acquisition_Src/gps_acquistion.d 


# Each subdirectory must supply rules for building sources it contributes
MITCH_Common/Software/Acquisition/Acquisition_Src/bmp_acquisition.o: ../MITCH_Common/Software/Acquisition/Acquisition_Src/bmp_acquisition.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Software/Acquisition/Acquisition_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/System/System_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/MITCH_2021-0/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MITCH_Common/Software/Acquisition/Acquisition_Src/bmp_acquisition.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MITCH_Common/Software/Acquisition/Acquisition_Src/gps_acquistion.o: ../MITCH_Common/Software/Acquisition/Acquisition_Src/gps_acquistion.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Software/Acquisition/Acquisition_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/System/System_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/MITCH_2021-0/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MITCH_Common/Software/Acquisition/Acquisition_Src/gps_acquistion.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

