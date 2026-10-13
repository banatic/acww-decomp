/* func_02001988 @ 0x02001988, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void OS_DisableInterrupts(int a, int b, int c, int d);
extern void OS_VSNPrintf(int a, int b, int c, int d);
extern void OS_Terminate(void);

extern int data_0213fde4;
extern int data_0213fde8;
extern int data_0213fdec;

extern unsigned char FX_SinCosTable_[];

void func_02001988(int a, int b, int c, int d)
{
    OS_DisableInterrupts(a, b, c, d);
    data_0213fdec = a;
    data_0213fde8 = b;
    data_0213fde4 = (unsigned int) FX_SinCosTable_;
    OS_VSNPrintf((unsigned int) FX_SinCosTable_, 0x80, c, d);
    OS_Terminate();
}
