/* obj_020dd33c_5: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02059e10 @ 0x02059e10, 0xc bytes, Thumb
 * func_02059d28 @ 0x02059d28, 0xe8 bytes, Thumb
 * func_02059cf8 @ 0x02059cf8, 0x30 bytes, Thumb
 * func_02059cc4 @ 0x02059cc4, 0x34 bytes, Thumb
 * func_02059c80 @ 0x02059c80, 0x44 bytes, Thumb
 * func_02059c60 @ 0x02059c60, 0x20 bytes, Thumb
 * func_02059c40 @ 0x02059c40, 0x20 bytes, Thumb
 */

typedef struct {
    char pad_00[12];
    unsigned short unk_0C;
} UnkStruct_02059cf8;

struct Params {
    char pad_00[0xc];
    unsigned short unk_0C;
};

struct Entry {
    char pad_00[0xc];
    char data[0xc];
};

extern unsigned int data_020cbb44[];
extern int func_0207cec0(const void *table, int mask);
extern int func_020808ec(unsigned int object);
extern unsigned char data_021e5a2c[];
extern char *data_020dd31c[];
extern void *func_020edf70(int size);
extern void *func_020ee660(void *);
extern void func_020f5958(void *ptr);
extern int data_020da13c;
extern int data_020dd33c;
extern void func_02059ac4(void *);
extern void func_0200451c(void *ptr);
extern int data_021c9350;
extern int func_020044a0(void *ptr);

unsigned int func_02059e10(unsigned int r0)
{
    return data_020cbb44[r0];
}

int func_02059d28(void *param)
{
    int forwarded_value;

    volatile unsigned short id_store;
    unsigned short full;
    unsigned short raw;
    int ret = 3;

    id_store = 0xfff1;
    id_store = (unsigned short) (*(unsigned int *) ((unsigned char *) param + 8));

    full = id_store;
    raw = id_store;

    switch ((raw & 0xf000) >> 12) {
        case 0xe: {
            int idx = ((forwarded_value = (int) func_0207cec0((const void *) data_021e5a2c, raw & 0x0fff)),
                       func_020808ec((unsigned int) forwarded_value));
            switch (idx) {
                case 0:
                case 5:
                case 6:
                case 10:
                case 12:
                case 15:
                case 16:
                case 21:
                case 25:
                case 31:
                case 32:
                    ret = 4;
                    break;
                case 1:
                case 2:
                case 4:
                case 7:
                case 9:
                case 13:
                case 14:
                case 17:
                case 19:
                case 20:
                case 22:
                case 23:
                case 26:
                case 27:
                case 29:
                    ret = 5;
                    break;
            }
        } break;
        case 0xd:
            switch (full) {
                case 0xd00c:
                    ret = 0;
                    break;
                case 0xd013:
                    ret = 1;
                    break;
                case 0xd012:
                case 0xd025:
                    ret = 2;
                    break;
            }
            break;
    }
    return ret;
}

char *func_02059cf8(UnkStruct_02059cf8 *obj, int size)
{
    if (obj->unk_0C == 9) {
        return data_020dd31c[3] + size * 24;
    } else {
        return data_020dd31c[func_02059d28((void *) obj)] + size * 24;
    }
}

void *func_02059cc4(struct Params *a, int index)
{
    if (a->unk_0C == 9) {
        return ((struct Entry **) data_020dd31c)[3][index].data;
    } else {
        return ((struct Entry **) data_020dd31c)[func_02059d28((void *) a)][index].data;
    }
}

void *func_02059c80(void)
{
    void *p = func_020edf70(0x11c);
    if (p) {
        func_020ee660(p);
        *(volatile void **) p = (void *) &data_020da13c;
        *(volatile void **) p = (void *) &data_020dd33c;
        *(volatile unsigned short *) ((char *) p + 0x50) = 0xfff1;
        func_020f5958((char *) p + 0xdc);
    }
    return p;
}

int func_02059c60(int param)
{
    func_02059ac4((void *) param);
    func_0200451c((void *) (param + 0xdc));
    data_021c9350 = param;
    return 1;
}

int func_02059c40(void)
{
    func_020044a0((*(char **) &data_021c9350) + 0xDC);
    (*(char **) &data_021c9350) = 0;
    return 1;
}
