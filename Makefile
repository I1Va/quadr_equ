CC = g++

CC_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal \
	-Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch \
	-Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions \
	-Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 \
	-Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor \
	-Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
	-Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla
INCLUDE_FLAGS = -Iinc

BUILD_DIR = build_files

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_OUTPUTFILE = $(BUILD_DIR)/quadr_eq.out

# tests_manager <=> TM
TM_DIR = quadr_tests
TM_FILES = $(wildcard $(TM_DIR)/*.cpp)
TM_OUTPUTFILE = $(BUILD_DIR)tests_manager.out
DEFINES = -testing# -D_DEBUG



# LD_FLAGS = 

all: build
	
build:
	$(CC) $(SRC_FILES) -O0 -o $(SRC_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)
	$(CC) $(TM_FILES) -O0 -o $(TM_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)
launch:
	./$(SRC_OUTPUTFILE)
clean:
	rm -f $(SRC_OUTPUTFILE) $(TM_OUTPUTFILE)
TM:
	$(CC) $(TM_FILES) -O0 -o $(TM_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)
	./$(TM_OUTPUTFILE)
testing:
	$(CC) $(SRC_FILES) -O0 -o $(SRC_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)
	./$(SRC_OUTPUTFILE) -testing