CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++17 -O2
TARGET = main
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp mydeque.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
