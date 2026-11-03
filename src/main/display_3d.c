/* display_3d: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02002f68 @ 0x02002f68, 0xd0 bytes, Thumb
 * func_02002ee8 @ 0x02002ee8, 0x80 bytes, Thumb
 * func_02002ec0 @ 0x02002ec0, 0x28 bytes, Thumb
 * func_02002e98 @ 0x02002e98, 0x28 bytes, Thumb
 * func_02002e54 @ 0x02002e54, 0x44 bytes, Thumb
 * func_02002e48 @ 0x02002e48, 0xc bytes, Thumb
 * func_02002e3c @ 0x02002e3c, 0xc bytes, Thumb
 * func_02002e14 @ 0x02002e14, 0x28 bytes, Thumb
 */

typedef struct {
    unsigned long long d[6];
} DataType;

typedef struct {
    unsigned short w[32];
} Data_020d5ca4;

extern void G3X_Init(void);
extern void G3X_InitTable(void);
extern void G3X_InitMtxStack(void);
extern void G3i_PerspectiveW_(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
                              unsigned int);
extern void NNS_G3dInit(void);
extern void G3X_SetClearColor(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern DataType data_0213fee4;
extern char data_0213feb4[];
extern const DataType data_02138f8c;
extern void GX_SetBankForTex(int);
extern void GX_SetBankForTexPltt(int);
extern void OS_EnableDTCM(void);
extern int MTX_Inverse43(void *, void *);
extern void G3X_Reset(void);
extern Data_020d5ca4 data_020d5ca4;
extern void DC_FlushRange(void *ptr, int len);
extern void G3X_SetToonTable(void *ptr);
extern unsigned char data_0213feac[];
extern unsigned char data_0213feb0[];

void func_02002e54(void);

void func_02002f68(void)
{
    G3X_Init();
    G3X_InitTable();
    G3X_InitMtxStack();

    *(volatile unsigned short *) 0x04000060 = *(volatile unsigned short *) 0x04000060 & 0xffffcffd;
    *(volatile unsigned short *) 0x04000060 = (*(volatile unsigned short *) 0x04000060 & 0xffffcfff) | 0x10;
    *(volatile unsigned short *) 0x04000060 = (*(volatile unsigned short *) 0x04000060 & 0xffffcfff) | 0x08;
    *(volatile unsigned short *) 0x04000060 = *(volatile unsigned short *) 0x04000060 & 0x0000cfdf;

    *(volatile unsigned int *) 0x04000580 = 0xbfff0000;

    G3i_PerspectiveW_(0x579, 0x0f09, 0x1555, 0x1000, 0x003e8000, 0x1000, 1, 0);

    *(volatile unsigned int *) 0x0400044c = 0;
    *(volatile unsigned int *) 0x04000540 = 3;

    NNS_G3dInit();
    func_02002e54();

    G3X_SetClearColor(0, 0, 0x7fff, 0x3f, 1);

    (*(volatile unsigned short *) data_0213feac) = 0;
    (*(volatile unsigned int *) data_0213feb0) = 0x7fff;
}

void func_02002ee8(void)
{
    func_02002f68();
    GX_SetBankForTex(6);
    GX_SetBankForTexPltt(0x10);
    OS_EnableDTCM();

    *(volatile unsigned short *) 0x04000060 = (*(volatile unsigned short *) 0x04000060 & 0xffffcfff) | 4;
    *(volatile unsigned short *) 0x04000340 = 0;
    *(volatile unsigned short *) 0x04000060 = (*(volatile unsigned short *) 0x04000060 & 0xffffcfff) | 8;

    G3X_SetClearColor(0, 0, 0x7fff, 0, 1);

    data_0213fee4 = data_02138f8c;
    MTX_Inverse43(&data_0213fee4, data_0213feb4);
}

void func_02002ec0(void)
{
    G3X_Reset();
    *(volatile unsigned int *) 0x04000440 = 3;
    *(volatile unsigned int *) 0x04000454 = 0;
    *(volatile unsigned int *) 0x04000440 = 2;
}

void func_02002e98(const DataType *src)
{
    data_0213fee4 = *src;
    MTX_Inverse43(&data_0213fee4, data_0213feb4);
}

void func_02002e54(void)
{
    Data_020d5ca4 local;
    unsigned short *p;
    unsigned short v;

    local = data_020d5ca4;
    DC_FlushRange(&local, 0x40);
    p = (unsigned short *) 0x04000060;
    v = *p;
    v &= ~0x3002;
    *p = v;
    G3X_SetToonTable(&local);
}

void func_02002e48(int value)
{
    (*(int *) data_0213feb0) = value;
}

void func_02002e3c(unsigned short value)
{
    (*(volatile unsigned short *) data_0213feac) = value;
}

void func_02002e14(void)
{
    int stack_var;
    unsigned short *ptr_0x0213feac;
    int *ptr_0x0213feb0;

    stack_var = 1;
    ptr_0x0213feac = (unsigned short *) data_0213feac;
    ptr_0x0213feb0 = (int *) data_0213feb0;
    G3X_SetClearColor(*ptr_0x0213feac, 0, *ptr_0x0213feb0, 0x3f, stack_var);
}
