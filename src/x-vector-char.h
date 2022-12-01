#ifndef __XSTRING_H
#define __XSTRING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String{
	char*  buffer;
	int    length;
	int    size;
} String;

String String_alloc(){
	int len=10;
	String s={
		.buffer=(char*)malloc(2*len * sizeof(char)),
		.length=len,
		.size=2*len
	};
	strcpy(s.buffer,"                    ");
	return s;
}
int String_free(String self){
	free(self.buffer);
	self.length=10;
	self.size=10;
	self.buffer=0;
}
String String_of(char str[]){
	int len=strlen(str);
	String s={
		.buffer=(char*)malloc(2*len * sizeof(char)),
		.length=len,
		.size=2*len
	};
	s.buffer=strcpy(s.buffer,str);
	return s;
}
String String_append_chars(String self,char str[]){
	int add_len=strlen(str);
	int new_len=self.length+add_len;
	int new_sz=self.size;
	char* old_str=self.buffer;
	if(new_len > new_sz) {
		new_sz=new_len * 2;
	}

	char* new_buffer = (char*)malloc(new_sz*sizeof(char));

	new_buffer=strcpy(new_buffer,old_str);
	new_buffer=strcat(new_buffer,str);
	self.buffer=new_buffer;
	return self;
}
int String_print(String self){
	printf( "%s", self.buffer );
}

/// #define __XSTRING_TEST \
/// 	String str=String_alloc(); \
/// 	String_append_chars(str," abcd "); \
/// 	String_print(str); \
/// 	String_free(str); \
/// 	String str2=String_of("something\n"); \
/// 	String_print(str2);\

#endif