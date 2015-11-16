#include "rs_fs.hpp"
using std::cout;
using std::ios;

rs_fs::rs_fs(const char* file_name){
	fs.open(file_name, ios::binary);
	if (!fs.is_open()){
		cout << "Failed to open a file\n";
		assert(true);
	}
	fs.seekg(3, ios::beg);
	fs.get(identifier, 9);
}

char* rs_fs::get_identifier(){
	return identifier;
}
