#ifndef OUTPUTSTREAM_H
#define OUTPUTSTREAM_H

struct s_outstream {
	void* dest;
	int (*f_write_c)(void*, char);
	int (*f_write_s)(void*, char*, int);
	void (*f_close)(void*);
};
typedef struct s_outstream OUTSTREAM;

#define OUTPUT_SUCCESSED 0
#define OUTPUT_FAILED -1

OUTSTREAM* createEmptyOutputStream();
int outstream_writec(OUTSTREAM* stream, char c);
int outstream_writes(OUTSTREAM* stream, char* sh, int len);
void outstream_close(OUTSTREAM* stream);
void destroyOutputStream();

/* fileoutputstream factory */
OUTSTREAM* createFileOutputStream(FILE* fp);
int os_fileos_writec(void* fp, char c);
int os_fileos_writes(void* fp, char* s, int len);
void os_fileos_close(void* fp);


#endif
