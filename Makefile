# Makefile

# 可执行文件名
EXEC=apps
CC=gcc
# 编译选项
CFLAGS=-Wall -O -pthread

BASE_DIR=$(shell pwd)
INC_DIR=include
BIN_DIR=obj
LOG_DIR=log
BUILD_DIR=build

C_SOURCES=$(wildcard *.c)
C_OBJS=$(patsubst %.c, %.o, $(C_SOURCES))

C_BIN_OBJS=$(wildcard $(BASE_DIR)/$(BIN_DIR)/*.o)

SUBDIRS=$(shell ls -l|grep ^d | awk '{if($$9 != "obj" && $$9 != "include" && $$9!="build" && $$9 != "log") print $$9}')

export CC BASE_DIR INC_DIR BIN_DIR


build: start_build  
	@echo build done

start_build: check_dir $(SUBDIRS) $(C_OBJS) build_app
	@echo 

# 构建可执行文件
build_app:
	$(CC) $(CFLAGS) -o $(EXEC) $(wildcard $(BASE_DIR)/$(BIN_DIR)/*.o) 

# 编译当前目录所有的C文件
$(C_OBJS):%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $(BASE_DIR)/$(BIN_DIR)/$@ -I $(BASE_DIR)/$(INC_DIR) 

# 检查 BIN_DIR 目录是否存在
check_dir:
	mkdir -p $(BIN_DIR)
	mkdir -p $(LOG_DIR)
	mkdir -p $(BUILD_DIR) 

# 递归编译子目录
$(SUBDIRS):NOP 
	@echo begin compile $@
	make -C $@

NOP:
	

.PHONY:clean
clean:
	-rm -rf $(BASE_DIR)/$(BIN_DIR)
	-rm -rf $(EXEC)

echo:
	@echo $(C_BIN_OBJS)

