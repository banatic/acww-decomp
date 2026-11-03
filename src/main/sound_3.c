/* sound_3: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02004270 @ 0x02004270, 0x10 bytes, Thumb
 * func_02004260 @ 0x02004260, 0x10 bytes, Thumb
 * func_0200424c @ 0x0200424c, 0x14 bytes, Thumb
 * func_0200423c @ 0x0200423c, 0x10 bytes, Thumb
 * func_0200422c @ 0x0200422c, 0x10 bytes, Thumb
 * func_0200421c @ 0x0200421c, 0x10 bytes, Thumb
 * func_0200420c @ 0x0200420c, 0x10 bytes, Thumb
 * func_020041fc @ 0x020041fc, 0x10 bytes, Thumb
 * func_020041ec @ 0x020041ec, 0x10 bytes, Thumb
 * func_020041dc @ 0x020041dc, 0x10 bytes, Thumb
 * func_020041cc @ 0x020041cc, 0x10 bytes, Thumb
 * func_020041bc @ 0x020041bc, 0x10 bytes, Thumb
 * func_020041ac @ 0x020041ac, 0x10 bytes, Thumb
 * func_020041a4 @ 0x020041a4, 0x8 bytes, Thumb
 * func_0200419c @ 0x0200419c, 0x8 bytes, Thumb
 * func_02004194 @ 0x02004194, 0x8 bytes, Thumb
 * func_02004158 @ 0x02004158, 0x3c bytes, Thumb
 */

extern void func_020f1c6c(void *param1, void *param2);
extern unsigned char data_021fd1bc[];
extern void func_020f1c00(int, int);
extern void func_020f1ba4(void *dst, const void *src, unsigned int size);
extern void func_020f1a54(int, int);
extern void func_020f19c0(int a, int b);
extern void func_020f165c(int *ptr, int value);
extern int *func_020f0ff0(void *arg);
extern void func_020f1108(void *);
extern void func_020f10b8(void *ptr);
extern void func_020f1074(int);
extern void func_020f1030(void *);
extern void func_020f0f7c(void *param1, void *param2);
extern void func_020f0f68(int a, int b);
extern void func_020f697c(void *);
extern void func_020f6950(unsigned char *, const unsigned char *);
extern void func_020f688c(void *, unsigned int, void *);
extern int data_021c67a4;
extern int data_021c67b8[3];
extern void func_020f660c(int a, int *b, int c);

void func_02004270(void *param)
{
    func_020f1c6c((void *) data_021fd1bc, param);
}

void func_02004260(int arg)
{
    func_020f1c00((unsigned int) data_021fd1bc, arg);
}

void func_0200424c(void *dst, const void *src)
{
    func_020f1ba4((void *) data_021fd1bc, dst, (unsigned int) src);
}

void func_0200423c(int p0)
{
    func_020f1a54((int) ((int *) data_021fd1bc), p0);
}

void func_0200422c(int arg)
{
    func_020f19c0((unsigned int) data_021fd1bc, arg);
}

void func_0200421c(int value)
{
    func_020f165c(((int *) data_021fd1bc), value);
}

int *func_0200420c(void)
{
    return func_020f0ff0((void *) data_021fd1bc);
}

void func_020041fc(void)
{
    func_020f1108((void *) data_021fd1bc);
}

void func_020041ec(void)
{
    func_020f10b8((void *) data_021fd1bc);
}

void func_020041dc(void)
{
    func_020f1074((int) ((int *) data_021fd1bc));
}

void func_020041cc(void)
{
    func_020f1030((void *) data_021fd1bc);
}

void func_020041bc(void *param1)
{
    func_020f0f7c((void *) data_021fd1bc, param1);
}

void func_020041ac(int arg)
{
    func_020f0f68((unsigned int) data_021fd1bc, arg);
}

void func_020041a4(void *argument0)
{
    func_020f697c((void *) argument0);
}

void func_0200419c(unsigned char *argument0, const unsigned char *argument1)
{
    func_020f6950((unsigned char *) argument0, (const unsigned char *) argument1);
}

void func_02004194(void *argument0, unsigned int argument1, void *argument2)
{
    func_020f688c((void *) argument0, (unsigned int) argument1, (void *) argument2);
}

void func_02004158(int a, int *src, int c)
{
    int diff[3];
    if (data_021c67a4 == 0) {
        return;
    }
    diff[0] = src[0] - data_021c67b8[0];
    diff[1] = src[1] - data_021c67b8[1];
    diff[2] = src[2] - data_021c67b8[2];
    func_020f660c(a, diff, c);
}
