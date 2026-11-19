CXX = g++
CXX_FLAGS = -std=c++14 -Wall -Wextra -Iinclude
SOURCES = src/main.cpp \
	  src/cipher.cpp \
	  src/interface.cpp
LDLIBS = -lcryptopp
TARGET = cipher

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXX_FLAGS) $(SOURCES) -o $(TARGET) $(LDLIBS)

clean:
	rm -rf $(TARGET)

.PHONY: all clean