/* event_kinds: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203e740 @ 0x0203e740, 0x10 bytes, Thumb
 * func_0203e704 @ 0x0203e704, 0x3c bytes, Thumb
 * func_0203e6dc @ 0x0203e6dc, 0x28 bytes, Thumb
 * func_0203e6cc @ 0x0203e6cc, 0xe bytes, Thumb
 * func_0203e6b4 @ 0x0203e6b4, 0x18 bytes, Thumb
 * func_0203e68c @ 0x0203e68c, 0x28 bytes, Thumb
 * func_0203e67c @ 0x0203e67c, 0xe bytes, Thumb
 * func_0203e674 @ 0x0203e674, 0x8 bytes, Thumb
 * func_0203e664 @ 0x0203e664, 0xe bytes, Thumb
 * func_0203e648 @ 0x0203e648, 0x1c bytes, Thumb
 * func_0203e644 @ 0x0203e644, 0x4 bytes, Thumb
 * func_0203e640 @ 0x0203e640, 0x4 bytes, Thumb
 * func_0203e63c @ 0x0203e63c, 0x4 bytes, Thumb
 */

typedef struct {
    char pad_00[0x16];
    unsigned char unk_16;
} UnkStruct_0203e6cc;

typedef struct {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
} UnkStruct_0203e67c;

extern void func_0203f364(void);
extern int func_0203e340(void);
extern unsigned char data_021c75b8;
extern int func_02095d84(void);
extern int func_02095904(void);
extern int func_02095bdc(void);
extern int func_02095d04(void);
extern int func_ov004_0222bfb4(void);
extern int func_02095f08(int);

int func_0203e740(void)
{
    func_0203f364();
    return 1;
}

int func_0203e704(unsigned char *param)
{
    if (func_0203e340() != 0) {
        return 0;
    }
    {
        unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
        if (flag == 0) {
            return 0;
        } else {
            if (param[0x17] != 6) {
                return 0;
            }
            return 1;
        }
    }
}

int func_0203e6dc(void *arg0)
{
    int val;
    int val2;

    val = func_02095d84();
    if (val == 0) {
        return 0;
    }
    val2 = func_02095904();
    if (val2 == 0) {
        return 0;
    }
    *(unsigned char *) ((int) arg0 + 0x16) = 5;
    return 1;
}

int func_0203e6cc(UnkStruct_0203e6cc *s)
{
    if (s->unk_16 == 6) {
        return 1;
    } else {
        return 0;
    }
}

int func_0203e6b4(void)
{
    int result;
    if (func_02095bdc() != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_0203e68c(unsigned char *arg0)
{
    int result;

    if (func_02095d04() == 0) {
        result = 0;
    } else {
        if (func_ov004_0222bfb4() == 0) {
            result = 0;
        } else {
            arg0[0x16] = 5;
            result = 1;
        }
    }
    return result;
}

int func_0203e67c(UnkStruct_0203e67c *s)
{
    return s->unk_16 == 6;
}

int func_0203e674(unsigned char *p0)
{
    p0[22] = 5;
    return 1;
}

int func_0203e664(unsigned char *ptr)
{
    if (ptr[22] == 6) {
        return 1;
    }
    return 0;
}

int func_0203e648(unsigned char *p)
{
    if (p[0x16] == 6) {
        func_02095f08(0);
        return 1;
    }
    return 0;
}

int func_0203e644(void)
{
    return 0;
}

int func_0203e640(void)
{
    return 1;
}

int func_0203e63c(void)
{
    return 0;
}
