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
	fs.read(&c1, 1);
    fs.read(&c2, 1);
	bytes_per_sector = 256*((int)c2) + (int)c1;
    fs.read(&c1, 1);
	sectors_per_cluster = (int)c1;
    fs.read(&c1, 1);
    fs.read(&c2, 1);
	reserved_sectors = 256*((int)c2) + (int)c1;
	fs.seekg(RS_NUMBER_OF_FATS_OFFSET, ios::beg);
    fs.read(&c1, 1);
	number_of_FATs = (int)c1;
	fs.seekg(RS_ROOT_ENTRIES_OFFSET, ios::beg);
    fs.read(&c1, 1);
    fs.read(&c2, 1);
	root_entries = 256*((int)c2) + (int)c1;
	fs.seekg(RS_SECTOR_PER_FAT_OFFSET, ios::beg);
    fs.read(&c1, 1);
    fs.read(&c2, 1);
	sector_per_fat = 256*((int)c2) + (int)c1;
    current_offset = root_directory_entry_offset();
}

void rs_fs::print(){
	cout<< "id:  " << identifier << "\nBytes per sector: " << bytes_per_sector << "\nSectors per cluster: " << sectors_per_cluster << "\nReserved sectors " << reserved_sectors << "\nSector per FAT: " << sector_per_fat << "\nRoot entries: " << root_entries << '\n';
}

void rs_fs::ls_routine(int offset){
    char filename[8];
    char extension[3];
    char attribute[1];
    while (1) {
        fs.seekg(offset, ios::beg);
        fs.read(filename, 8);
        fs.read(extension, 3);
        fs.read(attribute, 1);
        if (filename[0] == 0) {
            cout << "\n Reached end\n";
            break;
        }
        if (*attribute == 0x02) {
            offset += 32;
            printf("HIDDEN FILE\n");
            continue;
        }
        if (*attribute == 0x0f) {
            char buf;
            int j = 0;
            fs.seekg(offset+1, ios::beg);
            for (int i = 0; i < 10; i++) {
                fs.read(&buf, 1);
                if (buf == 0) {
                    continue;
                }
                cout << buf;
                fs.ignore();
            }
            fs.seekg(offset+0x0E, ios::beg);
            for (int i = 0; i < 12; i++) {
                fs.read(&buf, 1);
                if (buf == 0) {
                    continue;
                }
                cout << buf;
                fs.ignore();
            }
            fs.seekg(offset+0x1C, ios::beg);
            for (int i = 0; i < 6; i++) {
                fs.read(&buf, 1);
                if (buf == 0) {
                    continue;
                }
                cout << buf;
                fs.ignore();
            }
            printf("           long filename");
        }else{
            printf("%.8s.%.3s", filename, extension);
        }
        if (*attribute == 0x10) {
            cout << "             DIR\n";
        }else{
            cout <<"\n";
        }
        offset += 32;
    }
}

void rs_fs::ls(){
	cout << "Current offset : " << current_offset <<'\n';
    ls_routine(current_offset);
}

void rs_fs::cd(char* new_dir_name){
    int offset = current_offset;
    char attribute[1];
    char next_cluster_number_c[2];
    int next_cluster_number;
    while(1) {
        fs.seekg(offset+26, ios::beg);
        fs.read(next_cluster_number_c, 2);
        int next_cluster_number = 256*((int)next_cluster_number_c[1]) + (int)next_cluster_number_c[0];
        cout << next_cluster_number;
        fs.seekg(offset+11, ios::beg);
        fs.read(attribute, 1);
        if (*attribute == 0x10) {
            cout << '\n';
            break;
        }
        cout << '\n';
        offset += 64;
    }
}
