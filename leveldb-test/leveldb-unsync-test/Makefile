
all : unsync check
unsync: unsync.cc
	g++ -I/home/liming/workspace/leveldb/include -L/home/liming/workspace/leveldb/  unsync.cc  -lleveldb -lpthread -ldl -rdynamic -o unsync

check: check.cc
	g++ -I/home/liming/workspace/leveldb/include -L/home/liming/workspace/leveldb/  check.cc  -lleveldb -lpthread -o check

clean:
	rm -f unsync check

