CC = g++
CC_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal \
	-Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch \
	-Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions \
	-Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 \
	-Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor \
	-Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
	-Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla

SRC_DIR = src
SRC =  $(SRC_DIR)/main.cpp $(SRC_DIR)/quadr_equ_solver_funcs.cpp $(SRC_DIR)/quadr_equ_tests.cpp
DEFINES = -DTESTING # -D_DEBUG
OUTPUTFILE = main.exe
# LD_FLAGS = 

all:
	$(CC) $(SRC) -O0 -o $(OUTPUTFILE) $(CC_FLAGS)

launch:
	$(OUTPUTFILE)
clean:
	rm -f $(OUTPUTFILE)