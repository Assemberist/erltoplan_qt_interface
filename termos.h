#pragma once

#include <string>
#include <string.h>
#include <vector>
#include <stdint.h>

using namespace std;

struct point{
	size_t position;
	uint32_t items;
	point(size_t pos, int32_t item = 0) : position(pos), items(item){}
};

struct termos{
	string str;
	
	termos();
	termos(const char* format, ...);

	void put_atom(const char*);
	void put_tuple(char);
	void put_string(const char* src);
	void put_list(int32_t);
	void put_int(int32_t);
	void end_of_list();
};

