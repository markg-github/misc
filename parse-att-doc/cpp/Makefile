CXX = g++
CXXFLAGS = -g -Wall -Wextra
LDLIBS = -lcbor

TARGET = parse-att-doc
SRC = parse-att-doc.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
