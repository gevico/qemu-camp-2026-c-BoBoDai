# src/myfile/Makefile

CC = gcc
CFLAGS = -Wall -I../../include -g

# 库名称
LIBNAME := myfile
# 静态库输出名：libmyfile.a
LIB := lib$(LIBNAME).a
# 最终库输出目录
OBJDIR ?= ./obj
# 最终 .a 文件路径 (在父目录的 obj 中)
LIB_PATH := ../../obj/$(LIB)

# 源文件
SRCS := myfile.c
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
