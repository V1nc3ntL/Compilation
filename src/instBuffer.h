
#ifndef __INST_BUFFER_HH__
#define __INST_BUFFER_HH__
typedef void (*inst3Member)(int32_t,int32_t,int32_t);
typedef void (*inst2Member)(int32_t,int32_t);
typedef void (*inst1Member)(int32_t);
typedef void (*inst0Member)();

typedef union {
    inst3Member tre;
    inst2Member duo;
    inst1Member uno;
    inst0Member zer;
}instWoutArg;

typedef struct{
    instWoutArg in;
    int32_t nArg;
    int32_t* arg;
}inst;

typedef struct{
    inst** bf;
    int32_t size;
}buffer;

void addToInstBuffer(instWoutArg i,int32_t a,int32_t b,int32_t c);
#endif