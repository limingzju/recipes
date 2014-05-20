#include <assert.h>
#include <stdio.h>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <sys/time.h>
#include <string>
#include <stdlib.h>
#include <leveldb/env.h>
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


  leveldb::Logger* logger;
  leveldb::Env* env = leveldb::Env::Default();
  leveldb::Status s= env->NewLogger("s.db.log", &logger);

  leveldb::Options options;
  options.info_log = logger;
  options.write_buffer_size = 500 * 1024 * 1024;
  leveldb::Status status = leveldb::DB::Open(options, "./s.db", &db);
  printf("status %s\n", status.ToString().c_str());
  assert(status.ok());

  leveldb::WriteOptions write_options = leveldb::WriteOptions();

  double s1 = currentMilliSecond();
  for (int i = 0; i < 1; i++) {
    leveldb::WriteBatch batch;

    // 1024 * 1MB
    for (int j = 0; j < 1024; j++) {
      char key[100];
      int num = 10*i +  j;
      snprintf(key, sizeof(key), "%16d", num);
      string value;
      leveldb::Status s = db->Get(leveldb::ReadOptions(), key, &value);
      if (!s.ok()) {
        printf("%s error\n", key);
      }
    }
  }
  printf("check ok\n");

 delete db;
  return 0;
}
