/* sound_5: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200467c @ 0x0200467c, 0x10 bytes, Thumb
 * func_02004668 @ 0x02004668, 0x14 bytes, Thumb
 * func_02004658 @ 0x02004658, 0x10 bytes, Thumb
 * func_02004644 @ 0x02004644, 0x14 bytes, Thumb
 * func_02004634 @ 0x02004634, 0x10 bytes, Thumb
 */

extern void func_020f1fb4(int, int);
extern void func_020f0df0(int, int, int);
extern unsigned char data_021fd1bc[];
extern void func_020f1f24(void *addr, int arg);
extern void func_020f1ed4(void *, int, int);
extern void func_020f2354(void *receiver, int effect);

void func_0200467c(int p0)
{
    func_020f1fb4((int) ((int *) data_021fd1bc), p0);
}

void func_02004668(int a, int b)
{
    func_020f0df0((unsigned int) data_021fd1bc, a, b);
}

void func_02004658(int arg)
{
    func_020f1f24((void *) data_021fd1bc, arg);
}

void func_02004644(int a, int b)
{
    func_020f1ed4(((int *) data_021fd1bc), a, b);
}

void func_02004634(int arg)
{
    func_020f2354(data_021fd1bc, arg);
}
