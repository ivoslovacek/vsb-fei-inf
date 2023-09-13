cpp_files=$(wildcard *.cpp)

default:
	g++ $(cpp_files) -o main -fsanitize=address

clean:
	rm main