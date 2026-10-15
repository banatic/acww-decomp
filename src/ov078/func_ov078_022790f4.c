/* func_ov078_022790f4 @ 0x022790f4, 0x248 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022790f4 {
    char pad_00[0x5c];
    char unk_5C[0x8e - 0x5c];
    short unk_8E;
    char pad_90[0x98 - 0x90];
    int unk_98;
    char pad_9C[0x350 - 0x9c];
    char unk_350[0x3aa - 0x350];
    char unk_3AA[0x564 - 0x3aa];
    char unk_564[0x651 - 0x564];
    unsigned char unk_651;
} UnkStruct_022790f4;

extern unsigned short data_020c80f8;
extern int data_021cb5a0;
extern int data_021fbee8[3];

extern int func_ov078_0227952c(UnkStruct_022790f4 *self);
extern unsigned char func_020e8858(unsigned char *p);
extern int func_ov078_0227933c(UnkStruct_022790f4 *self);
extern int func_02019de8(void *p);
extern int func_0201b354(void *p);
extern int func_020e92e8(int *p);
extern int func_ov078_0227949c(UnkStruct_022790f4 *self, int *v, int *z);
extern int func_0200322c(void *p, int *v);
extern int func_0201c3dc(int a);
extern int func_020644cc(int a);
extern int func_02019e00(void *p);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_ov078_02279670(UnkStruct_022790f4 *self, int a);
extern int *func_0201afd0(void *p);

static __inline int GetState(UnkStruct_022790f4 *self)
{
    return func_02019e00(self->unk_564);
}

int func_ov078_022790f4(UnkStruct_022790f4 *self)
{
    void *sub;
    int ok;
    int dir;
    int mode;
    int *p;
    int v[3];
    int v2[3];

    sub = self->unk_564;
    ok = func_ov078_0227952c(self);
    func_020e8858(&self->unk_651);
    if (ok != 0) {
        if (func_ov078_0227933c(self) == 0) {
            if (func_02019de8(sub) != 0) {
                if (func_0201b354(self->unk_3AA) == 2) {
                    func_02019d0c(sub, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                } else if ((func_020e92e8(&data_021cb5a0) & 7) == 0) {
                    v[0] = data_021fbee8[0];
                    v[1] = data_021fbee8[1];
                    v[2] = data_021fbee8[2];
                    if (func_ov078_0227949c(self, v, &v[2]) != 0) {
                        dir = func_0200322c(self->unk_5C, v);
                        if (func_0201c3dc((short) (dir - self->unk_8E)) != 0) {
                            mode = 1;
                            if (func_020644cc(4) == 0) {
                                mode = 2;
                            }
                            if (mode != GetState(self)) {
                                func_02019d0c(sub, mode, 1, v[0], v[2], 0, 0, 0, 0, data_020c80f8, 0);
                                self->unk_651 = 0x64;
                            }
                        } else {
                            if (GetState(self) != 4) {
                                func_02019d0c(sub, 4, 1, v[0], v[2], 0, dir, 0, 0, data_020c80f8, 0);
                                self->unk_651 = 0x50;
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
                        if (self->unk_651 == 0) {
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
            func_ov078_02279670(self, 3);
        }
    }
    return 0;
}
