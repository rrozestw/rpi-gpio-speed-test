all:
	gcc -Ofast -o sysfs_access sysfs_access.c
	gcc -Ofast -o direct_access direct_access.c

.PHONY: clean

clean:
	rm -f *.o *~ direct_access sysfs_access
