# 指定编译器
CC = g++

# 编译选项
CFLAGS = -Wall -std=c++11 -O2

# 目标可执行文件名
TARGET = test

# 源文件
SRCS = test.cpp

# 对象文件
OBJS = $(SRCS:.cpp=.o)

# LaTeX相关命令
LATEX = xelatex
REPORT_SRC = report.tex
REPORT_TARGET = report.pdf

# 默认目标：构建可执行文件
all: $(TARGET)

# 生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 从 .cpp 文件生成 .o 文件
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET) $(REPORT_TARGET) *.aux *.log

# 生成报告
report: $(REPORT_SRC)
	$(LATEX) $(REPORT_SRC)
	$(LATEX) $(REPORT_SRC)  # 第二次运行以确保所有引用和目录正确
	mv $(REPORT_SRC:.tex=.pdf) $(REPORT_TARGET)
