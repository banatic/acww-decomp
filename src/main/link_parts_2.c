/* link_parts_2: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a7948 @ 0x020a7948, 0x2 bytes, Thumb
 * func_020a7944 @ 0x020a7944, 0x2 bytes, Thumb
 * func_020a7940 @ 0x020a7940, 0x4 bytes, Thumb
 * func_020a7938 @ 0x020a7938, 0x6 bytes, Thumb
 * func_020a7934 @ 0x020a7934, 0x2 bytes, Thumb
 * func_020a7930 @ 0x020a7930, 0x2 bytes, Thumb
 * func_020a78ec @ 0x020a78ec, 0x44 bytes, Thumb
 * func_020a7890 @ 0x020a7890, 0x5a bytes, Thumb
 * func_020a7880 @ 0x020a7880, 0x10 bytes, Thumb
 * func_020a7870 @ 0x020a7870, 0x10 bytes, Thumb
 */

struct UnkStruct_020a78ec {
    char pad_00;
    unsigned char byte;
};

extern void func_02077a54(struct UnkStruct_020a78ec *p, int b, unsigned char flags);
extern void func_02077a34(unsigned char *, int, unsigned char *);

void func_020a7948(void *object) {}

void func_020a7944(void *object) {}

void func_020a7940(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_020a7938(unsigned char *s, unsigned char *d)
{
    *d = *s;
}

void func_020a7934(void) {}

void func_020a7930(void) {}

void func_020a78ec(struct UnkStruct_020a78ec *p, int a, int b, int c, unsigned char d, int e)
{
    unsigned char flags = 0;
    if (c) {
        flags |= 1;
    }
    if (d) {
        flags |= 2;
    }
    func_02077a54(p, b, flags);
    p->byte = e;
    p->byte |= (a << 6) & 0xC0;
}

void func_020a7890(unsigned char *p1, int *p2, int p3, unsigned char *p4, unsigned char *p5, int *p6)
{
    unsigned char flags;

    func_02077a34(p1, p3, &flags);
    if (flags & 1) {
        *p4 = 1;
    } else {
        *p4 = 0;
    }
    if (flags & 2) {
        *p5 = 1;
    } else {
        *p5 = 0;
    }
    *p6 = p1[1] & 0x3f;
    *p2 = ((unsigned int) p1[1] >> 6) & 3;
}

int func_020a7880(int arg)
{
    func_020a7934();
    return arg;
}

int func_020a7870(int arg)
{
    func_020a7930();
    return arg;
}
