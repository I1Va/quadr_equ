CC = g++

CC_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal \
	-Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch \
	-Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions \
	-Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 \
	-Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor \
	-Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
	-Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla

INCLUDE_FLAGS = -Iinc

BUILD_DIR = build

RANDOM_DIR = random

TEST_DIR = test_data

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_OUTPUTFILE = $(BUILD_DIR)/quadr_eq.out

# tests_manager <=> TM
TM_DIR = quadr_tests
TM_FILES = $(wildcard $(TM_DIR)/*.cpp)
TM_OUTPUTFILE = $(BUILD_DIR)tests_manager.out

# LD_FLAGS = 

.PHONY: build

all: build

copy_to_build:
	cp -r ./$(SRC_DIR)/$(RANDOM_DIR) ./$(BUILD_DIR)
	cp -r ./$(SRC_DIR)/$(TEST_DIR) ./$(BUILD_DIR)

build: copy_to_build
	$(CC) $(SRC_FILES) -O0 -o $(SRC_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)

example: build
	./$(SRC_OUTPUTFILE) --example

testing: build
	./$(BUILD_DIR)/$(SRC_OUTPUTFILE) --testing

debug: copy_to_build
	$(CC) $(SRC_FILES) -O0 -o $(SRC_OUTPUTFILE) -D_DEBUG $(INCLUDE_FLAGS) $(CC_FLAGS)
	./$(SRC_OUTPUTFILE) --user

launch:
	./$(SRC_OUTPUTFILE) --user

clean:
	rm -f $(SRC_OUTPUTFILE) $(TM_OUTPUTFILE)