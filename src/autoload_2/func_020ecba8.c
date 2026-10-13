/* func_020ecba8 @ 0x020ecba8, 0x13c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern char data_021fbef8;
extern int CTRDGi_WriteAgbFlashSectorAsync;
extern int data_021fbf30;
extern int data_021fbf40;
extern char *data_021fbf3c;
extern short data_021fbefc;
extern short data_021fbf00;
extern int data_0213e6bc;
extern int data_0213e6c0;
extern int data_021fbf1c;
extern int data_021fbf2c;
extern int data_021fbf44;
extern int data_021fbf4c;
extern int data_021fbf14;
extern int data_021fbf10;
extern int data_021fbf0c;
extern int data_021fbf34;
extern char data_021fbff8[0x40];
void MI_CpuFill8(void *dst, unsigned char fill, unsigned int size);
extern void func_020edab8(void);
extern void func_020edaa8(void);
extern void func_ov065_0227f1f4(void (*)(void), void (*)(void));
void func_020ecba8(unsigned char a0, int a1, int a2, int a3, char *a4)
{
    unsigned int i;
    char *p;
    data_021fbef8 = a0;
    CTRDGi_WriteAgbFlashSectorAsync = a1;
    data_021fbf40 = a3;
    data_021fbf3c = a4;
    data_021fbf30 = a2;
    data_021fbefc = 0;
    data_021fbf00 = 0;
    data_0213e6bc = 0;
    data_0213e6c0 = 1;
    data_021fbf1c = 0;
    data_021fbf2c = 0;
    data_021fbf44 = 0;
    data_021fbf4c = 0;
    data_021fbf14 = 0;
    data_021fbf10 = 0;
    data_021fbf0c = 0;
    data_021fbf34 = 0;
    MI_CpuFill8(data_021fbff8, 0, 0x40);
    for (i = 0; i < 32; i++) {
        p = data_021fbf3c + (i * 0x23);
        p[0x1a0] = 0;
    }

    func_ov065_0227f1f4(func_020edab8, func_020edaa8);
}
