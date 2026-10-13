/* func_ov071_022792e0 @ 0x022792e0, 0x290 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022792e0 {
    char pad_00[0x5c];
    char unk_5C[0x8e - 0x5c];
    short unk_8E;
    char pad_90[0x98 - 0x90];
    int unk_98;
    char pad_9C[0x350 - 0x9c];
    char unk_350[0x3aa - 0x350];
    char unk_3AA[0x564 - 0x3aa];
    char unk_564[0x72c - 0x564];
    int unk_72C;
    char unk_730[4];
} UnkStruct_022792e0;

extern unsigned short data_020c80f8;
extern int data_021cb5a0;
extern int data_021fbee8[3];

extern int func_ov071_02279c08(UnkStruct_022792e0 *self, void *p);
extern int func_0202ea80(int a, int b);
extern int func_ov071_02279c18(UnkStruct_022792e0 *self, int a);
extern int func_ov071_02279b2c(UnkStruct_022792e0 *self, int a);
extern void func_ov071_02279d04(UnkStruct_022792e0 *self, int a);
extern int func_ov071_02279570(UnkStruct_022792e0 *self);
extern int func_02019de8(void *p);
extern int func_0201b354(void *p);
extern int func_020e92e8(int *p);
extern int func_ov071_022796d0(UnkStruct_022792e0 *self, int *v, int *z);
extern int func_0200322c(void *p, int *v);
extern int func_0201c3dc(int a);
extern int func_020644cc(int a);
extern int func_02019e00(void *p);
extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int *func_0201afd0(void *p);

static __inline int GetState(UnkStruct_022792e0 *self)
{
    return func_02019e00(self->unk_564);
}

int func_ov071_022792e0(UnkStruct_022792e0 *self)
{
    void *sub;
    int dir;
    int mode;
    int *p;
    int v[3];
    int v2[3];

    sub = self->unk_564;
    if (func_ov071_02279c08(self, self->unk_730) == 0 && func_0202ea80(0x28, 0) == 0 && func_ov071_02279c18(self, 0) != 0 &&
        func_ov071_02279b2c(self, 0x8000) != 0) {
        func_ov071_02279d04(self, 1);
        return 1;
    }
    func_ov071_02279c08(self, &self->unk_72C);
    if (func_ov071_02279c18(self, 1) != 0) {
        if (func_ov071_02279570(self) == 0) {
            if (func_02019de8(sub) != 0) {
                if (func_0201b354(self->unk_3AA) == 2) {
                    func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                } else if ((func_020e92e8(&data_021cb5a0) & 7) == 0) {
                    v[0] = data_021fbee8[0];
                    v[1] = data_021fbee8[1];
                    v[2] = data_021fbee8[2];
                    if (func_ov071_022796d0(self, v, &v[2]) != 0) {
                        dir = func_0200322c(self->unk_5C, v);
                        if (func_0201c3dc((short) (dir - self->unk_8E)) != 0) {
                            mode = 1;
                            if (func_020644cc(4) == 0) {
                                mode = 2;
                            }
                            if (mode != GetState(self)) {
                                func_02019d0c(sub, mode, 1, v[0], v[2], 0, 0, 0, 0, data_020c80f8, 0);
                                self->unk_72C = 0x64;
                            }
                        } else {
                            if (GetState(self) != 4) {
                                func_02019d0c(sub, 4, 1, v[0], v[2], 0, dir, 0, 0, data_020c80f8, 0);
                                self->unk_72C = 0x50;
                            }
                        }
                    } else {
                        func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                    }
                } else {
                    func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                }
            } else {
                if (self->unk_98 != 0) {
                    if (GetState(self) == 1 || GetState(self) == 2 || GetState(self) == 4) {
                        if (self->unk_72C == 0) {
                            func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                        } else {
                            p = func_0201afd0(self->unk_350);
                            v2[0] = p[0];
                            v2[1] = p[1];
                            v2[2] = p[2];
                            if (func_0201c3dc((short) (func_0200322c(self->unk_5C, v2) - self->unk_8E)) == 0) {
                                func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                            }
                        }
                    }
                }
            }
        }
    } else {
        if (self->unk_98 != 0) {
            func_ov071_02279d04(self, 4);
        }
    }
    return 0;
}
