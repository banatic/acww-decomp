/* func_02002ee8 @ 0x02002ee8, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned long long d[6];
} DataType;
extern DataType data_0213fee4;
extern char data_0213feb4[];
extern const DataType data_02138f8c;

extern void func_02002f68(void);
extern void GX_SetBankForTex(int);
extern void GX_SetBankForTexPltt(int);
extern void OS_EnableDTCM(void);
extern void G3X_SetClearColor(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void MTX_Inverse43(void *, void *);

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
