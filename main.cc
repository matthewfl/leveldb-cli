#include <leveldb/db.h>
#include <iostream>



using namespace std;


class Control {
private:
  leveldb::DB *db;
public:
  Control(char *location) {
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, location, &db);
    assert(status.ok());
  }
};

int main (int argc, char **argv) {
  if(argc < 2) {
    cout << argv[0] << " [database location] \n";
    return 0;
  }

  Control ctrl(argv[1]);
}
