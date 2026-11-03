/* session_villager_5: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020786d8 @ 0x020786d8, 0x20 bytes, Thumb
 * func_0207868c @ 0x0207868c, 0x4c bytes, Thumb
 * func_02078654 @ 0x02078654, 0x38 bytes, Thumb
 * func_02078648 @ 0x02078648, 0xc bytes, Thumb
 * func_0207863c @ 0x0207863c, 0xc bytes, Thumb
 * func_02078630 @ 0x02078630, 0xc bytes, Thumb
 * func_02078624 @ 0x02078624, 0xc bytes, Thumb
 * func_02078618 @ 0x02078618, 0xc bytes, Thumb
 * func_0207860c @ 0x0207860c, 0xc bytes, Thumb
 * func_020785dc @ 0x020785dc, 0x30 bytes, Thumb
 */

extern int func_02073d90(void *obj);
extern void func_020786f8(int *dst, int a, int b, int c);
extern void func_02073820(void *obj);
extern void func_020737f0(void *obj, int *buf, int size);
extern void func_02073770(void *obj, int a, int b);
extern void *data_020ccf94;
extern int func_0207f294(int);
extern int func_0207cf74(int);
extern void func_020778b0(void *p, unsigned short value);

void func_020786d8(unsigned int *a, unsigned char *b, unsigned char *c, const unsigned char *d)
{
    *a = (*d >> 4) & 0xF;
    *b = *d & 0xF;
    *c = d[1];
}

void func_0207868c(int arg1, int arg2, int arg3)
{
    int local[2];
    void *p;
    if (func_02073d90(data_020ccf94)) {
        func_020786f8(local, arg1, arg3, arg2);
        p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, local, 2);
        func_02073770(p, 0x3c, 4);
    }
}

void func_02078654(int arg0, int arg1, int arg2)
{
    int v;
    if (func_02073d90(data_020ccf94) != 0) {
        v = func_0207f294(arg0);
        if (func_0207cf74(v) != 0) {
            func_0207868c(v, arg1, arg2);
        }
    }
}

void func_02078648(int p1, int p2)
{
    func_02078654(p1, p2, 0);
}

void func_0207863c(int a)
{
    func_02078654(a, 0, 1);
}

void func_02078630(int a)
{
    func_02078654(a, 1, 2);
}

void func_02078624(int a, int b)
{
    func_02078654(a, b, 3);
}

void func_02078618(int a, int b)
{
    func_02078654(a, b, 4);
}

void func_0207860c(int a, int b)
{
    func_02078654(a, b, 5);
}

void func_020785dc(unsigned char *out, unsigned int flags, unsigned char b3, unsigned short *data, unsigned int lowbits,
                   unsigned char bit3)
{
    out[2] = (lowbits & 7) | (((flags << 4) & 0xf0) | ((bit3 & 1) << 3));
    out[3] = b3;
    func_020778b0(out, *data);
}
