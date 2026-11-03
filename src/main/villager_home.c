/* villager_home: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020800fc @ 0x020800fc, 0xc bytes, Thumb
 * func_020800ec @ 0x020800ec, 0x10 bytes, Thumb
 * func_020800dc @ 0x020800dc, 0x10 bytes, Thumb
 * func_020800d0 @ 0x020800d0, 0xc bytes, Thumb
 * func_020800b8 @ 0x020800b8, 0x18 bytes, Thumb
 * func_02080078 @ 0x02080078, 0x40 bytes, Thumb
 */

extern void func_02081f94(int);
extern int func_02081f80(int arg);
extern unsigned int func_0204e414(void);
extern int func_0204e3f4(int a, int b, int c, int d);

int func_020800fc(int a)
{
    return a + 0x7b8;
}

void func_020800ec(int p0)
{
    func_02081f94((p0 + 1998));
}

int func_020800dc(int arg)
{
    return func_02081f80(arg + 0x7CE);
}

int func_020800d0(int a)
{
    return a + 0x7ce;
}

// placeholder, not actually used
// placeholder, not actually used
void func_020800b8(unsigned char *dst, unsigned char *src)
{
    unsigned char a, b;
    a = src[0];
    dst[0x7ce] = a;
    b = src[1];
    dst[0x7cf] = b;
}

void func_02080078(unsigned char *param1)
{
    unsigned short local_4;
    unsigned char *arg0;
    int val;
    int val2;
    unsigned char *puVar3;

    arg0 = param1;
    val = func_0204e414();
    if (val != 0) {
        if (func_020800dc((int) arg0) != 0) {
            puVar3 = (unsigned char *) func_020800d0((int) arg0);
            local_4 = 0x500a;
            func_0204e3f4(val, *puVar3, puVar3[1], (int) &local_4);
        }
    }
    return;
}
