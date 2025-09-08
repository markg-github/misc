CXX = g++
CXXFLAGS = -g -Wall -Wextra
LDLIBS = -lcbor

TARGET1 = parse-cbor
TARGET2 = parse-att-doc

SOURCES1 = parse-cbor.cpp parse-cbor-helper.cpp
SOURCES2 = parse-att-doc.cpp parse-cbor-helper.cpp

# Define the object files (automatically generated from sources)
OBJECTS1 = $(SOURCES1:.cpp=.o)
OBJECTS2 = $(SOURCES2:.cpp=.o)

all: $(TARGET1)
all2: $(TARGET2)

$(TARGET1): $(OBJECTS1)
	$(CXX) $(CXXFLAGS) $(OBJECTS1) -o $@ $(LDLIBS)

$(TARGET2): $(OBJECTS2)
	$(CXX) $(CXXFLAGS) $(OBJECTS2) -o $@ $(LDLIBS)

# Rule to compile each .cpp file into a .o file
# -c: Compile and assemble, but do not link
# -o $@: Output to the target file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET1)

.PHONY: all clean
