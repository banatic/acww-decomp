/* owl_4: 10 functions, module ov047
 * mwccarm 1.2/base -O4,s
 * func_ov047_02262450 @ 0x02262450, 0xa4 bytes, Thumb
 * func_ov047_022623cc @ 0x022623cc, 0x84 bytes, Thumb
 * func_ov047_02262390 @ 0x02262390, 0x3c bytes, Thumb
 * func_ov047_02262360 @ 0x02262360, 0x30 bytes, Thumb
 * func_ov047_022622fc @ 0x022622fc, 0x64 bytes, Thumb
 * func_ov047_022622bc @ 0x022622bc, 0x40 bytes, Thumb
 * func_ov047_02262238 @ 0x02262238, 0x84 bytes, Thumb
 * func_ov047_02262204 @ 0x02262204, 0x34 bytes, Thumb
 * func_ov047_02262200 @ 0x02262200, 0x4 bytes, Thumb
 * func_ov047_022621c8 @ 0x022621c8, 0x38 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x3b0];
    unsigned char sub_3b0[0x1b4];
    unsigned char buf_564[0x1c8];
    unsigned char flag_72c;
    unsigned char pad_72D;
    unsigned short unk_72E;
    unsigned short unk_730;
    unsigned short unk_732;
    unsigned char pad_734[2];
    unsigned char flag_736;
} UnkStruct_02262450;

typedef struct UnkStruct_022622bc {
    char pad_00[0x8e];
    char buf[0x478 - 0x8e];
    char unk_478;
    char pad_479[0x73c - 0x479];
    int unk_73C;
} UnkStruct_022622bc;

struct UnkStruct_02262204 {
    char pad_00[0x618];
    int unk_618;
    char pad_61C[0x11A];
    unsigned char unk_736;
};

extern int func_02019c6c(unsigned char *, int, unsigned short);
extern int func_0202ea40(void *, int *, int);
extern int func_020644cc(int);
extern unsigned short data_020c80f8;
extern void *data_020ccf94;
extern int func_020e8840(void *p);
extern void func_ov047_022624f4(void *obj, int n);
extern int func_02073d90(void *);
extern short *func_0209d358(int a, int b);
extern int func_0209dcac(void);
extern int func_02019d0c(char *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern int func_02019c20(char *p, int a, int b, int c, int d, int e);
extern int data_020c814c;
extern unsigned char data_021fbee8[];
extern int func_020912d4(int a, char *b, char *c, int _x);
extern void func_02091278(void *, void *, void *, void *);
extern int func_02016104(void *p);
extern int func_0201c314(void *a, int b);
extern void func_0209129c(int a);
extern void func_0201ad18(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
extern int func_020147fc(void *a, int b, int c, int d);
extern int func_02014868(void *);
extern int func_0203e020(void *);

int func_ov047_02262450(UnkStruct_02262450 *self)
{
    int local;

    self->unk_72E = 0xff;
    func_02019c6c(self->buf_564, 1, self->unk_730);

    if (self->flag_72c == 0) {
        if (func_0202ea40(self, &local, 1) != 0) {
            self->unk_72E = 100 + 20 * func_020644cc(5);
        }
    }

    self->flag_736 = 0;
    self->unk_730 = data_020c80f8;
    self->unk_732 = 0x78;
    func_0201ad18((int) self->sub_3b0, 1, 0, 0, (int) (((char *) data_021fbee8)), 4, (unsigned long) ((*(unsigned long *) &data_020c814c)), 1);
    return 1;
}

int func_ov047_022623cc(void *obj)
{
    unsigned short *p = (unsigned short *) ((char *) obj + 0x72e);

    if (*p != 0xff) {
        if (func_020e8840(p) == 0) {
            func_ov047_022624f4(obj, 5);
        }
        return 1;
    }
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0 || func_0209dcac() == 2 || func_0209dcac() == 3) {
        return 1;
    }
    if (func_020e8840((char *) obj + 0x732) == 0) {
        *(unsigned short *) ((char *) obj + 0x738) = 0x18;
        func_ov047_022624f4(obj, 2);
    }
    return 1;
}

int func_ov047_02262390(char *p)
{
    int v0 = 0;
    int v1 = 0;
    int v2 = *(signed short *) (p + 0x734);
    int v3 = 0;
    int v4 = 0;
    int v5 = data_020c80f8;
    int v6 = 0;
    func_02019d0c(p + 0x564, 3, 1, 0, v0, v1, v2, v3, v4, v5, v6);
    return 1;
}

int func_ov047_02262360(void *self)
{
    if (func_02019e00((char *) self + 0x564) == 3 && func_02019de8((char *) self + 0x564) != 0) {
        func_ov047_022624f4(self, 0);
    }
    return 1;
}

int func_ov047_022622fc(char *p)
{
    func_02019c20(p + 0x564, 1, 0xf0, 0, *(unsigned short *) (p + 0x738), 0);
    *(unsigned char *) (p + 0x736) = 1;
    func_0201ad18((int) (p + 0x3b0), 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    return 1;
}

int func_ov047_022622bc(UnkStruct_022622bc *self)
{
    int v = self->unk_73C;
    if (v == -1) {
        self->unk_73C = func_020912d4(0x3c, &self->unk_478, self->buf, 0);
    } else {
        func_02091278((void *) (v), (void *) (&self->unk_478), (void *) (self->buf), 0);
    }
    return 1;
}

int func_ov047_02262238(void *self)
{
    int v;
    int size;

    size = func_02016104((char *) self + 0x658);
    v = 0;
    if (size != 0) {
        v = func_0201c314(self, size);
    }
    if (*(int *) ((char *) self + 0x73c) != -1) {
        func_0209129c(*(int *) ((char *) self + 0x73c));
        *(int *) ((char *) self + 0x73c) = -1;
    }
    func_0201ad18((int) ((char *) self + 0x3b0), 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    func_020147fc((char *) self + 0x618, 0, v, 0);
    return 1;
}

int func_ov047_02262204(struct UnkStruct_02262204 *obj)
{
    if (func_02014868(&obj->unk_618) == 0) {
        obj->unk_736 = 0;
        func_0203e020(obj);
        func_ov047_022624f4(obj, 4);
    }
    return 1;
}

int func_ov047_02262200(void)
{
    return 1;
}

int func_ov047_022621c8(int param)
{
    func_0201ad18(param + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    return 1;
}
