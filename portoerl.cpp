#include "portoerl.h"

int write_cmd(string& str){
	return write_cmd((byte*)str.c_str(), str.length());
}

int read_exact(byte *buf, int len){
  int i, got=0;

  do {
      if ((i = read(0, buf+got, len-got)) <= 0)
          return(i);

    got += i;
  } while (got<len);

  return len;
}

int write_exact(byte *buf, int len){
  int i, wrote = 0;

  do {
    if ((i = write(1, buf+wrote, len-wrote)) <= 0)
      return (i);
      
    wrote += i;
  } while (wrote<len);

  return len;
}

int read_cmd(byte *buf){
  if (read_exact(buf, 2) != 2)
    return(-1);

  int len = (buf[0] << 8) | buf[1];
  return read_exact(buf, len);
}

int write_cmd(byte *buf, int len)
{
  byte li = (len >> 8) & 0xff;
  write_exact(&li, 1);
  
  li = len & 0xff;
  write_exact(&li, 1);

  return write_exact(buf, len);
}
