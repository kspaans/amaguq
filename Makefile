CXX=clang++
CXXFLAGS=-O0 -MMD -std=c++11 #-fsanitize=address


GTEST_DIR = /usr/src/gtest
USER_DIR = .
CPPFLAGS += -I$(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra
GTEST_HEADERS = /usr/include/gtest/*.h \
                /usr/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
TESTS = Tests

EXEC=Amaguq
OBJS=amaguq.o heap.o atom.o fixnum.o boolean.o charlit.o strlit.o list.o \
		 symbol.o eval.o quote.o
DEPS=${OBJS:.o=.d}

all: ${EXEC} ${TESTS}

${EXEC}: main.o ${OBJS}
	${CXX} main.o ${OBJS} -o ${EXEC}
clean:
	rm -vf ${EXEC} ${OBJS} ${DEPS} ${TESTS} gtest_main.a gtest_main.o gtest-all.o tests.o

tests: ${TESTS}

################################################################################
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

tests.o : $(USER_DIR)/tests.cpp $(GTEST_HEADERS) amaguq.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/tests.cpp

Tests : tests.o ${OBJS} gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
################################################################################

-include ${DEPS}
