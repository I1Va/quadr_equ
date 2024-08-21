CC = g++
CC_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal \
	-Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch \
	-Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions \
	-Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 \
	-Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor \
	-Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
	-Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

DEFINES = # -D_DEBUG

OUTPUTFILE = quadr_eq.exe
OUTPUTFILE1 = tests.exe
# LD_FLAGS = 

all: build launch

build:
	$(CC) $(SRC_FILES) -O0 -o $(OUTPUTFILE) $(CC_FLAGS) $(DEFINES)
	$(CC) $(SRC_FILES) -O0 -o $(OUTPUTFILE1) $(CC_FLAGS) $(DEFINES) -DTESTING
launch:
	$(OUTPUTFILE)
tests:
	$(OUTPUTFILE1)
clean:
	rm -f $(OUTPUTFILE) $(OUTPUTFILE1)