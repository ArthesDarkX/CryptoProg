CXX      = g++
CXXFLAGS = -Wall -Wextra
TARGET   = hash
SRC      = main.cpp
LDLIBS = -lcryptopp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean
