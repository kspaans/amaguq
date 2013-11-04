CXX=clang++
CXXFLAGS=-O -MMD


GTEST_DIR = /usr/src/gtest
USER_DIR = .
CPPFLAGS += -I$(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra
GTEST_HEADERS = /usr/include/gtest/*.h \
                /usr/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
TESTS = Tests

EXEC=Amaguq
OBJS=main.o amaguq.o
DEPS=${OBJS:.o=.d}

${EXEC}: ${OBJS}
	${CXX} ${OBJS} -o ${EXEC}
clean:
	rm -vf ${EXEC} ${OBJS} ${DEPS}

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

tests.o : $(USER_DIR)/tests.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/tests.cpp

tests : tests.o amaguq.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
################################################################################

-include ${DEPS}
