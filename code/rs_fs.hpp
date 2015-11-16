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

class rs_fs {
		ifstream fs;
		char identifier[8];
		int bytes_per_sector;
	public:
		rs_fs (const char* file_name);
		char* get_identifier();
};
