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

EXCEPT_MAIN_FILES = $(EXP_DIR)/experiments.cpp $(EXP_DIR)/quadr_equ_solver_funcs.cpp \
	$(EXP_DIR)/random_func.cpp $(EXP_DIR)/test_funcs.cpp  

EXCEPT_EXP = $(EXP_DIR)/main.cpp $(EXP_DIR)/quadr_equ_solver_funcs.cpp \
	$(EXP_DIR)/random_func.cpp $(EXP_DIR)/test_funcs.cpp  


SRC_DIR = src
SRC_FILES = $(EXCEPT_EXP) #$(wildcard $(SRC_DIR)/*.cpp)
SRC_OUTPUTFILE = $(BUILD_DIR)/quadr_eq.out

# tests_manager <=> TM
TM_DIR = quadr_tests
TM_FILES = $(wildcard $(TM_DIR)/*.cpp)
TM_OUTPUTFILE = $(BUILD_DIR)tests_manager.out
DEFINES = -testing# -D_DEBUG

#experiments <=> exp


EXP_DIR = $(SRC_DIR)
EXP_FILES = $(EXCEPT_MAIN_FILES)
EXP_OUTPUTFILE = $(BUILD_DIR)exp.out

# LD_FLAGS = 

.PHONY: build


all: build

build:
	$(CC) $(SRC_FILES) -O0 -o $(SRC_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)
	$(CC) $(EXP_FILES) -O0 -o $(EXP_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)
launch:
	$(CC) $(SRC_FILES) -O0 -o $(SRC_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)
	$(CC) $(EXP_FILES) -O0 -o $(EXP_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)
	./$(SRC_OUTPUTFILE) --user
clean:
	rm -f $(SRC_OUTPUTFILE) $(TM_OUTPUTFILE)
tm:
	./$(TM_OUTPUTFILE)
testing:
	$(CC) $(SRC_FILES) -O0 -o $(SRC_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)
	./$(SRC_OUTPUTFILE) --testing
exp:
	$(CC) $(SRC_FILES) -O0 -o $(SRC_OUTPUTFILE) $(INCLUDE_FLAGS) $(CC_FLAGS)
	./$(SRC_OUTPUTFILE) --example
random:
	$(CC) src/random_func.cpp -O0 -o $(BUILD_DIR)/random_func.out $(INCLUDE_FLAGS) $(CC_FLAGS)
	./build/random_func.out