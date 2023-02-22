GTEST=./googletest/googletest

OPENCV = -I /usr/local/include/opencv4
LIBS = -L $(shell ls /usr/local/lib/*libopencv*.so -1)

CPPFLAGS += -isystem $(GTEST)/include
CXXFLAGS += -std=c++17 -g -Wall -Wextra -pthread $(OPENCV)

SRC = $(shell find src -type f -name '*.cpp')
OBJ = $(subst .cpp,.o,$(SRC))

TEST = $(shell find test -type f -name '*.cpp')
TEST_OBJ = $(subst .cpp,.o,$(TEST))

.PHONY: all clean

all : setup-googletest gtest_main.a $(OBJ) $(TEST_OBJ) tests

setup-googletest:
	$(shell chmod +x setup-googletest.sh && ./setup-googletest.sh)

gtest-all.o : ${googletestSources}
	$(CXX) $(CPPFLAGS) -I$(GTEST) $(CXXFLAGS) -c $(GTEST)/src/gtest-all.cc
			
gtest_main.o : ${googletestSources}
	$(CXX) $(CPPFLAGS) -I$(GTEST) $(CXXFLAGS) -c $(GTEST)/src/gtest_main.cc

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

%: %.o
	$(CXX) $^ $(LDFLAGS) -o $@ $(LIBS)

tests: $(OBJ) $(TEST_OBJ) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(LIBS)

clean:
	find . -type f -name '*.o' -exec rm {} \;
	find . -type f -name '*.gch' -exec rm {} \;
	rm -f $(TESTS) tests gtest.a gtest_main.a core
	#rm -rf googletest
