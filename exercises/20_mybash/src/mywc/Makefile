# src/mywc/Makefile

CC = gcc
CFLAGS = -Wall -I../../include

# 库名称
LIBNAME := mywc
# 静态库输出名：libmywc.a
LIB := lib$(LIBNAME).a
# 最终库输出目录
OBJDIR ?= ./obj
# 最终 .a 文件路径 (在父目录的 obj 中)
LIB_PATH := ../../obj/$(LIB)

# 源文件
SRCS := mywc.c
OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst %,../../obj/%,$(OBJS))

all: $(LIB_PATH)

../../obj:
	mkdir -p ../../obj

../../obj/%.o: %.c | ../../obj
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB_PATH): $(OBJS)
	ar rcs $@ $^

clean:
	rm -rf $(OBJDIR)/*.o $(LIB_PATH)
