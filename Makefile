BUILD = build
PROG = $(BUILD)/cppgraph
OBJ = $(BUILD)/array_test.o $(BUILD)/memtrace.o

CXXFLAGS = -std=c++11 -Wall -Werror -g -DMEMTRACE

all: $(PROG)

$(BUILD):
	mkdir -p $(BUILD)

$(PROG): $(OBJ)
	$(CXX) -o $(PROG) $(OBJ)

$(BUILD)/array_test.o: test/array_test.cpp src/array.h lib/gtest_lite.h lib/memtrace.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/memtrace.o: lib/memtrace.cpp lib/memtrace.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(PROG)
	./$(PROG)

clean:
	rm -rf $(BUILD)
