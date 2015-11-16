#include "rs_fs.hpp"

rs_fs::rs_fs(FILE* fs){
	fseek(fs, RS_IDENTIFIER_OFFSET, SEEK_SET);
	fread(identifier, 1, 8, fs);
}

char* rs_fs::get_identifier(){
	return identifier;
}
