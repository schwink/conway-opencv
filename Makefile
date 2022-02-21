
crossword: main.cpp
	mkdir -p out
	g++ -I /usr/local/Cellar/opencv/4.5.4_3/include/opencv4 -L /usr/local/Cellar/opencv/4.5.4_3/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++17 -o out/main main.cpp

clean:
	rm -rf out
