#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define RS_IDENTIFIER_OFFSET 3

class rs_fs {
		char identifier [8];
	public:
		rs_fs (FILE* fs);
		char* get_identifier();
};
