#include "termos.h"

termos::termos(){
	str.push_back(131);
}

void termos::put_atom(const char* src){
	str.push_back(115);
	str.push_back((char)strlen(src));
	str.append(src);
}

void termos::put_tuple(char len){
	str.push_back(104);
	str.push_back(len);
}

void termos::put_list(int32_t len){
	str.push_back(108);
	for(int i=4; i--; str.push_back(((char*)&len)[i]));
}

void termos::end_of_list(){
	str.push_back(106);
}

void termos::put_string(const char* src){
	str.push_back(107);
	union{
		size_t len;
		char sym[4];
	}length;
	length.len = strlen(src);
	str.push_back(length.sym[1]);
	str.push_back(length.sym[0]);
	str.append(src);
}

void termos::put_int(int32_t val){
	str.push_back(98);
	for(int i=4; i--; str.push_back(((char*)&val)[i]));
}

termos::termos(const char* format, ...){
	vector<point> stack;
	void** args = (void**)&format;
	args++;

	str.push_back(131);
	while(*format){
		switch(*format){
			case ']':
				end_of_list();
				for(int i=4; i--; str[stack.back().position + 3 - i] = (((char*)&stack.back().items)[i]));
				stack.pop_back();
			case ' ':
			case ',':
				break;
				
			case '}':
				str[stack.back().position] = stack.back().items & 0xff;
				stack.pop_back();
				break;
	
			default:
				if(stack.size()) (stack.back()).items++;
				switch(*format){
					case '[':
					case '{':
						stack.emplace_back(str.length()+1, 0);
						*format == '[' ? put_list(0) : put_tuple(0);
						break;

					case '\'':
						{
							str.push_back(115);
							unsigned char len = strchr(format+1, '\'') - format -1;
							str.push_back(len);
							str.append(format+1, len);
							format += len + 1;				
						}
						break;
	
					case '\"':
						{
							str.push_back(107);
							unsigned len = strchr(format+1, '\"') - format - 1;
							str.push_back(((char*)&len)[1]);
							str.push_back(((char*)&len)[0]);
							str.append(format+1, len);
							format += len + 1;
						}
						break;
	
	
					case '%':
						format++;
						switch(*format){
							case 't':
								str.append((*(termos**)args)->str, 1, (*(termos**)args)->str.length()-1);
								break;
								
							case 's':
								put_string(*(const char**)args);
								break;
								
							case 'a':
								put_atom(*(const char**)args);
								break;
								
							case 'd':
								put_int(*(int32_t*)args);
						}
						args++;
						break;
						
					default:
						put_int(atoi(format));
				}
		}
		format++;
	}
}

