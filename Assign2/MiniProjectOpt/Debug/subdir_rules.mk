################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c6000_8.3.12/bin/cl6x" -mv6740 -g -O2 --define=c6748 --include_path="C:/ti/c6748/bsl/inc" --include_path="C:/Users/frank/OneDrive/Strathclyde/Strathclyde/Year5/EE580/S2/MiniProjectOpt" --include_path="C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c6000_8.3.12/include" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-86240367:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-86240367-inproc

build-86240367-inproc: ../hello.tcf
	@echo 'Building file: "$<"'
	@echo 'Invoking: TConf'
	"/xdctools/tconf" -b -Dconfig.importPath="/packages;" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

hellocfg.cmd: build-86240367 ../hello.tcf
hellocfg.s??: build-86240367
hellocfg_c.c: build-86240367
hellocfg.h: build-86240367
hellocfg.h??: build-86240367
hello.cdb: build-86240367

%.obj: ./%.s?? $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c6000_8.3.12/bin/cl6x" -mv6740 -g -O2 --define=c6748 --include_path="C:/ti/c6748/bsl/inc" --include_path="C:/Users/frank/OneDrive/Strathclyde/Strathclyde/Year5/EE580/S2/MiniProjectOpt" --include_path="C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c6000_8.3.12/include" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c6000_8.3.12/bin/cl6x" -mv6740 -g -O2 --define=c6748 --include_path="C:/ti/c6748/bsl/inc" --include_path="C:/Users/frank/OneDrive/Strathclyde/Strathclyde/Year5/EE580/S2/MiniProjectOpt" --include_path="C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-c6000_8.3.12/include" --display_error_number --diag_warning=225 --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


