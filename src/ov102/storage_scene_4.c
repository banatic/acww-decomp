/* storage_scene_4: 21 functions, module ov102
 * mwccarm 1.2/base -O4,s
 * func_ov102_0229d0b0 @ 0x0229d0b0, 0x3a bytes, Thumb
 * func_ov102_0229d074 @ 0x0229d074, 0x3a bytes, Thumb
 * func_ov102_0229d034 @ 0x0229d034, 0x40 bytes, Thumb
 * func_ov102_0229cff8 @ 0x0229cff8, 0x3a bytes, Thumb
 * func_ov102_0229cfdc @ 0x0229cfdc, 0x1c bytes, Thumb
 * func_ov102_0229cf90 @ 0x0229cf90, 0x4c bytes, Thumb
 * func_ov102_0229cf74 @ 0x0229cf74, 0x1c bytes, Thumb
 * func_ov102_0229cf3c @ 0x0229cf3c, 0x36 bytes, Thumb
 * func_ov102_0229cef8 @ 0x0229cef8, 0x44 bytes, Thumb
 * func_ov102_0229ce58 @ 0x0229ce58, 0xa0 bytes, Thumb
 * func_ov102_0229cdf4 @ 0x0229cdf4, 0x64 bytes, Thumb
 * func_ov102_0229cdb8 @ 0x0229cdb8, 0x3c bytes, Thumb
 * func_ov102_0229cd80 @ 0x0229cd80, 0x38 bytes, Thumb
 * func_ov102_0229cd38 @ 0x0229cd38, 0x48 bytes, Thumb
 * func_ov102_0229cd08 @ 0x0229cd08, 0x30 bytes, Thumb
 * func_ov102_0229cc90 @ 0x0229cc90, 0x78 bytes, Thumb
 * func_ov102_0229cc60 @ 0x0229cc60, 0x30 bytes, Thumb
 * func_ov102_0229cc24 @ 0x0229cc24, 0x3c bytes, Thumb
 * func_ov102_0229cbcc @ 0x0229cbcc, 0x58 bytes, Thumb
 * func_ov102_0229cb84 @ 0x0229cb84, 0x48 bytes, Thumb
 * func_ov102_0229cb74 @ 0x0229cb74, 0x10 bytes, Thumb
 */

typedef struct UnkStruct_0229cdf4 {
    char pad_00[0x218c];
    char sub[0x415];
    unsigned char unk_25A1;
    char pad_25A2[3];
    unsigned char unk_25A5;
} UnkStruct_0229cdf4;

typedef struct {
    char pad_00[0x225c];
    char unk_225C;
    char pad_225D[0x24e0 - 0x225c - 1];
    int unk_24E0;
    int unk_24E4;
} UnkStruct_0229cd08;

typedef struct UnkStruct_0229cc90 {
    char pad_00[0xcc];
    int sub;
    char pad_D0[0x259c - 0xd0];
    unsigned short unk_259C;
    unsigned char unk_259E;
    unsigned char unk_259F;
} UnkStruct_0229cc90;

typedef struct {
    char pad_00[0x259c];
    unsigned short unk_259C;
    unsigned char unk_259E;
    unsigned char flag;
} UnkStruct_0229cc60;

struct UnkStruct_0229cb84 {
    char pad_00[0x25a5];
    unsigned char byte;
};

extern int func_ov102_0229d464(void *, int);
extern int func_ov102_0229d454(void *, int);
extern int func_ov102_0229d400(void *, int);
extern int func_ov094_0229a8bc(void *, int);
extern int func_ov094_0229a69c(void *a, int b);
extern int func_ov094_0229aaac(int, int);
extern int func_ov094_0229aa84(void *p, int v);
extern void func_ov094_0229ab5c(void *p);
extern void func_ov094_0229b98c(void *p);
extern void func_ov094_0229ab1c(unsigned char *p, int v);
extern void func_ov094_0229ab0c(void *);
extern void func_ov094_0229b944(void *);
extern void func_ov094_0229aafc(void *self_plus, int value);
extern unsigned char data_021f6c60;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c54;
extern int func_ov102_0229d1e8(void *, unsigned char);
extern int func_ov102_0229d178(void *, unsigned char);
extern int func_0206fe54(void);
extern void func_0208aa80(void *);
extern void func_0208aa78(void *);
extern void func_0208aa60(void *, int, int);
extern void func_ov094_0229abb8(void *, void *, int);
extern void func_ov002_02207cf0(char *sub);
extern void func_ov002_02207cf8(char *sub);
extern int func_ov102_0229c2a8(void *p, int arg);
extern void func_ov094_0229a6bc(void *p, int a, int b);
extern int func_ov002_02209f3c(char *);
extern int func_ov002_02209f14(char *);
extern int func_0208e4bc(char *);
extern int func_ov002_02209d84(void *p);
extern int func_ov002_02209d7c(void *p);
extern void func_ov094_0229aa58(void *sub, int x);
extern void func_ov094_0229a99c(void *sub, int arg2, int arg3);
extern void func_ov102_0229d2a4(void *s, int param2, unsigned short f1, unsigned char f2);
extern void func_ov002_0220a0b4(void *, int, int);
extern int func_ov102_0229d438(void *, unsigned char);
extern void func_ov002_0220a374(void *, int);
extern void func_ov102_0229ca98(void *);

