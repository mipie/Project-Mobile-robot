.PHONY = all clean compile install

all: clean compile

clean:
	cd ./lib_dir && make clean
	cd ./exec_dir && make clean


compile:
	cd ./lib_dir && make
	cd ./exec_dir && make


install: clean compile
	cd ./exec_dir && make install

