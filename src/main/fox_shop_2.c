/* fox_shop_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ae64c @ 0x020ae64c, 0x30 bytes, Thumb
 * func_020ae614 @ 0x020ae614, 0x38 bytes, Thumb
 * func_020ae5f4 @ 0x020ae5f4, 0x20 bytes, Thumb
 * func_020ae5bc @ 0x020ae5bc, 0x38 bytes, Thumb
 * func_020ae590 @ 0x020ae590, 0x2c bytes, Thumb
 * func_020ae56c @ 0x020ae56c, 0x24 bytes, Thumb
 * func_020ae564 @ 0x020ae564, 0x6 bytes, Thumb
 * func_020ae538 @ 0x020ae538, 0x2a bytes, Thumb
 * func_020ae514 @ 0x020ae514, 0x22 bytes, Thumb
 * func_020ae4fc @ 0x020ae4fc, 0x16 bytes, Thumb
 * func_020ae4f0 @ 0x020ae4f0, 0xc bytes, Thumb
 */

struct UnkStruct_020ae64c {
    int unk_00;
    char unk_04;
};

typedef struct {
    char pad_00[4];
    signed char v;
} UnkStruct_020ae5f4;

typedef struct {
    unsigned char pad_00[5];
    unsigned char unk_05;
} UnkStruct_020ae564;

struct UnkStruct_020ae514 {
    char pad_00[4];
    signed char unk_04;
    unsigned char unk_05;
};

struct UnkStruct_020ae4fc {
    unsigned char pad_00[5];
    unsigned char flags;
};

extern int func_020ae470(struct UnkStruct_020ae64c *p);
extern void func_0209f100(void *p, int n);
extern int func_020b49d4(const char *a, const char *b, const void *c);
extern char data_020e41ac;
extern int func_0209f150(void *, int);
extern void func_0209f128(void *param1, int param2);
extern unsigned char data_021dc7a8[];
extern char data_021f49e8;

void func_020ae564(UnkStruct_020ae564 *p);

int func_020ae64c(struct UnkStruct_020ae64c *p)
{
    p->unk_04 = -1;
    if (func_020ae470(p) == 0) {
        p->unk_00 = 0;
    }
    func_020ae564((UnkStruct_020ae564 *) p);
    func_0209f100(((int *) data_021dc7a8), 8);
    return 1;
}

int func_020ae614(volatile signed char *p, const char *q)
{
    char local;
    if (p[4] == -1) {
        goto ret0;
    }
    local = (p[4] & 0x1f) << 1;
    return func_020b49d4(q, &local, &data_020e41ac);
ret0:
    return 0;
}

int func_020ae5f4(volatile UnkStruct_020ae5f4 *self)
{
    if (self->v == -1) {
        return 0;
    }
    return (unsigned char) (self->v * 2 + 1);
}

int func_020ae5bc(volatile signed char *p, const char *q)
{
    char local;
    if (p[4] == -1) {
        goto ret0;
    }
    local = ((p[4] & 0x1f) << 1) + 1;
    return func_020b49d4(q, &local, &data_020e41ac);
ret0:
    return 0;
}

int func_020ae590(signed char *s)
{
    if (s[4] != -1) {
        if (func_0209f150(((int *) data_021dc7a8), 8) == 0) {
            return 1;
        }
    }
    return 0;
}

void func_020ae56c(void *param0)
{
    signed char c;
    void *addr;

    c = *(signed char *) ((char *) param0 + 4);
    if (c != -1) {
        addr = (void *) data_021dc7a8;
        func_0209f128(addr, 8);
    }
}

void func_020ae564(UnkStruct_020ae564 *p)
{
    p->unk_05 = 0;
}

int func_020ae538(unsigned char *p, int index)
{
    int result;
    if ((signed char) p[4] != -1) {
        result = ((p[5] >> (index & 3)) & 1) != 0;
    } else {
        result = 0;
    }
    return result;
}

void func_020ae514(struct UnkStruct_020ae514 *obj, int param)
{
    if (obj->unk_04 != -1) {
        obj->unk_05 |= (1 << (param & 3));
    }
}

void func_020ae4fc(struct UnkStruct_020ae4fc *p, int shift)
{
    p->flags &= ~(1 << (shift & 3));
}

void func_020ae4f0(void)
{
    data_021f49e8 = 0;
}
