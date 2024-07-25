CXX := g++
CXXFLAGS += -g -O0 -std=c++17 -fPIC -shared

PATH_INSTALL_LIB_ROOT = /usr/lib
PATH_INSTALL_INC_ROOT = /usr/include

LIB_NAME = libthpool.so
HEADER_NAME = threadpool.h

# 生成共享库
$(LIB_NAME): threadpool.cpp $(HEADER_NAME)
	$(CXX) $(CXXFLAGS) threadpool.cpp -o $@ -lpthread

# 测试编译
test: test.cpp $(LIB_NAME)
	$(CXX) test.cpp -o test.o -lthpool -lpthread

# 安装规则
install: $(LIB_NAME)
	sudo cp $(HEADER_NAME) $(PATH_INSTALL_INC_ROOT)/
	sudo cp $(LIB_NAME) $(PATH_INSTALL_LIB_ROOT)/

# 卸载规则
uninstall:
	sudo rm -rf $(PATH_INSTALL_INC_ROOT)/$(HEADER_NAME) $(PATH_INSTALL_LIB_ROOT)/$(LIB_NAME)

# 清理规则
clean:
	rm -rf *.o $(LIB_NAME)
