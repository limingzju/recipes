#include <assert.h>
#include <stdio.h>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <sys/time.h>
#include <string>
#include <stdlib.h>
using namespace std;

uint64_t currentMilliSecond() {
  struct timeval tv;
  int s = gettimeofday(&tv, NULL);
  if (s < 0) {
    printf("gettimeofday error\n");
    exit(1);
  }
  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}



int main() {
  leveldb::DB* db;
  leveldb::Options options;
//  options.write_buffer_size = 500 * 1024 * 1024;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "./u.db", &db);
  printf("status %s\n", status.ToString().c_str());
  assert(status.ok());

  leveldb::WriteOptions write_options = leveldb::WriteOptions();

  char* value = new char[1024*1024];
  for (int i = 0; i < 1024 * 1024; i++) {
    value[i] = 'a' + i % 26;
  }

  double s1 = currentMilliSecond();

  // 1024 * 1MB
  for (int j = 0; j < 1024; j++) {
    leveldb::WriteBatch batch;
    char key[100];
    int num =  j;
    snprintf(key, sizeof(key), "%16d", num);
    batch.Put(key, leveldb::Slice(value, 1024*1024));
    db->Write(write_options, &batch);
  }

  string v;
  db->Get(leveldb::ReadOptions(), "loop", &v);
  printf("loop = %s\n", v.c_str());

  double s2 = currentMilliSecond();
  double time = (s2-s1)/1000;
  delete db;
  printf("cost %f s\n", time);
  return 0;
}
