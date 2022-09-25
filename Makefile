GTEST=./googletest/googletest

CPPFLAGS += -isystem $(GTEST)/include
CXXFLAGS += -std=c++17 -g -Wall -Wextra -pthread

TEST = $(shell find test -type f -name '*.cpp')
TEST_OBJ = $(subst .cpp,.o,$(TEST))

all : setup-googletest $(TEST_OBJ) tests

setup-googletest:
	$(shell chmod +x setup-googletest.sh && ./setup-googletest.sh)

gtest-all.o : ${googletestSources}
	$(CXX) $(CPPFLAGS) -I$(GTEST) $(CXXFLAGS) -c $(GTEST)/src/gtest-all.cc
			
gtest_main.o : ${googletestSources}
	$(CXX) $(CPPFLAGS) -I$(GTEST) $(CXXFLAGS) -c $(GTEST)/src/gtest_main.cc

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

tests: $(TEST_OBJ) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

clean:
	find . -type f -name '*.o' -exec rm {} \;
	rm -f $(TESTS) tests gtest.a gtest_main.a
	rm -rf googletest
