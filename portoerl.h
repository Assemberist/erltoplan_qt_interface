#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string>

using namespace std;

typedef unsigned char byte;

int read_cmd(byte *buf);
int write_cmd(byte *buf, int len);
int write_cmd(string& str);

