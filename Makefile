#	conan
third_party/conan: third_party/conanfile.txt
	mkdir -p $@
	cd $@ && conan install ..
	touch $@

#	antlr
sysy/antlr-4.12.0-complete.jar:
	cd sysy && curl -O https://www.antlr.org/download/antlr-4.12.0-complete.jar

sysy/include: sysy/SysY.g4 sysy/CommonLex.g4 sysy/antlr-4.12.0-complete.jar
	cd sysy && java -Xmx500M -cp "antlr-4.12.0-complete.jar:$CLASSPATH" org.antlr.v4.Tool -Dlanguage=Cpp -visitor -no-listener -package front SysY.g4 -o include
	touch $@

allForBuild = third_party/conan sysy/include

build/bin/asm-producer:	#	prerequisites are managed by cmake, so no prerequisite in makefile
	mkdir -p build
	cd build && cmake .. -G "Unix Makefiles" && make asm-producer
	# -DCMAKE_BUILD_TYPE=Release

.PHONY: all clean show run demo_run
.DEFAULT_GOAL := all
all: ${allForBuild}

clean:
	rm -rf ${allForBuild}

show:
	@echo ${allForBuild}

args ?= --help
run: build/bin/asm-producer
	@build/bin/asm-producer --help

include .demo/config.mk
demoSysyBase ?= demo

demo_run:
	mkdir -p build && cd build && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Build && make
	build/${dutBin} .demo/${demoSysyBase}.sysy -o .demo/${demoSysyBase}.S ${dutOptions}

demo_see_ast:
	antlr4-parse sysy/SysY.g4 sysy/CommonLex.g4 compUnit .demo/${demoSysyBase}.sysy -gui