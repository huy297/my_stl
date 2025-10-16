CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

BUILD_DIR = build
TEST_DIR = test

file ?= test_mystring


SRC = test_mystring.cpp
OUT = test_mystring


run: 
	@src="$(TEST_DIR)/$(file).cpp"; \
	out="$(BUILD_DIR)/$(file).out"; \
	if [ -f $$src ]; then \
		echo "Compiling $$src..."; \
		mkdir -p $(BUILD_DIR); \
		$(CXX) $(CXXFLAGS) $$src -o $$out && echo "Build success" && echo "--Running--" && ./$$out; \
	else \
		echo "Error: test file '$$src' not found."; \
	fi

clean:
	rm -rf $(BUILD_DIR)