/* map_menu_list_3: 5 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229ae0c @ 0x0229ae0c, 0x58 bytes, Thumb
 * func_ov118_0229adf0 @ 0x0229adf0, 0x1c bytes, Thumb
 * func_ov118_0229ade0 @ 0x0229ade0, 0x10 bytes, Thumb
 * func_ov118_0229add4 @ 0x0229add4, 0xc bytes, Thumb
 * func_ov118_0229ad24 @ 0x0229ad24, 0xb0 bytes, Thumb
 */

struct func_ov118_0229ae0c_obj {
    unsigned char pad_00[0x98];
    unsigned short unk_98;
    unsigned char pad_9A[0x10];
    unsigned char unk_AA;
};

typedef struct {
    char pad_00[0x98];
    unsigned short unk_98;
    unsigned short unk_9A;
} FuncoV118;

struct UnkStruct_0229ad24 {
    char pad_00[0x98];
    unsigned short unk_98;
    unsigned short unk_9A;
    char pad_9C[0xa4 - 0x9c];
    unsigned char unk_A4;
};

extern void func_ov118_0229a450(void *self, int flag);
extern int func_ov118_0229a460(int arg0, int arg1);
extern int func_ov118_0229b374(void *arg0);
extern void func_ov118_0229a440(void *obj, int arg);
extern int _s32_div_f(int a, int b);

void func_ov118_0229ade0(int p0, int p1);

void func_ov118_0229ae0c(struct func_ov118_0229ae0c_obj *self)
{
    unsigned char b;
    int t;
    int h;
    int k;
    unsigned char b2;

    b = self->unk_AA;
    if (b == 14) {
        return;
    }

    if (b == 13) {
        func_ov118_0229ade0((int) self, 0);
        return;
    }

    t = (self->unk_98 + 15) >> 4;
    if (b < t) {
        func_ov118_0229ade0((int) self, b << 4);
    }

    h = self->unk_98 >> 4;
    b2 = self->unk_AA;
    if (b2 <= 5) {
        k = 0;
    } else {
        k = b2 - 5;
    }

    if (h < k) {
        func_ov118_0229ade0((int) self, k << 4);
    }
}

void func_ov118_0229adf0(FuncoV118 *self, unsigned short value)
{
    unsigned short tmp;
    self->unk_98 = value;
    tmp = self->unk_98;
    self->unk_9A = tmp;
    func_ov118_0229a450(self, 0x10);
}

void func_ov118_0229ade0(int p0, int p1)
{
    *(unsigned short *) ((char *) (((int) (p0) + (154))) + (0)) = p1;
    func_ov118_0229a450((void *) p0, 16);
}

int func_ov118_0229add4(int arg0)
{
    return func_ov118_0229a460(arg0, 0x10);
}

void func_ov118_0229ad24(struct UnkStruct_0229ad24 *obj)
{
    int r4 = func_ov118_0229b374((void *) obj);

    if (r4 == 0) {
        func_ov118_0229a440(obj, 0x10);
        obj->unk_A4 = 0;
        return;
    }

    if (obj->unk_98 == obj->unk_9A) {
        func_ov118_0229a440(obj, 0x10);
    } else if (obj->unk_98 < obj->unk_9A) {
        obj->unk_98 += 8;
        if (obj->unk_98 > obj->unk_9A) {
            obj->unk_98 = obj->unk_9A;
        }
    } else if (obj->unk_98 < 8) {
        obj->unk_98 = obj->unk_9A;
    } else {
        obj->unk_98 -= 8;
        if (obj->unk_98 < obj->unk_9A) {
            obj->unk_98 = obj->unk_9A;
        }
    }

    obj->unk_A4 = (unsigned char) _s32_div_f(obj->unk_98 * 0x58, r4);
}
