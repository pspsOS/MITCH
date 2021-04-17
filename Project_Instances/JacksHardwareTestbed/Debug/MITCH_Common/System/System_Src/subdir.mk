################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MITCH_Common/System/System_Src/Nucleo_Profiles.c \
../MITCH_Common/System/System_Src/interface_structs.c \
../MITCH_Common/System/System_Src/retarget.c \
../MITCH_Common/System/System_Src/system_functions.c 

OBJS += \
./MITCH_Common/System/System_Src/Nucleo_Profiles.o \
./MITCH_Common/System/System_Src/interface_structs.o \
./MITCH_Common/System/System_Src/retarget.o \
./MITCH_Common/System/System_Src/system_functions.o 

C_DEPS += \
./MITCH_Common/System/System_Src/Nucleo_Profiles.d \
./MITCH_Common/System/System_Src/interface_structs.d \
./MITCH_Common/System/System_Src/retarget.d \
./MITCH_Common/System/System_Src/system_functions.d 


# Each subdirectory must supply rules for building sources it contributes
MITCH_Common/System/System_Src/Nucleo_Profiles.o: ../MITCH_Common/System/System_Src/Nucleo_Profiles.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Software/Acquisition/Acquisition_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/System/System_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/MITCH_2021-0/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MITCH_Common/System/System_Src/Nucleo_Profiles.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MITCH_Common/System/System_Src/interface_structs.o: ../MITCH_Common/System/System_Src/interface_structs.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Software/Acquisition/Acquisition_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/System/System_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/MITCH_2021-0/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MITCH_Common/System/System_Src/interface_structs.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MITCH_Common/System/System_Src/retarget.o: ../MITCH_Common/System/System_Src/retarget.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Software/Acquisition/Acquisition_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/System/System_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/MITCH_2021-0/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MITCH_Common/System/System_Src/retarget.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
MITCH_Common/System/System_Src/system_functions.o: ../MITCH_Common/System/System_Src/system_functions.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/Software/Acquisition/Acquisition_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/JacksHardwareTestbed/MITCH_Common/System/System_Inc" -I"C:/Users/Jeff/Documents/GitHub/MITCH/Project_Instances/MITCH_2021-0/MITCH_Common/Hardware_Interfaces/Hardware_Interfaces_Inc" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MITCH_Common/System/System_Src/system_functions.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

