/* scene_motion_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02017310 @ 0x02017310, 0x60 bytes, Thumb
 * func_020172d8 @ 0x020172d8, 0x36 bytes, Thumb
 * func_02017258 @ 0x02017258, 0x80 bytes, Thumb
 * func_02017224 @ 0x02017224, 0x32 bytes, Thumb
 * func_0201709c @ 0x0201709c, 0x188 bytes, Thumb
 * func_02016f30 @ 0x02016f30, 0x16c bytes, Thumb
 */

struct UnkStruct_020172d8 {
    unsigned char pad_00[0x22];
    unsigned short unk_22;
};

struct UnkStruct_020172d8_2 {
    unsigned char pad_00[0x28];
    int unk_28;
    struct UnkStruct_020172d8 sub;
};

struct Work {
    unsigned char pad_00[0x5c];
    int unk_5C;
    unsigned char pad1[0x64 - 0x60];
    int unk_64;
    unsigned char pad_68[0x8e - 0x68];
    short unk_8E;
};

struct UnkStruct_0201709c {
    int unk_00;
    unsigned char pad1[0x98 - 4];
    unsigned char unk_98;
};

struct UnkStruct_02016f30 {
    int unk_00;
    unsigned char pad1[0x98 - 4];
    unsigned char unk_98;
};

extern int func_020164a0(int, int);
extern int func_020164cc(int, int);
extern void func_02057cb8(int);
extern void func_02016764(int, int, int, int, int, int, int, int);
extern void func_02019af0(int, int);
extern unsigned short data_020c80f8;
extern void func_02019d70(struct UnkStruct_020172d8_2 *s, int a, int b);
extern void func_02019ea0(struct UnkStruct_020172d8 *s);
extern int func_02019de4(void *param1);
extern void func_02012444(int a, unsigned short b, int c);
extern int func_02091230(int a, void *b, int c, int d);
extern int func_0200442c(void *a, int b, int c, int d);
extern int func_02017f1c(int, int, int, int, int);
extern int func_0201bee0(void *, int *, short *);
extern int FX_MulFunc(int, int);
extern int func_020e8ed8(int, int);
extern int func_0201c3dc(int);
extern void func_0201b1a4(void *, void *, int, int, int);
extern void func_0201aff4(void *, int);
extern void func_0201b044(void *, void *);
extern void func_0201afd4(void *, void *);
extern char data_021fbee8[];
extern int func_0201b1a0(void *);

void func_02017310(int param1, int param2)
{
    if (func_020164a0(param2 + 0x334, 0) != 0x2A) {
        return;
    }
    if (func_020164cc(param2 + 0x334, param2) == 0) {
        return;
    }
    func_02057cb8(param2);
    func_02016764(param2 + 0x334, param2, 0, data_020c80f8, 0, 0x1000, 0, 0);
    func_02019af0(param1, 1);
}

int func_020172d8(struct UnkStruct_020172d8_2 *s, int val, unsigned short *src)
{
    int ret = 0;
    if (val >= s->unk_28 || s->unk_28 == 3) {
        struct UnkStruct_020172d8 *sub = &s->sub;
        func_02019d70(s, 0x14, val);
        func_02019ea0(sub);
        sub->unk_22 = *src;
        ret = 1;
    }
    return ret;
}

int func_02017258(void *param1, char *param2)
{
    unsigned short color;
    int obj;

    func_02019de4(param1);
    color = (*(volatile unsigned short *) &data_020c80f8);
    func_02016764((int) (param2 + 0x334), (int) param2, 6, (unsigned short) ((*(volatile unsigned short *) &data_020c80f8)), 1, 0x1000, 0, 0);
    obj = *(int *) (param2 + 0x628);
    if (obj) {
        func_02012444(obj, color, 0);
    }
    func_02091230(0x61, param2 + 0x5c, 0, 0);
    func_0200442c(param2 + 0x514, 0x76, 0x7f, 0);
    func_02019af0((int) param1, 0);
    return 1;
}

void func_02017224(int a, int b)
{
    int t;

    t = func_02019de4((void *) a);
    if (func_02017f1c(a, b, t + 0x22, 6, 0)) {
        func_02019af0(a, 1);
    }
}

