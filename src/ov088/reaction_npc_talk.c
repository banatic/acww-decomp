/* reaction_npc_talk: 5 functions, module ov088
 * mwccarm 1.2/base -O4,s
 * func_ov088_02278d54 @ 0x02278d54, 0xd4 bytes, Thumb
 * func_ov088_02278d28 @ 0x02278d28, 0x2c bytes, Thumb
 * func_ov088_02278d10 @ 0x02278d10, 0x18 bytes, Thumb
 * func_ov088_02278cf8 @ 0x02278cf8, 0x18 bytes, Thumb
 * func_ov088_02278cd8 @ 0x02278cd8, 0x20 bytes, Thumb
 */

typedef struct Work Work;

typedef struct UnkStruct_02278d54 UnkStruct_02278d54;

struct Work {
    /* 0x00 */ char pad_00[4];
    /* 0x04 */ int state;
};

struct UnkStruct_02278d54 {
    /* 0x00 */ char pad_00[0x40];
    /* 0x40 */ Work *work;
    /* 0x44 */ char pad_44[0x74];
    /* 0xb8 */ unsigned char *str;
    /* 0xbc */ unsigned char flag;
};

typedef struct UnkStruct_02278d28 {
    unsigned char pad_00[0xb8];
    unsigned int unk_B8;
} UnkStruct_02278d28;

extern int func_02013a94(void *);
extern int func_020e8858(void *);
extern int func_0202ea80(int, int);
extern int func_0203fa4c(void);
extern int func_020683e4(void *, int, void *, const void *);
extern void func_0206844c(void *, void *, const void *);
extern void func_ov088_02278f0c(void *, int);
extern const char data_ov088_02279da8[];
extern const char data_ov088_02279d98[];
extern int func_020155cc(UnkStruct_02278d28 *p);
extern void *func_0202eb70(void *);
extern char data_ov088_02279c58;
extern void *func_0202eb20(void *);
extern void func_020edb3c(void *);

void func_ov088_02278d54(UnkStruct_02278d54 *p)
{
    Work *work;
    unsigned char stack[2];

    work = p->work;
    if (work->state != 5) {
        return;
    }

    if (p->str[0x739] == 0) {
        p->str[0x739] = 0x34;
    }

    if (func_02013a94(p->str) == -1) {
        if ((unsigned) func_020e8858(p->str + 0x739) > 2) {
            return;
        }
    }

    stack[0] = 0x19;
    if (p->str[0x739] > 2) {
        goto larger;
    }
    stack[0] = 0x18;
    goto done;
larger:
    func_0202ea80(0xe, 1);
    if (func_0203fa4c() == -1) {
        stack[0] = 0x1a;
    }
done:
    stack[1] = p->flag;
    func_020683e4(p->work, 0, &stack[1], data_ov088_02279da8);

    p->str[0x739] = 0;
    p->str[0x738] = 0x14;

    func_0206844c(work, stack, data_ov088_02279d98);

    func_ov088_02278f0c(p, 4);
}

void func_ov088_02278d28(UnkStruct_02278d28 *p)
{
    if (func_020e8858((void *) (p->unk_B8 + 0x738)) == 0) {
        func_ov088_02278f0c((void *) p, 0);
        func_020155cc(p);
    }
}

void *func_ov088_02278d10(void *p)
{
    func_0202eb70(p);
    *(void **) p = &data_ov088_02279c58;
    return p;
}

void *func_ov088_02278cf8(void *self)
{
    *(void **) self = &data_ov088_02279c58;
    func_0202eb20(self);
    return self;
}

void *func_ov088_02278cd8(void *self)
{
    *(void **) self = (void *) ((int *) &data_ov088_02279c58);
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
