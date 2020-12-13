# 编译选项
CFLAGS=-Wall -O -pthread -std=c99


C_SOURCES=$(wildcard *.c)
C_OBJS=$(patsubst %.c, %.o, $(C_SOURCES))

SUBDIRS=$(shell ls -l|grep ^d | awk '{if($$9 != "obj" && $$9 != "include" && $$9!="build") print $$9}')

build_module: $(SUBDIRS) $(C_OBJS)


$(C_OBJS):%.o:%.c
    $(CC) $(CFLAGS) -c $^ -o $(BASE_DIR)/$(BIN_DIR)/$@ -I $(BASE_DIR)/$(INC_DIR) 


$(SUBDIRS): NOP
    make -C $@

NOP:
    
