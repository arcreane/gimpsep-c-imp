clean:
	rm main

main: clean
	g++ -o main.o -c main.cpp -I/usr/include/opencv4/ -Icore
	g++ -o gimpsep.o -c core/gimpsep.cpp -I/usr/include/opencv4/
	g++ -o main main.o gimpsep.o -Lcore -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_stitching
