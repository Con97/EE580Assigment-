################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs1271/ccs/tools/compiler/c6000_7.3.23/bin/cl6x" -mv6740 -O2 --define=c6748 --include_path="C:/Users/frank/OneDrive/Strathclyde/Strathclyde/Year5/EE580/S2/Assigment_1_FIR" --include_path="C:/ti/ccs1271/ccs/tools/compiler/c6000_7.3.23/include" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


