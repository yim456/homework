# 指定编译器
CC = g++

# 编译选项
CFLAGS = -Wall -std=c++11
LDFLAGS =

# 目标可执行文件名
TARGET = ./test

# LaTeX 相关命令
LATEX = xelatex
REPORT_SRC = report.tex
REPORT_TARGET = report.pdf

# 默认目标：构建可执行文件和报告
all: $(TARGET) $(REPORT_TARGET)

# 生成可执行文件
$(TARGET): main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 从 .cpp 文件生成 .o 文件
main.o: main.cpp cuckoo.h
	$(CC) $(CFLAGS) -c $<

# 生成报告
$(REPORT_TARGET): $(REPORT_SRC)
	$(LATEX) $(REPORT_SRC)
	$(LATEX) $(REPORT_SRC)  # 第二次运行以解决引用问题

# 清理生成的文件
clean:
	rm -f *.o $(TARGET) $(REPORT_TARGET) *.aux *.log *.out *.toc

.PHONY: all clean