int func_ov102_0229cb84(struct UnkStruct_0229cb84 *self);
int func_ov102_0229cb74(void *p);

int func_ov102_0229d0b0(char *arg0, int arg1)
{
    if (func_ov102_0229d464(arg0, arg1) != 0 || func_ov102_0229d454(arg0, arg1) != 0) {
        int c = func_ov102_0229d400(arg0, arg1);
        return func_ov094_0229a8bc(arg0 + 0xcc, c);
    } else {
        return 0;
    }
}

int func_ov102_0229d074(void *arg1, int arg2)
{
    if (func_ov102_0229d464(arg1, arg2) || func_ov102_0229d454(arg1, arg2)) {
        int temp = func_ov102_0229d400(arg1, arg2);
        arg1 = (char *) arg1 + 0xcc;
        return func_ov094_0229a69c(arg1, temp);
    }
    return 1;
}

int func_ov102_0229d034(int a, int b)
{
    int result;

    if (func_ov102_0229d464((void *) a, b) || func_ov102_0229d454((void *) a, b)) {
        result = func_ov094_0229aaac(a + 0xcc, func_ov102_0229d400((void *) a, b));
    } else {
        result = 0xfff1;
    }
    return result;
}

int func_ov102_0229cff8(void *p, int q)
{
    if (func_ov102_0229d464(p, q) != 0 || func_ov102_0229d454(p, q) != 0) {
        return func_ov094_0229aa84((char *) p + 0xcc, func_ov102_0229d400(p, q));
    } else {
        return 0xf1;
    }
}

void func_ov102_0229cfdc(void *self)
{
    func_ov094_0229ab5c((char *) self + 0xcc);
    func_ov094_0229b98c((char *) self + 0xb2c);
}

void func_ov102_0229cf90(unsigned char *arg0, unsigned char *arg1)
{
    if (func_ov102_0229d464((void *) arg0, (int) arg1) || func_ov102_0229d454((void *) arg0, (int) arg1)) {
        int v = func_ov102_0229d400((void *) arg0, (int) arg1);
        func_ov094_0229ab1c(arg0 + 0xcc, v);
        func_ov094_0229b98c((void *) (arg0 + 0xb2c));
    } else {
        func_ov102_0229cfdc((void *) arg0);
    }
}

void func_ov102_0229cf74(void *self)
{
    func_ov094_0229ab0c((char *) self + 0xcc);
    func_ov094_0229b944((char *) self + 0xb2c);
}

void func_ov102_0229cf3c(void *self, void *other)
{
    if (func_ov102_0229d464(self, (int) other) != 0 || func_ov102_0229d454(self, (int) other) != 0) {
        func_ov094_0229aafc((char *) self + 0xcc, func_ov102_0229d400(self, (int) other));
    }
}

int func_ov102_0229cef8(void *self)
{
    int diff1;
    int diff2;

    diff1 = data_021f6c60 - data_021f6c58;
    if (diff1 < 0) {
        diff1 = -diff1;
    }
    if (diff1 > 8) {
        return 1;
    }

    diff2 = data_021f6c5c - data_021f6c54;
    if (diff2 < 0) {
        diff2 = -diff2;
    }
    if (diff2 > 8) {
        return 1;
    }

    return 0;
}

void func_ov102_0229ce58(unsigned char *self)
{
    int r6, r4;

    r6 = func_ov102_0229d1e8(self, *(unsigned char *) (self + 0x25a1)) - 0x6d;
    r4 = func_ov102_0229d178(self, *(unsigned char *) (self + 0x25a1)) - 0x78;

    if (func_0206fe54() != 0) {
        r4 -= 8;
    }

    if (r4 < -92) {
        func_0208aa80(self + 0x218c);
        r4 = func_ov102_0229d178(self, *(unsigned char *) (self + 0x25a1)) - 0x50;
    } else {
        func_0208aa78(self + 0x218c);
    }

    func_0208aa60(self + 0x218c, r6, r4);

    if (func_ov102_0229d464(self, (unsigned char) (*(unsigned char *) (self + 0x25a1))) != 0 ||
        func_ov102_0229d454(self, (unsigned char) (*(unsigned char *) (self + 0x25a1))) != 0) {
        int tmp = func_ov102_0229d400(self, (unsigned char) (*(unsigned char *) (self + 0x25a1)));
        func_ov094_0229abb8(self + 0xcc, self + 0x218c, tmp);
    }
}

