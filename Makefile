BUILD = build
TEST_PROG = $(BUILD)/cppgraph_test
PLAY_PROG = $(BUILD)/cppgraph

CXXFLAGS = -std=c++11 -Wall -Werror -g -DMEMTRACE

SRCS = $(wildcard src/*.h) $(wildcard test/*.h) $(wildcard lib/*.h)

all: $(TEST_PROG) $(PLAY_PROG)

$(BUILD):
	mkdir -p $(BUILD)

# Test binary
$(TEST_PROG): $(BUILD)/test_main.o $(BUILD)/memtrace.o
	$(CXX) -o $@ $^

$(BUILD)/test_main.o: test/main.cpp $(SRCS) | $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Playground binary
$(PLAY_PROG): $(BUILD)/playground_main.o $(BUILD)/playground.o $(BUILD)/memtrace.o
	$(CXX) -o $@ $^

$(BUILD)/playground_main.o: src/main.cpp src/playground.h $(SRCS) | $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/playground.o: src/playground.cpp src/playground.h $(SRCS) | $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Shared
$(BUILD)/memtrace.o: lib/memtrace.cpp lib/memtrace.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(TEST_PROG)
	./$(TEST_PROG)

play: $(PLAY_PROG)
	./$(PLAY_PROG)

clean:
	rm -rf $(BUILD)
