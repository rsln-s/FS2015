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
	fs.get(c1);
	sectors_per_cluster = (int)c1;
	fs.get(c1);
	fs.get(c2);
	reserved_sectors = 256*((int)c2) + (int)c1;
	fs.seekg(RS_NUMBER_OF_FATS_OFFSET, ios::beg);
	fs.get(c1);
	number_of_FATs = (int)c1;
	fs.seekg(RS_ROOT_ENTRIES_OFFSET, ios::beg);
	fs.get(c1);
	fs.get(c2);
	root_entries = 256*((int)c2) + (int)c1;
	fs.seekg(RS_SECTOR_PER_FAT_OFFSET, ios::beg);
	fs.get(c1);
	fs.get(c2);
	sector_per_fat = 256*((int)c2) + (int)c1;
}

void rs_fs::print(){
	cout<< "id:  " << identifier << "\nBytes per sector: " << bytes_per_sector << "\nSectors per cluster: " << sectors_per_cluster << "\nReserved sectors " << reserved_sectors << "\nSector per FAT: " << sector_per_fat << "\nRoot entries: " << root_entries << '\n';
}

void rs_fs::ls(){
	fs.seekg(root_catalog_offset(), ios::beg);
	int offset = root_catalog_offset();
	cout << " Offset at the beginning : " << offset <<'\n';
	char filename[8];
	fs.get(filename, 9);
	cout << " Please let this be a name of a file: " << filename << '\n';
}

