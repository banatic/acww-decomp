/* field_label_2: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b8e10 @ 0x020b8e10, 0xcc bytes, Thumb
 * func_020b8df0 @ 0x020b8df0, 0x20 bytes, Thumb
 * func_020b8dd8 @ 0x020b8dd8, 0x18 bytes, Thumb
 * func_020b8dc0 @ 0x020b8dc0, 0x18 bytes, Thumb
 * func_020b8db4 @ 0x020b8db4, 0xc bytes, Thumb
 * func_020b8d74 @ 0x020b8d74, 0x40 bytes, Thumb
 * func_020b8d6c @ 0x020b8d6c, 0x8 bytes, Thumb
 * func_020b8d08 @ 0x020b8d08, 0x64 bytes, Thumb
 * func_020b8cec @ 0x020b8cec, 0x1c bytes, Thumb
 * func_020b8cc8 @ 0x020b8cc8, 0x24 bytes, Thumb
 * func_020b8cb8 @ 0x020b8cb8, 0x10 bytes, Thumb
 * func_020b8ca8 @ 0x020b8ca8, 0x10 bytes, Thumb
 * func_020b8c98 @ 0x020b8c98, 0x10 bytes, Thumb
 * func_020b8c88 @ 0x020b8c88, 0x10 bytes, Thumb
 * func_020b8c30 @ 0x020b8c30, 0x58 bytes, Thumb
 * func_020b8c24 @ 0x020b8c24, 0xc bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020b8e10_2;

typedef struct {
    unsigned char pad_00[0x7c];
    int unk_7C;
} UnkStruct_020b8e10;

typedef struct {
    unsigned char pad_00[0x7c];
    int unk_7C;
} UnkStruct_020b8df0;

typedef struct {
    char pad_00[0x7c];
    int unk_7C;
} Owner;

typedef struct {
    int unk_00;
} Target;

typedef struct {
    char pad_00[0x7c];
    unsigned int unk_7C;
} UnkStruct_020b8db4;

typedef struct UnkStruct_020b8d08 {
    void *unk_00;          // 0x00
    int unk_04;            // 0x04
    char sub8[0xec];       // 0x08
    int unk_F4;            // 0xf4
    unsigned short unk_F8; // 0xf8
    int unk_FC;            // 0xfc
    int unk_100;           // 0x100
    int unk_104;           // 0x104
    int unk_108;           // 0x108
    char unk_10C;          // 0x10c
    char unk_10D;          // 0x10d
} UnkStruct_020b8d08;

struct UnkStruct_020b8cc8 {
    void *vtable;
    int unk_04;
    char sub[4];
};

extern int func_020b65c4(void);
extern int func_0203dff0(void);
extern int func_0203e21c(void);
extern int func_0203e190(void);
extern UnkStruct_020b8e10_2 *func_020682e0(int i);
extern int func_02070070(void);
extern int func_0206f53c(void);
extern void func_020b889c(void *p);
extern int data_020d2288[];
extern UnkStruct_020b8e10 data_021f6ba0;
extern unsigned char data_021f6b20[];
extern void func_020b88c0(int *);
extern int data_021f6c20;
extern void func_02038d50(void);
extern void *func_020b91c4(void *);
extern unsigned char data_020e5848[];
extern void *func_020b91a0(void *);
extern void func_020edb3c(void *);
extern void func_020b8b88(void *ptr);
extern void func_020b8b74(void *ptr);
extern void func_0208aa40(void *);
extern void func_020b9070(int arg);

void func_020b8c30(void *p);
void func_020b8c24(int arg);

void func_020b8e10(int idx)
{
    int v;
    int res = 0;
    int ok;
    int c;
    int f;
    int t;
    UnkStruct_020b8e10_2 *e;

    v = func_020b65c4();
    ok = 0;
    if ((unsigned char) (v + 0xf4) <= 2) {
    } else if ((unsigned char) (v + 0xd2) <= 1) {
    } else {
        ok = 1;
    }
    if (ok != 0) {
        if (func_0203dff0() != 0 || func_0203e21c() != 0 || func_0203e190() != 0) {
            c = 1;
        } else {
            c = 0;
        }
        f = 0;
        if (c != 0) {
            e = func_020682e0(0);
            t = 0;
            if (e != 0 && e->unk_04 != 0) {
                t = 1;
            }
            if (func_02070070() != 0) {
                if (func_0206f53c() != 0) {
                    f = 1;
                } else {
                    res = 1;
                }
            } else {
                if (t != 0) {
                    res = 2;
                }
            }
        } else {
            if (func_02070070() != 0 && func_0206f53c() != 0) {
                f = 1;
            }
        }
        if (f != 0 && idx < 4) {
            res = data_020d2288[idx];
        }
    }
    if (data_021f6ba0.unk_7C != 0xa) {
        data_021f6ba0.unk_7C = res;
        if (res != 0) {
            func_020b889c(data_021f6b20);
        }
    }
}

void func_020b8df0(int index)
{
    int value = data_020d2288[index];
    (*(UnkStruct_020b8df0 *) &data_021f6ba0).unk_7C = value;
    func_020b889c((void *) (((int *) data_021f6b20)));
}

void func_020b8dd8(void)
{
    *(int *) ((char *) ((int) ((int *) &data_021f6ba0)) + (124)) = 9;
    func_020b889c((void *) ((int) ((int *) data_021f6b20)));
}

void func_020b8dc0(void)
{
    (*(Owner *) &data_021f6ba0).unk_7C = 0xa;
    func_020b889c((void *) (((Target *) data_021f6b20)));
}

void func_020b8db4(void)
{
    (*(UnkStruct_020b8db4 *) &data_021f6ba0).unk_7C = 0;
}

void func_020b8d74(int param)
{
    int x = func_020b65c4();
    int flag = 0;

    if (!((unsigned char) (x + 0xf4) <= 2 || (unsigned char) (x + 0xd2) <= 1)) {
        flag = 1;
    }

    if (flag) {
        data_021f6c20 = param;
        func_020b88c0(((int *) data_021f6b20));
    }
}

void func_020b8d6c(void)
{
    func_02038d50();
}

UnkStruct_020b8d08 *func_020b8d08(UnkStruct_020b8d08 *self)
{
    self->unk_00 = (void *) data_020e5848;
    self->unk_04 = 0;
    func_020b91c4(self->sub8);
    self->unk_F4 = 0;
    self->unk_F8 = 0xfff1;
    self->unk_FC = 0;
    self->unk_100 = 0;
    self->unk_104 = 0;
    self->unk_108 = 0;
    self->unk_10C = 0;
    self->unk_10D = 0;
    return self;
}

void *func_020b8cec(void *self)
{
    *(unsigned int *) self = (unsigned int) ((char *) data_020e5848);
    func_020b91a0((char *) self + 8);
    return self;
}

void *func_020b8cc8(struct UnkStruct_020b8cc8 *obj)
{
    obj->vtable = (void *) ((int *) data_020e5848);
    func_020b91a0((void *) &obj->sub[0]);
    func_020edb3c((void *) obj);
    return obj;
}

void func_020b8cb8(void)
{
    func_020b8c30((void *) data_021f6b20);
}

void func_020b8ca8(void)
{
    func_020b8c24((int) ((void *) data_021f6b20));
}

void func_020b8c98(void)
{
    func_020b8b88((void *) data_021f6b20);
}

void func_020b8c88(void)
{
    func_020b8b74((void *) data_021f6b20);
}

void func_020b8c30(void *p)
{
    int *q = (int *) p;
    q[1] = 0;
    func_0208aa40((char *) p + 8);
    q[0x3d] = 0;
    *(unsigned short *) ((char *) p + 0xf8) = 0xfff1;
    q[0x3f] = 0;
    q[0x40] = 0;
    q[0x41] = 0;
    q[0x42] = 0;
    ((char *) p)[0x10c] = 0;
    ((char *) p)[0x10d] = 0;
}

void func_020b8c24(int arg)
{
    func_020b9070(arg + 8);
}