void func_ov102_0229cdf4(UnkStruct_0229cdf4 *obj)
{
    if (func_ov102_0229d464((void *) obj, (unsigned char) obj->unk_25A5) != 0 ||
        func_ov102_0229d454((void *) obj, (unsigned char) obj->unk_25A5) != 0) {
        if (func_ov102_0229d074((void *) obj, (unsigned char) obj->unk_25A5) != 0) {
            func_ov002_02207cf0(obj->sub);
        } else {
            obj->unk_25A1 = obj->unk_25A5;
            func_ov002_02207cf8(obj->sub);
        }
    } else {
        func_ov002_02207cf0(obj->sub);
    }
}

void func_ov102_0229cdb8(char *param)
{
    unsigned char b;

    if (func_ov102_0229c2a8(param, 0x40) != 0) {
        return;
    }

    b = *(unsigned char *) (param + 0x259f);
    if (b != 0 && b == 1) {
        func_ov094_0229a6bc(param + 0xcc, *(int *) (param + 0x24e0), *(int *) (param + 0x24e4));
    }
}

void func_ov102_0229cd80(int *r0)
{
    int r2;
    int r1;

    r2 = *(int *) ((char *) r0 + 0x24d8);
    r1 = data_021f6c58;
    r2 += r1;
    *(int *) ((char *) r0 + 0x24e0) = r2;

    r2 = *(int *) ((char *) r0 + 0x24dc);
    r1 = data_021f6c54;
    r2 += r1;
    *(int *) ((char *) r0 + 0x24e4) = r2;
}

void func_ov102_0229cd38(char *obj)
{
    *(int *) (obj + 0x24e0) = func_ov002_02209f3c(obj + 0x2274) - 2;
    *(int *) (obj + 0x24e4) = func_ov002_02209f14(obj + 0x2274) - 4;
    if (func_0208e4bc(obj + 0x2274) == 1) {
        *(int *) (obj + 0x24e4) -= 22;
    }
}

void func_ov102_0229cd08(UnkStruct_0229cd08 *obj)
{
    obj->unk_24E0 = func_ov002_02209d84(&obj->unk_225C);
    obj->unk_24E4 = func_ov002_02209d7c(&obj->unk_225C);
}

void func_ov102_0229cc90(UnkStruct_0229cc90 *a, void *b)
{
    int x;
    if (func_ov102_0229d464(a, (int) b) != 0 || func_ov102_0229d454(a, (int) b) != 0) {
        x = func_ov102_0229d400(a, (int) b);
        a->unk_259F = 1;
        a->unk_259C = func_ov094_0229aaac((int) (&a->sub), x);
        a->unk_259E = func_ov094_0229aa84(&a->sub, x);
        func_ov094_0229aa58(&a->sub, x);
        func_ov094_0229a99c(&a->sub, a->unk_259C, a->unk_259E);
    }
}

void func_ov102_0229cc60(UnkStruct_0229cc60 *s, int param2)
{
    if (s->flag == 1) {
        func_ov102_0229d2a4(s, param2, s->unk_259C, s->unk_259E);
    }
    s->flag = 0;
}

void func_ov102_0229cc24(unsigned char *self, int param)
{
    if (self[0x259f] == 1) {
        unsigned short field_a = *(unsigned short *) (self + 0x259c);
        unsigned char field_b = self[0x259e];
        func_ov102_0229cc90((UnkStruct_0229cc90 *) self, (void *) param);
        func_ov102_0229d2a4(self, param, field_a, field_b);
    }
}

void func_ov102_0229cbcc(unsigned char *self)
{
    int a;
    int b;

    a = func_ov102_0229cb84((struct UnkStruct_0229cb84 *) self);
    b = func_ov102_0229cb74(self);
    func_ov002_0220a0b4(self + 0x2274, a, b);
    if (func_ov102_0229d438(self, self[0x25a5]) != 0) {
        func_ov002_0220a374(self + 0x2274, 7);
    } else {
        func_ov002_0220a374(self + 0x2274, 1);
    }
    func_ov102_0229ca98(self);
}

int func_ov102_0229cb84(struct UnkStruct_0229cb84 *self)
{
    int result = func_ov102_0229d1e8((void *) self, self->byte);
    if (func_ov102_0229c2a8((void *) self, 0x20)) {
        result += 0x100;
    } else if (func_ov102_0229c2a8((void *) self, 0x10)) {
        result -= 0x100;
    }
    result += 8;
    return result;
}

int func_ov102_0229cb74(void *p)
{
    return func_ov102_0229d178(p, ((unsigned char *) p)[0x25A5]);
}
