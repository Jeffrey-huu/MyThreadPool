CXX := g++
CXXFLAGS += -g -O0 -std=c++11


# 测试编译
test: test.cpp $(LIB_NAME)
	$(CXX) test.cpp -o test.o -lpthread

# 清理规则
clean:
	rm -rf *.o
