/* block_02034858: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020348f8 @ 0x020348f8, 0x2 bytes, Thumb
 * func_020348ec @ 0x020348ec, 0xc bytes, Thumb
 * func_020348e0 @ 0x020348e0, 0xc bytes, Thumb
 * func_020348c8 @ 0x020348c8, 0x16 bytes, Thumb
 * func_020348c4 @ 0x020348c4, 0x2 bytes, Thumb
 * func_02034898 @ 0x02034898, 0x2a bytes, Thumb
 * func_0203488c @ 0x0203488c, 0xa bytes, Thumb
 * func_02034858 @ 0x02034858, 0x34 bytes, Thumb
 */

struct UnkStruct_02034898 {
    signed short a[3];
    signed short b[3];
    signed short c[3];
    char d;
};

extern unsigned int *data_021c5144;
extern unsigned int data_021c5140;
extern short data_020c9f0c[];
extern short data_020c9f04[];

void func_02034898(struct UnkStruct_02034898 *p);
void func_02034858(int param);

void func_020348f8(void) {}

void func_020348ec(unsigned int value)
{
    data_021c5144 = (unsigned int *) value;
}

void func_020348e0(unsigned int value)
{
    data_021c5140 = value;
}

void *func_020348c8(void *arg)
{
    func_02034898((struct UnkStruct_02034898 *) arg);
    func_02034858((int) arg);
    return arg;
}

void func_020348c4(void *object) {}

void func_02034898(struct UnkStruct_02034898 *p)
{
    unsigned int i;
    p->d = 0;
    i = 0;
    do {
        p->c[i] = 0;
        p->b[i] = p->c[i];
        p->a[i] = p->b[i];
        i++;
    } while (i < 3);
}

void func_0203488c(short *p, int i, int a, int b)
{
    short *q = p + i;
    q[3] = (short) a;
    q[6] = (short) b;
}

void func_02034858(int param)
{
    unsigned char i;
    for (i = 0; i < 3; i++) {
        func_0203488c((short *) param, (unsigned char) i, (short) data_020c9f0c[i], (short) data_020c9f04[i]);
    }
}
