/* insurer_4: 9 functions, module ov071
 * mwccarm 1.2/base -O4,s
 * func_ov071_02279c54 @ 0x02279c54, 0xb0 bytes, Thumb
 * func_ov071_02279c18 @ 0x02279c18, 0x3c bytes, Thumb
 * func_ov071_02279c08 @ 0x02279c08, 0xe bytes, Thumb
 * func_ov071_02279c04 @ 0x02279c04, 0x4 bytes, Thumb
 * func_ov071_02279bd8 @ 0x02279bd8, 0x2c bytes, Thumb
 * func_ov071_02279b9c @ 0x02279b9c, 0x3c bytes, Thumb
 * func_ov071_02279b98 @ 0x02279b98, 0x4 bytes, Thumb
 * func_ov071_02279b6c @ 0x02279b6c, 0x2c bytes, Thumb
 * func_ov071_02279b2c @ 0x02279b2c, 0x40 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02279c54;

typedef struct UnkStruct_02279bd8 {
    unsigned char pad_00[0x618];
    char unk_618;
} UnkStruct_02279bd8;

struct UnkStruct_02279b2c {
    unsigned char pad_00[0x734];
    int unk_734;
};

extern int data_021c67a4;
extern int data_021c67d0[3];
extern int func_02014868(void *ptr);
extern int func_0203e020(void *ptr);
extern void func_ov071_02279d04(void *ptr, int value);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int a);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_020ea9e4(void *a, void *b);
extern int func_0201c390(struct UnkStruct_02279b2c *obj, int value);
extern int func_0201c2b0(struct UnkStruct_02279b2c *obj, int value);
extern signed short data_ov071_0227a340[];

int func_ov071_02279c54(int unused, UnkStruct_02279c54 *a, UnkStruct_02279c54 *b, int mode)
{
    int ret, c2, c1;

    if (mode == 0) {
        ret = 0;
        c2 = 0;
        c1 = 0;
        if (b->unk_00 > a->unk_00 - 0x8000) {
            if (b->unk_00 < a->unk_00 + 0x8000) {
                c1 = 1;
            }
        }
        if (c1 != 0) {
            if (b->unk_08 > a->unk_08 - 0xc000) {
                c2 = 1;
            }
        }
        if (c2 != 0) {
            if (b->unk_08 < a->unk_08 + 0x6000) {
                ret = 1;
            }
        }
    } else {
        ret = 0;
        c2 = 0;
        c1 = 0;
        if (b->unk_00 > a->unk_00 - 0x10000) {
            if (b->unk_00 < a->unk_00 + 0x10000) {
                c1 = 1;
            }
        }
        if (c1 != 0) {
            if (b->unk_08 > a->unk_08 - 0x1a000) {
                c2 = 1;
            }
        }
        if (c2 != 0) {
            if (b->unk_08 < a->unk_08 + 0xa000) {
                ret = 1;
            }
        }
    }
    return ret;
}

int func_ov071_02279c18(void *a, void *b)
{
    int local[4];
    void *p = (char *) a + 0x5c;
    int result = 0;
    if (data_021c67a4) {
        local[0] = data_021c67d0[0];
        local[1] = data_021c67d0[1];
        local[2] = data_021c67d0[2];
        result = func_ov071_02279c54((int) a, (UnkStruct_02279c54 *) local, (UnkStruct_02279c54 *) p, (int) b);
    }
    return result;
}

int func_ov071_02279c08(int a, int *b)
{
    if (*b) {
        (*b)--;
    }
    return *b;
}

int func_ov071_02279c04(void)
{
    return 1;
}

int func_ov071_02279bd8(UnkStruct_02279bd8 *self)
{
    if (func_02014868(&self->unk_618) == 0) {
        func_0203e020(self);
        func_ov071_02279d04(self, 2);
    }
    return 1;
}

int func_ov071_02279b9c(char *self)
{
    int size;
    int s;

    size = func_02016104(self + 0x658);
    s = *(short *) (self + 0x8e);

    if (size != 0) {
        s = func_0201c314(self, size);
    }

    func_020147fc(self + 0x618, 0, s, 0);
    return 1;
}

int func_ov071_02279b98(void)
{
    return 1;
}

int func_ov071_02279b6c(void *self)
{
    if (func_020ea9e4((char *) self + 0x5c, (char *) self + 0x738) > 0xc000) {
        return 0;
    }
    return 1;
}

int func_ov071_02279b2c(struct UnkStruct_02279b2c *obj, int param2)
{
    int i = 0;
    if (func_0201c390(obj, obj->unk_734) > param2) {
        goto out;
    }
    {
        int r = func_0201c2b0(obj, obj->unk_734);
        int t = data_ov071_0227a340[i];
        if (r < -t) {
            goto out;
        }
        if (r > t) {
            goto out;
        }
    }
    i = 1;
out:
    return i;
}
