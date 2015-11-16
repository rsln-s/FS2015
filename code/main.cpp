#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "rs_fs.hpp"
using std::cout;
using std::cin;

int main(){
	rs_fs* my_fat = new rs_fs("../fatdisk");
	cout << "id: " << my_fat->get_identifier();
	return 0;
}
