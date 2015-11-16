#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstdio>
#include <fstream>
using std::string;
using std::ifstream;

#define RS_IDENTIFIER_OFFSET 3
#define RS_BYTES_PER_SECTOR_OFFSET 11
#define RS_ROOT_ENTRIES_OFFSET 17
#define RS_SECTOR_PER_FAT_OFFSET 22

class rs_fs {
		ifstream fs;
		char identifier[8];
		int bytes_per_sector;
		int sectors_per_cluster;
		int reserved_sectors;
		int sector_per_fat;
		int root_entries;
	public:
		rs_fs (const char* file_name);
		void print();
		int root_catalog_offset() { return bytes_per_sector * (reserved_sectors + sector_per_fat); }
		void ls();
};
