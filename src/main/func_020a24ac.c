/* func_020a24ac @ 0x020a24ac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e37f8;
extern void *func_020984e8(void);
extern void *func_0209847c(unsigned char);
extern void MI_CpuCopy8(void *, const void *, unsigned int);

void func_020a24ac(void *receiver)
{
    void *p1;
    void *p2;

    p1 = func_020984e8();
    p2 = func_0209847c(data_020e37f8);
    MI_CpuCopy8(p1, p2, 0x249c);
}
