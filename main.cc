#include <leveldb/db.h>
#include <iostream>
#include <string>


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
  int read() {
    string cmd;
    cin >> cmd;
    if(cmd == "quit") return 0;
    if(cmd == "put") {
      string name;
      string data;
      cin >> name;
      cin >> data;
      db->Put(leveldb::WriteOptions(), name, data);
    }else if(cmd == "get") {
      string name;
      cin >> name;
      string ret;
      if( db->Get(leveldb::ReadOptions(), name, &ret).ok() ) {
	cout << ret << endl;
      } else {
	cout << "did not find key\n";
      }
    }else if(cmd == "delete") {
      string name;
      cin >> name;
      if( db->Delete(leveldb::WriteOptions(), name).ok() ) {
	cout << "key deleted\n";
      }else{
	cout << "failed to delete\n";
      }
    }else if(cmd == "list") {
      leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
      for(it->SeekToFirst(); it->Valid(); it->Next()) {
	cout << "\t" << it->key().ToString() << endl;
      }
      delete it;
    }
  }
};

int main (int argc, char **argv) {
  if(argc < 2) {
    cout << argv[0] << " [database location] \n";
    return 0;
  }

  Control ctrl(argv[1]);

  do {
    cout << "> ";
  } while(ctrl.read());
}
