################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1126142177:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1126142177-inproc

build-1126142177-inproc: ../hello.tcf
	@echo 'Building file: "$<"'
	@echo 'Invoking: TConf'
	"/xdctools/tconf" -b -Dconfig.importPath="/packages;" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

hellocfg.cmd: build-1126142177 ../hello.tcf
hellocfg.s??: build-1126142177
hellocfg_c.c: build-1126142177
hellocfg.h: build-1126142177
hellocfg.h??: build-1126142177
hello.cdb: build-1126142177


