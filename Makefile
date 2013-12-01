objects = OS_Project6.o disk_volume.o file_alloc_table.o directory_table.o

all: $(objects)
	g++ -o project6 $(objects)

directory_table.o : directory_table.cpp directory_table.h global_vars.h
	g++ -c -Wall directory_table.cpp

file_alloc_table.o : file_alloc_table.cpp file_alloc_table.h
	g++ -c -Wall file_alloc_table.cpp

disk_volume.o : disk_volume.cpp disk_volume.h file_alloc_table.h directory_table.h global_vars.h
	g++ -c -Wall disk_volume.cpp

OS_Project6.o : OS_Project6.cpp 
	g++ -c -Wall OS_Project6.cpp

clean :
	rm -f $(objects) log*.txt core
