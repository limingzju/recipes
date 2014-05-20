
all : sync check
sync: sync.cc
	g++ -I/home/liming/workspace/leveldb-sync/include -L/home/liming/workspace/leveldb-sync/  sync.cc  -lleveldb -lpthread -o sync

check: check.cc
	g++ -I/home/liming/workspace/leveldb-sync/include -L/home/liming/workspace/leveldb-sync/  check.cc  -lleveldb -lpthread -o check

clean:
	rm -f sync check

