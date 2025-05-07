# 编译器与工具
CC := gcc
RM := del /Q
EXE_EXT := .exe  # Windows 下生成 SolomonC.exe

# 编译选项
CFLAGS := -Wall -g

# 工程目标
TARGET := lab2bin$(EXE_EXT)

# 源文件与目标文件自动推导
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

# 默认目标
all: $(TARGET) 

# 链接
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# 编译规则（带依赖文件生成）
%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# 清理构建产物
clean:
	$(RM) *.o *.d

# 包含自动生成的依赖文件（确保不存在时报错不影响）
-include $(DEPS)

# 伪目标声明
.PHONY: all clean
