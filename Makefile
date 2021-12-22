CC= clang++
FRAMEWORKS= -framework Cocoa -framework OpenGL -framework IOKit
CFLAGS= -Wall -std=c++17
LIBS= -lglfw3 -lGLEW
OUTPUT= bin/app
WINOUT= bin/win64App.exe
DEPENDENCIES= head/shader.cpp head/texture.cpp head/controls.cpp head/objloader.cpp 
MLIBFOLDER= -L./libs/macos
wLIBFOLDER= -L./libs/win32



macos: main.cpp $(DEPENDENCIES)
	$(CC) $(CFLAGS) -o $(OUTPUT) main.cpp $(DEPENDENCIES) $(MLIBFOLDER) $(LIBS) $(FRAMEWORKS)

test: macos
	./bin/app

cleanup:
	rm -rf bin/app
	rm -rf /log/log.LOG

run:
	./bin/app


