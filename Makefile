
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include

# Source files
SRC = $(shell find src -name '*.cpp')
COMMON_SRC = $(filter-out src/main.cpp, $(SRC))
HEADERS = $(wildcard include/*.h)

# Test files and executables
TEST_SRC = $(shell find tests -name '*.cpp')
TEST_BINS = $(patsubst tests/%.cpp, build/%, $(TEST_SRC))

# Compile the HTTP server
all: server

server: $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o server

# Compile each test
build/%: tests/%.cpp $(COMMON_SRC) $(HEADERS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< $(COMMON_SRC) -o $@

# Compile and run all tests
test: $(TEST_BINS)
	@if [ -z "$(TEST_BINS)" ]; then \
		echo "No test files found."; \
		exit 1; \
	fi
	@set -e; for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# Remove generated files
clean:
	rm -rf server build

.PHONY: all test clean
