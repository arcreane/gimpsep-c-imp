clean:
	rm -f ./main
	rm -f ./main.o
	rm -f ./Gimpsep.o
	rm -f ./GimpsepVideo.o
	rm -f ./FileReader.o
main: clean
	g++ -o main.o -c main.cpp -I/usr/include/opencv4/ -Icore -Iutils
	g++ -o Gimpsep.o -c core/Gimpsep.cpp -I/usr/include/opencv4/
	g++ -o GimpsepVideo.o -c core/GimpsepVideo.cpp -I/usr/include/opencv4/
	g++ -o FileReader.o -c utils/FileReader.cpp 
	g++ -o main main.o Gimpsep.o GimpsepVideo.o FileReader.o -Lcore -Lutils -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_stitching -lopencv_objdetect
