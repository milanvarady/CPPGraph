BUILD = build
PROG = $(BUILD)/cppgraph

CXXFLAGS = -std=c++11 -Wall -Werror -g -DMEMTRACE

SRCS = $(wildcard src/*.h) $(wildcard test/*.h) $(wildcard lib/*.h)

all: $(PROG)

$(BUILD):
	mkdir -p $(BUILD)

$(PROG): $(BUILD)/main.o $(BUILD)/memtrace.o
	$(CXX) -o $@ $^

$(BUILD)/main.o: test/main.cpp $(SRCS) | $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/memtrace.o: lib/memtrace.cpp lib/memtrace.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(PROG)
	./$(PROG)

clean:
	rm -rf $(BUILD)
