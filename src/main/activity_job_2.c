/* activity_job_2: 22 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a1948 @ 0x020a1948, 0xc bytes, Thumb
 * func_020a193c @ 0x020a193c, 0xc bytes, Thumb
 * func_020a1930 @ 0x020a1930, 0xc bytes, Thumb
 * func_020a1924 @ 0x020a1924, 0xc bytes, Thumb
 * func_020a1918 @ 0x020a1918, 0xc bytes, Thumb
 * func_020a190c @ 0x020a190c, 0xc bytes, Thumb
 * func_020a1900 @ 0x020a1900, 0xc bytes, Thumb
 * func_020a18f4 @ 0x020a18f4, 0xc bytes, Thumb
 * func_020a18e8 @ 0x020a18e8, 0xc bytes, Thumb
 * func_020a18dc @ 0x020a18dc, 0xc bytes, Thumb
 * func_020a18d0 @ 0x020a18d0, 0xc bytes, Thumb
 * func_020a18c4 @ 0x020a18c4, 0xc bytes, Thumb
 * func_020a18b8 @ 0x020a18b8, 0xc bytes, Thumb
 * func_020a18ac @ 0x020a18ac, 0xc bytes, Thumb
 * func_020a18a0 @ 0x020a18a0, 0xc bytes, Thumb
 * func_020a1894 @ 0x020a1894, 0xc bytes, Thumb
 * func_020a1888 @ 0x020a1888, 0xc bytes, Thumb
 * func_020a186c @ 0x020a186c, 0x1c bytes, Thumb
 * func_020a1848 @ 0x020a1848, 0x24 bytes, Thumb
 * func_020a182c @ 0x020a182c, 0x1c bytes, Thumb
 * func_020a1810 @ 0x020a1810, 0x1c bytes, Thumb
 * func_020a17ec @ 0x020a17ec, 0x24 bytes, Thumb
 */

struct UnkStruct_020a186c {
    unsigned char pad_00[0x50];
    int unk_50;
};

typedef struct {
    char pad_00[0x50];
    int unk_50;
    char pad_54[0x4D];
    unsigned char unk_A1;
} UnkStruct_020a1848;

struct UnkStruct_020a182c {
    char pad_00[0x50];
    int unk_50;
};

struct UnkStruct_020a17ec {
    char pad_00[0x50];
    int unk_50;
    char pad_54[0xa1 - 0x54];
    unsigned char unk_A1;
};

extern unsigned char data_021f3c38[];
extern struct UnkStruct_020a186c *data_021f3c3c;

void func_020a1948(void)
{
    (*(int *) data_021f3c38) = 1;
}

void func_020a193c(void)
{
    (*(int *) data_021f3c38) = 2;
}

void func_020a1930(void)
{
    (*(int *) data_021f3c38) = 6;
}

void func_020a1924(void)
{
    (*(int *) data_021f3c38) = 5;
}

void func_020a1918(void)
{
    (*(int *) data_021f3c38) = 3;
}

void func_020a190c(void)
{
    (*(int *) data_021f3c38) = 0x12;
}

void func_020a1900(void)
{
    unsigned int *r0;
    unsigned int r1;

    r1 = 0x13;
    r0 = (unsigned int *) data_021f3c38;
    *r0 = r1;
}

void func_020a18f4(void)
{
    (*(int *) data_021f3c38) = 0x14;
}

void func_020a18e8(void)
{
    (*(int *) data_021f3c38) = 21;
}

void func_020a18dc(void)
{
    unsigned int *ptr;
    ptr = (unsigned int *) data_021f3c38;
    *ptr = 0x16;
}

void func_020a18d0(void)
{
    unsigned int *ptr;
    ptr = (unsigned int *) data_021f3c38;
    *ptr = 0x17;
}

void func_020a18c4(void)
{
    unsigned int *ptr;
    unsigned int value;

    value = 0x18;
    ptr = (unsigned int *) data_021f3c38;
    *ptr = value;
}

void func_020a18b8(void)
{
    (*(int *) data_021f3c38) = 0x19;
}

void func_020a18ac(void)
{
    unsigned int *r0;
    unsigned int r1;

    r1 = 0x1a;
    r0 = (unsigned int *) data_021f3c38;
    *r0 = r1;
}

void func_020a18a0(void)
{
    (*(int *) data_021f3c38) = 27;
}

void func_020a1894(void)
{
    unsigned int *r0;
    unsigned int r1;

    r1 = 0x1f;
    r0 = (unsigned int *) data_021f3c38;
    *r0 = r1;
}

void func_020a1888(void)
{
    unsigned int *addr;
    addr = (unsigned int *) data_021f3c38;
    *addr = 0x1c;
}

int func_020a186c(void)
{
    if (data_021f3c3c != 0 && data_021f3c3c->unk_50 == 0) {
        return 1;
    }
    return 0;
}

int func_020a1848(void)
{
    if ((*(UnkStruct_020a1848 **) &data_021f3c3c) != 0 && (*(UnkStruct_020a1848 **) &data_021f3c3c)->unk_50 == 0x12 &&
        (*(UnkStruct_020a1848 **) &data_021f3c3c)->unk_A1 == 3) {
        return 1;
    }
    return 0;
}

int func_020a182c(void)
{
    if ((*(struct UnkStruct_020a182c **) &data_021f3c3c) != 0 &&
        (*(struct UnkStruct_020a182c **) &data_021f3c3c)->unk_50 == 0) {
        return 1;
    }
    return 0;
}

int func_020a1810(void)
{
    unsigned int *p = (*(unsigned int *const *) &data_021f3c3c);

    if (p != 0) {
        if (*(unsigned int *) ((char *) p + 0x50) == 0) {
            return 1;
        }
    }
    return 0;
}

int func_020a17ec(void)
{
    if ((*(struct UnkStruct_020a17ec **) &data_021f3c3c) != 0 &&
        (*(struct UnkStruct_020a17ec **) &data_021f3c3c)->unk_50 == 0x13 &&
        (*(struct UnkStruct_020a17ec **) &data_021f3c3c)->unk_A1 == 3) {
        return 1;
    } else {
        return 0;
    }
}
