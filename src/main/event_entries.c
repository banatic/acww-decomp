/* event_entries: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203f598 @ 0x0203f598, 0xc bytes, Thumb
 * func_0203f58c @ 0x0203f58c, 0xa bytes, Thumb
 * func_0203f568 @ 0x0203f568, 0x24 bytes, Thumb
 * func_0203f53c @ 0x0203f53c, 0x2c bytes, Thumb
 * func_0203f504 @ 0x0203f504, 0x38 bytes, Thumb
 */

struct Func0203f598 {
    int unk_00;
    int unk_04;
    unsigned char unk_08;
};

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    int unk_10;
    unsigned char unk_14;
} UnkStruct_0203f58c;

struct UnkStruct_0203f53c {
    char data[28];
};

struct UnkStruct_0203f504 {
    unsigned char data[0x1c];
};

extern int func_020e8ce0(void *param1, void *param2);
extern struct UnkStruct_0203f53c data_021c72e8[15];
extern void MI_CpuFill8(void *p, int a, int b);

void func_0203f598(struct Func0203f598 *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    p->unk_08 = 0xff;
}

void func_0203f58c(UnkStruct_0203f58c *p)
{
    p->unk_14 = 0;
    p->unk_0C = 0;
    p->unk_10 = 0;
}

void func_0203f568(void *param1)
{
    void *r5;
    void *r4;
    void *r6;

    r6 = param1;
    r5 = *(void **) r6;
    while (r5) {
        r4 = *(void **) ((char *) r5 + 4);
        func_020e8ce0(r6, r5);
        func_0203f58c((UnkStruct_0203f58c *) r5);
        r5 = r4;
    }
}

void func_0203f53c(void)
{
    int i;
    for (i = 0; i < 15; i++) {
        func_0203f58c((UnkStruct_0203f58c *) (&data_021c72e8[i]));
    }
    MI_CpuFill8(data_021c72e8, 0, 15);
}

struct UnkStruct_0203f504 *func_0203f504(void)
{
    int i;
    unsigned int found;

    for (i = 0; i < 15; i++) {
        found = (((struct UnkStruct_0203f504 *) data_021c72e8)[i].data[0x14] == 0) ? 1 : 0;
        if (found > 0) {
            return &((struct UnkStruct_0203f504 *) data_021c72e8)[i];
        }
    }
    return 0;
}
