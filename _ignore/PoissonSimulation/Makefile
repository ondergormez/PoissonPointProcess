#
# Filename:    Poisson Point Simulation
# Author:      Önder Görmez
# Dated:       December 17, 2017
# Decription:  Makefile for the PoissonPointProcess
#

# Directories
ROOT         = .
INC_DIR     := $(ROOT)
SRC_DIR     := $(ROOT)

# Compilers
CPP      := g++

# Add this flag to CPPFLAGS, for release optimization "-D NDEBUG"
CPPFLAGS := -Wall -fPIC -std=c++11 -w

SRCS_CPP = $(SRC_DIR)/poisson_simulation_prb.cpp \
           $(SRC_DIR)/poisson_simulation.cpp

main:
	$(CPP) $(CPPFLAGS) $(SRCS_CPP) -I$(INC_DIR) -o ./bin/poisson_simulation_prb.elf