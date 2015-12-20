#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "rs_fs.hpp"
using std::cout;
using std::cin;

int main(){
//    char* dir_name = "";
	rs_fs* my_fat = new rs_fs("../fatdisk");
	my_fat->print();
	my_fat->ls();
    my_fat->cd(NULL);
	return 0;
}
