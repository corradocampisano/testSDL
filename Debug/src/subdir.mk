################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Being.cpp \
../src/Constants.cpp \
../src/Simulation.cpp \
../src/TestCamera.cpp \
../src/main.cpp 

OBJS += \
./src/Being.o \
./src/Constants.o \
./src/Simulation.o \
./src/TestCamera.o \
./src/main.o 

CPP_DEPS += \
./src/Being.d \
./src/Constants.d \
./src/Simulation.d \
./src/TestCamera.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/SDL -I/usr/include/c++/4.8/ -I/usr/include/ -I/usr/include/GL -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


