#include "rs_fs.hpp"
using std::cout;
using std::ios;

rs_fs::rs_fs(const char* file_name){
	fs.open(file_name, ios::binary);
	if (!fs.is_open()){
		cout << "Failed to open a file\n";
		assert(true);
	}
	fs.seekg(RS_IDENTIFIER_OFFSET, ios::beg);
	fs.get(identifier, 9);
	fs.seekg(RS_BYTES_PER_SECTOR_OFFSET, ios::beg);
	char c1, c2;
	fs.get(c1);
	fs.get(c2);
	bytes_per_sector = 256*((int)c2) + (int)c1;
}

void rs_fs::print(){
	cout<< "id:  " << identifier << "\nBytes per sector: " << bytes_per_sector;
}
