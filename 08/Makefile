all: json

json: cjson.c
	gcc -I/usr/include/python3.10/ -fPIC -shared -o libutils.so cjson.c
	sudo python3 setup.py install
	./main.py

