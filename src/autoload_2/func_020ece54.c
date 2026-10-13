/* func_020ece54 @ 0x020ece54, 0xc8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbf04;
extern int data_021fbf20;
extern unsigned char data_0213e6b4;
extern unsigned char data_021fbef8;
extern int data_0213e6b8;
extern unsigned char data_021fbef4;
extern void *data_021fbf08;
extern void *OS_PutString;
extern void *data_021fbf98;
extern void *data_021fbfb8;
extern void *data_021fc120;

extern void OS_InitMessageQueue(void *q, void *buf, int n);
extern void MI_CpuFill8(void *p, int a, int n);

void func_020ece54(int code, int a, int b, unsigned long long v, unsigned char n, void *f1, void *f2)
{
    data_021fbef8 = 0;
    data_021fbf04 = code;
    data_021fbf20 = a;
    data_0213e6b4 = (unsigned char) b;
    data_0213e6b8 = (int) ((v << 6) / 0x82ea);
    data_021fbef4 = (unsigned char) n;
    data_021fbf08 = f1;
    OS_PutString = f2;
    OS_InitMessageQueue(&data_021fbf98, &data_021fbfb8, 0x10);
    MI_CpuFill8(&data_021fc120, 0, 0x100);
}
