################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1271/ccs/tools/compiler/c6000_7.3.23

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"C:/ti/c6748/bsl/lib/evmc6748_bsl.lib" \
libc.a \

-include ../makefile.init

RM := 
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MiniProject.out

# Tool invocations
MiniProject.out: 
	@echo 'Building target: "$@"'
	@echo 'Invoking: C6000 Linker'
	0x800 0x800 MiniProject.out MiniProject.map MiniProject_linkInfo.xml /lib /include  "MiniProject.out"
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

