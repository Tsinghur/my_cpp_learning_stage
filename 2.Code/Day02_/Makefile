# 查找当前目录下所有 .cc 源文件
SRCS := $(wildcard *.cc)
# 生成对应的可执行文件名（去掉 .cc 后缀）
OUTS := $(patsubst %.cc,%,$(SRCS))

# 使用 g++ 编译器
CXX      := g++
# 编译选项：C++17标准、常见警告、调试信息
CXXFLAGS := -std=c++17 -Wall -g
# 链接选项（根据实际需要保留或修改）
LDFLAGS  :=
LIBS     := -lpthread -lmysqlclient

.PHONY: all clean rebuild

# 默认目标：编译所有独立的可执行文件
all: $(OUTS)

# 模式规则：将任意目标名匹配同名的 .cc 文件并编译
# 例如 make foo 会编译 foo.cc 生成可执行文件 foo
% : %.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LIBS)

# 清理所有生成的可执行文件
clean:
	$(RM) $(OUTS)

# 重新编译：先清理再编译
rebuild: clean all
