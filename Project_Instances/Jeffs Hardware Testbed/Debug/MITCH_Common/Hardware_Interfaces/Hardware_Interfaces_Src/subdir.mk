################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/Adafruit_GPS.c \
../MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MS5607.c \
../MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MT3339.c \
../MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/generic_interface.c 

OBJS += \
./MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/Adafruit_GPS.o \
./MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MS5607.o \
./MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MT3339.o \
./MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/generic_interface.o 

C_DEPS += \
./MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/Adafruit_GPS.d \
./MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MS5607.d \
./MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MT3339.d \
./MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/generic_interface.d 


# Each subdirectory must supply rules for building sources it contributes
MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/Adafruit_GPS.o: ../MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/Adafruit_GPS.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/Software/Acquisition/Acquisition_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/System/System_Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/Adafruit_GPS.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MS5607.o: ../MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MS5607.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/Software/Acquisition/Acquisition_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/System/System_Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MS5607.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MT3339.o: ../MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MT3339.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/Software/Acquisition/Acquisition_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/System/System_Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/MT3339.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/generic_interface.o: ../MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/generic_interface.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/Software/Acquisition/Acquisition_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/Jeffs Hardware Testbed/MITCH_Common/System/System_Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Src/generic_interface.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

