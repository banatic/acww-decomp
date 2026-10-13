/* func_02085e94 @ 0x02085e94, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021d2128;
extern unsigned char data_021d213c;
extern unsigned char data_021d232c;
extern int data_020e1ca8;
extern void MI_CpuFill8(void *dst, int val, unsigned int size);
extern void func_02084dac(void *p);

void func_02085e94(void)
{
    data_021d2128 = 0;
    MI_CpuFill8(&data_021d213c, 0, 0xF0);
    MI_CpuFill8(&data_021d232c, 0, 0x474);
    func_02084dac(&data_020e1ca8);
}
