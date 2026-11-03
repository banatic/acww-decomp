/* event_kinds_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203e904 @ 0x0203e904, 0x34 bytes, Thumb
 * func_0203e8c0 @ 0x0203e8c0, 0x42 bytes, Thumb
 * func_0203e89c @ 0x0203e89c, 0x24 bytes, Thumb
 * func_0203e860 @ 0x0203e860, 0x3c bytes, Thumb
 */

struct UnkStruct_0203e904;

struct UnkStruct_0203e904 {
    char pad_00[12];
    int unk_0C;
    char pad_10[7];
    unsigned char unk_17;
};

struct UnkStruct_0203e8c0 {
    unsigned char pad_00[0x10];
    unsigned int unk_10;
    unsigned char pad_14[2];
    unsigned char state;
    unsigned char unk_17;
};

struct UnkStruct_0203e860 {
    unsigned char pad_00[0xC];
    int unk_0C;
    unsigned char pad_10[7];
    unsigned char unk_17;
};

extern int func_0203ef90(int arg);
extern int func_02095d84(void);
extern int func_0203eb08(struct UnkStruct_0203e904 *s);
extern int func_02095904(void);
extern int func_02096174(void);
extern void func_0203ead0(int, unsigned char);
extern int func_02095bdc(void);
extern void func_0203ea80(int, int);
extern void func_0203f364(void);
extern int func_02095f28(void);
extern int func_02095f08(int arg);

int func_0203e904(struct UnkStruct_0203e904 *s)
{
    if ((func_0203ef90(s->unk_0C), func_02095d84()) == 0) {
        return 0;
    }
    s->unk_17 = 1;
    if (func_0203eb08(s) != 0) {
        func_02095904();
        return 1;
    } else {
        return 0;
    }
}

int func_0203e8c0(struct UnkStruct_0203e8c0 *p)
{
    int r = func_0203ef90(p->unk_10);
    switch (p->state) {
        case 4:
            if (func_02096174() != 0) {
                func_0203ead0(r, p->unk_17);
                p->state = 5;
            }
            break;
        case 5:
            break;
        case 6:
            return 1;
    }
    return 0;
}

int func_0203e89c(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    if (func_02095bdc() != 0) {
        func_0203ea80(r4, 8);
        func_0203f364();
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_0203e860(struct UnkStruct_0203e860 *arg)
{
    int result1;

    result1 = func_0203ef90(arg->unk_0C);
    if (result1 == 0) {
        return 0;
    }
    if (func_02095f28() == 0) {
        return 0;
    }
    if (func_02095f08(1) == 0) {
        return 0;
    }
    arg->unk_17 = 1;
    return func_0203eb08((struct UnkStruct_0203e904 *) arg);
}