int func_0201709c(struct UnkStruct_0201709c *self, struct Work *work)
{
    int coord[3];
    short angle;
    int dx, dy;
    int sum;
    int v;

    coord[0] = 0;
    coord[1] = 0;
    coord[2] = 0;
    angle = work->unk_8E;

    if (func_0201bee0(work, coord, &angle) != 0) {
        dx = coord[0] - work->unk_5C;
        dy = coord[2] - work->unk_64;
        sum = FX_MulFunc(dx, dx) + FX_MulFunc(dy, dy);
        if (sum < 0x29) {
            if (angle != work->unk_8E) {
                func_0201b1a4((char *) work + 0x350, work, 3, 0, data_020c80f8);
                func_0201aff4((char *) work + 0x350, angle);
                self->unk_98 = 2;
            } else {
                func_0201b1a4((char *) work + 0x350, work, 0, 0, data_020c80f8);
                self->unk_98 = 0;
            }
            func_0201b044((char *) work + 0x350, data_021fbee8);
            func_0201afd4((char *) work + 0x350, data_021fbee8);
        } else {
            v = func_020e8ed8(dx, dy);
            if (func_0201c3dc((short) (v - angle)) != 0) {
                if (self->unk_00 == 2) {
                    func_0201b1a4((char *) work + 0x350, work, 2, 0, data_020c80f8);
                } else {
                    func_0201b1a4((char *) work + 0x350, work, 1, 0, data_020c80f8);
                }
                self->unk_98 = 1;
            } else {
                func_0201b1a4((char *) work + 0x350, work, 4, 0, data_020c80f8);
                func_0201aff4((char *) work + 0x350, v);
                self->unk_98 = 3;
            }
            func_0201b044((char *) work + 0x350, coord);
            func_0201afd4((char *) work + 0x350, coord);
        }
    } else {
        func_0201b1a4((char *) work + 0x350, work, 0, 0, data_020c80f8);
        func_0201b044((char *) work + 0x350, data_021fbee8);
        func_0201afd4((char *) work + 0x350, data_021fbee8);
        self->unk_98 = 0;
    }
    return 1;
}

void func_02016f30(struct UnkStruct_02016f30 *self, struct Work *work)
{
    int coord[3];
    short angle;
    int dx, dy;
    int sum;
    int v;

    coord[0] = 0;
    coord[1] = 0;
    coord[2] = 0;
    angle = work->unk_8E;

    if (func_0201bee0(work, coord, &angle) == 0) {
        return;
    }
    dx = coord[0] - work->unk_5C;
    dy = coord[2] - work->unk_64;
    sum = FX_MulFunc(dx, dx) + FX_MulFunc(dy, dy);
    if (sum < 0x29) {
        if (angle != work->unk_8E) {
            func_0201b1a4((char *) work + 0x350, work, 3, 0, data_020c80f8);
            func_0201aff4((char *) work + 0x350, angle);
            self->unk_98 = 2;
            return;
        }
        if (func_0201b1a0((char *) work + 0x350) == 0) {
            return;
        }
        func_0201b1a4((char *) work + 0x350, work, 0, 0, data_020c80f8);
        func_0201b044((char *) work + 0x350, data_021fbee8);
        func_0201afd4((char *) work + 0x350, data_021fbee8);
        return;
    }
    v = func_020e8ed8(dx, dy);
    if (func_0201c3dc((short) (v - angle)) != 0) {
        if (self->unk_00 == 2) {
            func_0201b1a4((char *) work + 0x350, work, 2, 0, data_020c80f8);
        } else {
            func_0201b1a4((char *) work + 0x350, work, 1, 0, data_020c80f8);
        }
        func_0201aff4((char *) work + 0x350, angle);
        self->unk_98 = 1;
    } else {
        func_0201b1a4((char *) work + 0x350, work, 4, 0, data_020c80f8);
        func_0201aff4((char *) work + 0x350, v);
        self->unk_98 = 3;
    }
    func_0201b044((char *) work + 0x350, coord);
    func_0201afd4((char *) work + 0x350, coord);
}
