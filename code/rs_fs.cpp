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
	fs.seekg(root_directory_entry_offset(), ios::beg);
	int offset = root_directory_entry_offset();
	cout << " Offset at the beginning : " << offset <<'\n';
    char filename[8];
    int a;
    char extension[3];
    int b;
    char attribute[1];
	fs.read(filename, 8);
    fs.read(extension, 3);
    fs.read(attribute, 1);
    printf("%.8s.%.3s\n", filename, extension);
    
    while (1) {
        cout << "\niteration\n"<< std::flush;
        offset += 32;
        fs.seekg(offset, ios::beg);
        fs.read(filename, 8);
        fs.read(extension, 3);
        fs.read(attribute, 1);
        if (*attribute == 0x0f) {
            char* longfilename = (char*) calloc(sizeof(char), 26);
            char buf;
            int j = 0;
            fs.seekg(offset+1, ios::beg);
            for (int i = 0; i < 10; i++) {
                fs.read(&buf, 1);
                cout << buf;
                longfilename[j] = buf;
                fs.read(&buf, 1);
                j++;
            }
            fs.seekg(offset+0x0E, ios::beg);
            for (int i = 0; i < 12; i++) {
                fs.read(&buf, 1);
                cout << buf;
                longfilename[j] = buf;
                fs.read(&buf, 1);
                j++;
            }
            fs.seekg(offset+0x1C, ios::beg);
            for (int i = 0; i < 6; i++) {
                fs.read(&buf, 1);
                cout << buf;
                longfilename[j] = buf;
                fs.read(&buf, 1);
                j++;
            }
//            printf("long filename: %.26s\n", longfilename);
        }else{
            printf("%.8s.%.3s\n", filename, extension);
        }
        if (filename[0] == 0) {
            cout << "\n Reached end\n";
            break;
        }
    }
	
}

