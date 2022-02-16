################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Assignment2.cpp \
../src/BaseApplication.cpp \
../src/Entity381.cpp \
../src/EntityMgr.cpp 

CPP_DEPS += \
./src/Assignment2.d \
./src/BaseApplication.d \
./src/Entity381.d \
./src/EntityMgr.d 

OBJS += \
./src/Assignment2.o \
./src/BaseApplication.o \
./src/Entity381.o \
./src/EntityMgr.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/student/eclipse-workspace/Assignment-2/inc" -I/usr/local/include/OGRE -I/usr/local/include/OGRE/Overlay -I/usr/include/ois -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Assignment2.d ./src/Assignment2.o ./src/BaseApplication.d ./src/BaseApplication.o ./src/Entity381.d ./src/Entity381.o ./src/EntityMgr.d ./src/EntityMgr.o

.PHONY: clean-src

