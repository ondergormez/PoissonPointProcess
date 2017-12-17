#
# Filename:    PoissonPointProcess
# Author:      Önder Görmez
# Dated:       December 17, 2017
# Decription:  Makefile for the PoissonPointProcess
#

# Directories
ROOT         = ..
MAIN_DIR    := $(ROOT)
INC_DIR     := $(ROOT)/core
SRC_DIR     := $(ROOT)/core

# Compilers
CPP      := g++

# Add this flag to CPPFLAGS, for release optimization "-D NDEBUG"
CPPFLAGS := -Wall -fPIC -std=c++11 -w

SRCS_CPP = $(MAIN_DIR)/PoisssonPointProcess_cpp_mex.cpp \
           $(SRC_DIR)/PoissonPointProcess.cpp

main:
	$(CPP) $(CPPFLAGS) $(SRCS_CPP) -I$(INC_DIR) -o PoisssonPointProcess.elf