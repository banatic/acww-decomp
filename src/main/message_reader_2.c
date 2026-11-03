/* message_reader_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b4424 @ 0x020b4424, 0x24 bytes, Thumb
 * func_020b43f4 @ 0x020b43f4, 0x30 bytes, Thumb
 */

extern int data_021f4dac;
extern int func_020b42a0(int *, int);
extern int func_020b4218(int *);
extern void func_020b547c(void *);
extern void func_020a9b04(void *);
extern void MI_CpuFill8(void *, int, int);

int func_020b4424(int param)
{
    int result = 0;
    if (func_020b42a0(&data_021f4dac, param)) {
        result = func_020b4218(&data_021f4dac);
    }
    return result;
}

void func_020b43f4(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_020b547c((char *) r4 + 0x4c);
    func_020a9b04((char *) r4 + 0xaf0);
    MI_CpuFill8((char *) r4 + 0xafc, 0, 0xa00);
}
