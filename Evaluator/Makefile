# 指定编译器
CC = g++

# 编译选项
CFLAGS = -Wall -std=c++11
LDFLAGS =

# 目标可执行文件名
TARGET = expression_evaluator

# 源文件
SRCS = main.cpp expression_evaluator.cpp

# 对象文件
OBJS = main.o expression_evaluator.o

# LaTeX相关命令
LATEX = xelatex
REPORT_SRC = report.tex
REPORT_TARGET = report.pdf

# 默认目标：构建可执行文件和报告
all: $(TARGET) $(REPORT_TARGET)

# 生成可执行文件
$(TARGET): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 从 .cpp 文件生成 .o 文件
main.o: main.cpp expression_evaluator.h
		$(CC) $(CFLAGS) -c $<

expression_evaluator.o: expression_evaluator.cpp expression_evaluator.h
		$(CC) $(CFLAGS) -c $<

# 生成报告
$(REPORT_TARGET): $(REPORT_SRC)
		$(LATEX) $(REPORT_SRC)
		$(LATEX) $(REPORT_SRC)  # Run twice to resolve references
        # Uncomment the following line if necessary
        # mv $(REPORT_SRC:.tex=.pdf) $(REPORT_TARGET)

# 清理生成的文件
clean:
		rm -f *.o $(TARGET) $(REPORT_TARGET) *.aux *.log *.out

.PHONY: all clean