CC = g++

CC_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal \
	-Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch \
	-Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions \
	-Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 \
	-Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor \
	-Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
	-Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror

INCLUDE_FLAGS = -Iinc

BUILD_DIR = build

RANDOM_DIR = random

TEST_DIR = test_data

SRC_DIR = src

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

OUT_FILE = $(BUILD_DIR)/quadr_eq.out

OBJ_FILES = $(SRC_FILES:.cpp=.o)


# LD_FLAGS =

.PHONY: build

all: build

copy_to_build:
	cp -r ./$(SRC_DIR)/$(RANDOM_DIR) ./$(BUILD_DIR)
	cp -r ./$(SRC_DIR)/$(TEST_DIR) ./$(BUILD_DIR)


# $< $^ $@

%.o: %.cpp
	$(CC) $< -O0 -o $@ -c $(INCLUDE_FLAGS) $(CC_FLAGS)


build: $(OBJ_FILES) copy_to_build
	$(CC) $(OBJ_FILES) -o $(OUT_FILE)


example: build
	./$(OUT_FILE) --example

testing: build
	./$(OUT_FILE) -t

parsing: build
	./$(OUT_FILE) -p

debug: copy_to_build
	$(CC) $(SRC_FILES) -O0 -o $(OUT_FILE) -D_DEBUG $(INCLUDE_FLAGS) $(CC_FLAGS)
	./$(OUT_FILE) --testing

launch: build
	./$(OUT_FILE) --user

clean:
	rm -f $(OUT_FILE) $(TM_OUTPUTFILE) $(OBJ_FILES)