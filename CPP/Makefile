CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra
SRC := $(shell find src test -name '*.cpp')
OBJ = $(SRC:.cpp=.o)
TARGET = ds_project

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(CXX) $(OBJ) -o $@

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	@./$(TARGET)
	@make clean --silent

clean:
	@rm -f $(OBJ) $(TARGET)