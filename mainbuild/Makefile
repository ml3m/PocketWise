# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -I./include
LDFLAGS = -lmatplot 

# Source and object files
SRCS = src/main.cpp \
       src/BudgetManagement.cpp \
       src/ExpenseRevenue.cpp \
       src/Stocks.cpp \
       src/MainMenu.cpp \
       src/UserAuthentication.cpp \
       src/Analysis.cpp \
       src/Goals.cpp \
       src/terminal_utils.cpp \
       src/global.cpp \
       src/sha256.cpp 

OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = finance_app

# Default rule
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compiling source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean
