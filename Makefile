CC := g++ --std=c++17
BUILD_DIR := ./build
SOURCES := $(shell find . -name "*.cc") $(shell find . -name "*.h")

all: build

clean:
	rm -rfv $(BUILD_DIR)

ant: build
	$(BUILD_DIR)/ant.out

gauss: build
	$(BUILD_DIR)/gauss.out

winograd: build
	$(BUILD_DIR)/winograd.out

linter:
	clang-format -n -style=google $(SOURCES)

linter-fix:
	clang-format -i -style=google $(SOURCES)

cppcheck:
	cppcheck --language=c++ --std=c++17 \
	--enable=all \
	--suppress=unusedFunction \
	--suppress=unusedStructMember \
	--suppress=missingInclude \
	$(SOURCES)

build:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

.PHONY: all clean ant gauss winograd linter cppcheck build


