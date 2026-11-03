/* held_item_pool: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205f15c @ 0x0205f15c, 0x60 bytes, Thumb
 * func_0205f150 @ 0x0205f150, 0xa bytes, Thumb
 * func_0205f140 @ 0x0205f140, 0x10 bytes, Thumb
 * func_0205f130 @ 0x0205f130, 0x10 bytes, Thumb
 * func_0205f120 @ 0x0205f120, 0x10 bytes, Thumb
 * func_0205f110 @ 0x0205f110, 0x10 bytes, Thumb
 * func_0205f100 @ 0x0205f100, 0x10 bytes, Thumb
 * func_0205f0c0 @ 0x0205f0c0, 0x40 bytes, Thumb
 * func_0205f094 @ 0x0205f094, 0x2c bytes, Thumb
 * func_0205f070 @ 0x0205f070, 0x24 bytes, Thumb
 */

extern int data_021ca16c;
extern int func_0205f20c(int *, int, int);
extern int func_0205f2b0(int *, int);
extern int NNS_G3dGetTexSRTAnmSet(int);
extern int func_02107bbc(int, int);
extern int func_02055e00(int);
extern void func_02056440(int, int, int, int, int, int);
extern void func_020b9ec4(void *);
extern void func_020ba004(void *);
extern int func_0205f6bc(int);
extern int func_0205f2f0(int, int);
extern int func_0205f644(void);
extern int func_02064af4(int, int, int);
extern void func_02055b50(int, int);
extern int func_021077e8(unsigned int *);

int func_0205f130(int a, int b);
int func_0205f110(int *base, int index);

void func_0205f15c(void *p0, int p1, int p2, int p3)
{
    int c, d;
    func_0205f20c(&data_021ca16c, p1, p2);
    c = func_02107bbc(NNS_G3dGetTexSRTAnmSet(func_0205f2b0(&data_021ca16c, p1)), 0);
    d = func_0205f110((int *) p0, p1);
    func_02056440(d, func_02055e00(func_0205f130((int) p0, p1)), c, p3, 0x1000, 0);
}

void *func_0205f150(unsigned char *p, int i)
{
    return (p + 220) + i * 20;
}

void *func_0205f140(void *base, int index)
{
    return (char *) base + 0x190 + index * 28;
}

int func_0205f130(int a, int b)
{
    return (a + 0x28c) + 244 * b;
}

void func_0205f120(unsigned char *r0, int r1, unsigned char r2)
{
    unsigned char *ptr;
    int offset;

    offset = r1 << 2;
    ptr = r0 + offset;
    *(unsigned int *) (ptr + 0x0b20) = r2;
}

int func_0205f110(int *base, int index)
{
    return *(int *) ((char *) base + (index << 2) + 0x0b20);
}

short *func_0205f100(short *base, int index)
{
    return (short *) ((char *) base + 0xb44) + index;
}

void func_0205f0c0(void *base, int idx)
{
    unsigned int flag;
    int off;

    off = idx * 28;
    flag = (((unsigned char *) base + off)[0x19d] == 1) ? 1 : 0;
    if (flag > 0) {
        func_020b9ec4((unsigned char *) base + 0x190 + off);
    } else {
        func_020ba004((unsigned char *) base + 0x190 + off);
    }
}

int func_0205f094(int a, int b, int c)
{
    int v1;
    int v2;
    int v3;
    v1 = func_0205f6bc(c);
    v2 = func_0205f2f0(a, b);
    v3 = func_0205f644();
    return func_02064af4(v1, v2, v3);
}

void func_0205f070(int param1, int param2)
{
    int result;
    int temp;

    temp = func_021077e8((unsigned int *) (unsigned long) func_0205f2f0((int) ((void *) param1), (int) param2));
    result = (int) func_0205f150((unsigned char *) param1, param2);
    func_02055b50(result, temp);
}
