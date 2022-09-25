CPPFLAGS += -isystem $(GTEST)/include
CXXFLAGS += -std=c++17 -g -Wall -Wextra -pthread

GTEST=./googletest-main/googletest

GTEST_HEADERS = $(shell find $(GTEST)/include -type f -name '*.h')
GTEST_SRCS = $(GTEST)/src/* $(GTEST_HEADERS)

TEST = $(shell find test -type f -name '*.cpp')
TEST_OBJ = $(subst .cpp,.o,$(TEST))

all : $(TEST_OBJ) tests

clean:
	find . -type f -name '*.o' -exec rm {} \;
	rm -f $(TESTS) tests gtest.a gtest_main.a

gtest-all.o : $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) -I$(GTEST) $(CXXFLAGS) -c $(GTEST)/src/gtest-all.cc
			
gtest_main.o : $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) -I$(GTEST) $(CXXFLAGS) -c $(GTEST)/src/gtest_main.cc

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

tests: $(TEST_OBJ) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
