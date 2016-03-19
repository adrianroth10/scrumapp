SOURCE_PATH = ../src/
INCLUDE_PATH = ../include/
TEST_PATH = ../tests/
VPATH = $(SOURCE_PATH) $(INCLUDE_PATH) $(TEST_PATH)

CXXFLAGS = -pedantic -Wall -Werror -g -funsigned-char -I../include/
OFLAGS = -g

OBJS = reader.o
TEST_OBJS := $(addsuffix ut, $(OBJS))
TEST_OBJS := $(addprefix test_, $(TEST_OBJS))

.PHONY: all clean test

all: main.out

main.out: $(OBJS) main.o
	$(CXX) $(OFLAGS) -o $@ $^

clean:
	rm -f *.o *.out


test: $(TEST_OBJS)
	$(foreach X, $(TEST_OBJS), ./$X)

test_%.out: test_%.o %.o
	$(CXX) $(OFLAGS) -o $@ $^
