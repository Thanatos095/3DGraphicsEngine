SRC_DIR := source
OBJ_DIR := build

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

INCLUDESPATHS := -IE:\includes\glfw-3.3.8.bin.WIN64\include -IE:\includes\glew-2.1.0\include -IE:\includes\glm -IE:\repositories\openGLEngine\headers
LDFLAGS := -LE:\includes\glfw-3.3.8.bin.WIN64\lib-mingw-w64 -LE:\includes\glew-2.1.0\lib\Release\x64 -l:libglfw3.a -l:libglfw3dll.a -lopengl32 -lglew32
CPPFLAGS := -g -std=c++17 -O2 -Wall
CC := g++
main: $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDESPATHS) -c -o $@ $<

clean:
	rm build/*.o main.exe