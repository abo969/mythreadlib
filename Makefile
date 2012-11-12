# Flags passed to the C++ compiler.
CXX_FLAGS += -g -Wall -Wextra -fPIC
CPP_FLAGS += -I.
CXX_DEFINES = -DTHREAD_COMPILING

LINK_FLAGS = -fPIC -shared -Wl,-soname
AR_FLAGS = cr

SHARED_TARGET = libthread.so.1.0
SHARED_TARGET2 = libthread.so
STATIC_TARGET = libthread.a
TARGETS = $(SHARED_TARGET) $(STATIC_TARGET)

SRC_DIR = ./linux
SRC_FILE1 = $(SRC_DIR)/mythread.cpp
OBJ_FILE1 = $(SRC_DIR)/mythread.o

SRC_FILE2 = $(SRC_DIR)/mymutex.cpp
OBJ_FILE2 = $(SRC_DIR)/mymutex.o

OBJ_FILES = $(OBJ_FILE1) $(OBJ_FILE2)

all : $(TARGETS)

clean :
	rm -f $(TARGETS) *.so $(OBJ_FILES)

$(OBJ_FILE1) : $(SRC_FILE1)
	$(CXX) $(CPP_FLAGS) $(CXX_DEFINES) $(CXX_FLAGS) -c $^ -o $@

$(OBJ_FILE2) : $(SRC_FILE2)
	$(CXX) $(CPP_FLAGS) $(CXX_DEFINES) $(CXX_FLAGS) -c $^ -o $@

all:
$(SHARED_TARGET): $(OBJ_FILES)
	$(CXX) $(LINK_FLAGS) -lpthread $^ -o $@ && ln -s $(SHARED_TARGET) $(SHARED_TARGET2) 

$(STATIC_TARGET): $(OBJ_FILES)
	$(AR) $(AR_FLAGS) $@ $^ && ranlib $@

