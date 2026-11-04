/* sound_13: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f0e48 @ 0x020f0e48, 0x18 bytes, ARM
 * func_020f0e34 @ 0x020f0e34, 0x14 bytes, ARM
 * func_020f0df0 @ 0x020f0df0, 0x44 bytes, ARM
 * func_020f0ddc @ 0x020f0ddc, 0x14 bytes, ARM
 */

extern int func_020eedb8(int a, int b, int c);
extern void func_020f1ed4(int a, int b, int c);
extern unsigned short data_0213e858;
extern void func_0210b634(void *a, unsigned short b, void *c);

void func_020f0e48(int p)
{
    func_020eedb8(0x2d, 0, p + 0x38);
}

void func_020f0e34(int x)
{
    func_020f1ed4(x, 0x2d, 1);
}

void func_020f0df0(char *a, void *b, void *c)
{
    func_020eedb8((int) b, 0, (int) (a + 0x38));
    func_0210b634(a + 0x38, data_0213e858, c);
}

void func_020f0ddc(void *r0, int r1)
{
    *(int *) ((char *) r0 + 4) = r1 << 12;
    *(unsigned short *) ((char *) r0 + 2) = 0;
}
