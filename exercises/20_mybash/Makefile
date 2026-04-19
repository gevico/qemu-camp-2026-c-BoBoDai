# =============================================
# 主 Makefile
# 功能：
#   - mybash：生成二进制，放到 bin/
#   - 其他模块（mysed, myfile, mywc, mytrans）：生成静态库 .a
# =============================================

CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -L./obj

# 所有子模块目录（静态库：生成 .a）
SUBDIRS = mysed myfile mywc mytrans

# 最终可执行文件
TARGET = bin/mybash

# 默认目标：构建 mybash（依赖其他库）
all: $(TARGET)

# 构建子模块
$(SUBDIRS):
	$(MAKE) -C src/$@

# 创建 bin 目录
bin:
	mkdir -p bin

# 创建 obj 目录
obj:
	mkdir -p obj

# 构建 mybash 可执行文件
$(TARGET): $(SUBDIRS) bin
	cd src/mybash && $(CC) $(CFLAGS) -I../../include -o ../../bin/mybash main.c \
		-L../../obj -lmyfile -lmysed -lmywc -lmytrans

# 清理所有生成的文件
clean:
	rm -rf bin obj
	cd src/mybash && rm -f ../../../bin/mybash
	for dir in $(SUBDIRS); do \
		$(MAKE) -C src/$$dir clean; \
	done

.PHONY: all $(SUBDIRS) clean bin obj
