#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

struct s_instream {
	void* dest;
	int (*f_read)(void*, char*, int);
	int (*f_read_c)(void*);
	int (*f_read_s)(void*, char*, int);
	int (*f_skip)(void*, int);
	void (*f_close)(void*);
};
typedef struct s_instream INSTREAM;

INSTREAM* createEmptyInputStream(void);
int instream_read(INSTREAM* stream, char* dst, int len);
int instream_readc(INSTREAM* stream);
int instream_reads(INSTREAM* stream, char* dst, int len);
int instream_skip(INSTREAM* stream, int byte);
void instream_close(INSTREAM* stream);
void destroyInputStream(INSTREAM* stream);

/* fileoutputstream factory */
INSTREAM* createFileInputStream(FILE* fp);
int is_fileis_read(void* fp, char* dst, int len);
int is_fileis_readc(void* fp);
int is_fileis_reads(void* fp, char* dst, int len);
int is_fileis_skip(void* fp, int byte);
void is_fileis_close(void* fp);


#endif
