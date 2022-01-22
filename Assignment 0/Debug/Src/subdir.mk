################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/BaseApplication.cpp \
../Src/TutorialApplication.cpp 

CPP_DEPS += \
./Src/BaseApplication.d \
./Src/TutorialApplication.d 

OBJS += \
./Src/BaseApplication.o \
./Src/TutorialApplication.o 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.cpp Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/student/eclipse-workspace/Assignment 0/Inc" -I/usr/local/include/OGRE -I/usr/local/include/OGRE/Overlay -I/usr/include/ois -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Src

clean-Src:
	-$(RM) ./Src/BaseApplication.d ./Src/BaseApplication.o ./Src/TutorialApplication.d ./Src/TutorialApplication.o

.PHONY: clean-Src

