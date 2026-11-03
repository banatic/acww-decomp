/* sky_object_kinds_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bf9cc @ 0x020bf9cc, 0x8 bytes, Thumb
 * func_020bf9ac @ 0x020bf9ac, 0x1e bytes, Thumb
 * func_020bf948 @ 0x020bf948, 0x64 bytes, Thumb
 * func_020bf924 @ 0x020bf924, 0x24 bytes, Thumb
 */

struct UnkStruct_020bf948 {
    char pad_00[0x28];
    int unk_28;
    short unk_2C;
    char unk_2E;
    char unk_2F;
    char unk_30;
    char unk_31;
    char pad_32[0x34 - 0x32];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    short unk_54;
    char unk_56;
    char unk_57;
    int unk_58;
    char unk_5C;
    char unk_5D;
    char pad_5E[0x60 - 0x5e];
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
};

struct UnkStruct_020bf924 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    char pad_10[0x24 - 0x10];
    int unk_24;
    char pad_28[0x4c - 0x28];
    int unk_4C;
    int unk_50;
    unsigned short unk_54;
};

extern void func_020bf590(void *);
extern void func_0208a1f8(void *p);

void func_020bf948(struct UnkStruct_020bf948 *s);
void func_020bf924(struct UnkStruct_020bf924 *p);

void func_020bf9cc(void *argument0)
{
    func_020bf590((void *) argument0);
}

void *func_020bf9ac(void *p)
{
    func_0208a1f8((char *) p + 16);
    func_020bf948((struct UnkStruct_020bf948 *) p);
    func_020bf924((struct UnkStruct_020bf924 *) p);
    return p;
}

void func_020bf948(struct UnkStruct_020bf948 *s)
{
    s->unk_4C = 0x1000;
    s->unk_50 = 0x1000;
    s->unk_34 = 0;
    s->unk_38 = 0;
    s->unk_3C = 0;
    s->unk_40 = 0;
    s->unk_44 = 0;
    s->unk_48 = 0;
    s->unk_54 = 0;
    s->unk_28 = 0;
    s->unk_2C = 0;
    s->unk_2E = 1;
    s->unk_2F = 0;
    s->unk_30 = 0;
    s->unk_31 = 0;
    s->unk_56 = 0;
    s->unk_57 = 0;
    s->unk_58 = -1;
    s->unk_5C = 0;
    s->unk_5D = -1;
    s->unk_60 = 0;
    s->unk_64 = 0;
    s->unk_68 = 0;
    s->unk_6C = 0;
    s->unk_70 = 0;
}

void func_020bf924(struct UnkStruct_020bf924 *p)
{
    p->unk_00 = 0xd;
    p->unk_04 = 0;
    p->unk_08 = 0x34;
    p->unk_0C = 0x2e;
    p->unk_24 = 5;
    p->unk_4C = 0x1000;
    p->unk_50 = 0x1000;
    p->unk_54 = 0;
}
