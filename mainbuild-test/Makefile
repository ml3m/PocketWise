# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -I./include -Wall -Wextra
LDFLAGS = -lmatplot

# Source and object files
SRCS = src/main.cpp \
       src/BudgetManagement.cpp \
       src/ExpenseRevenue.cpp \
       src/Investments.cpp \
       src/MainMenu.cpp \
       src/UserAuthentication.cpp \
       src/Analysis.cpp \
       src/Goals.cpp \
       src/terminal_utils.cpp \
       src/global.cpp

OBJS = $(SRCS:.cpp=.o)

# Precompiled header
PCH = include/precompiled.h
PCH_GCH = $(PCH).gch

# Executable name
TARGET = finance_app

# Default rule
all: $(TARGET)

# Precompiled header rule
$(PCH_GCH): $(PCH)
	$(CXX) $(CXXFLAGS) -x c++-header -o $(PCH_GCH) $(PCH)

# Linking the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compiling source files into object files
%.o: %.cpp $(PCH_GCH)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS) $(PCH_GCH)

# Phony targets
.PHONY: all clean
