/* func_ov121_0229b484 @ 0x0229b484, 0xf0 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb1];
    unsigned char unk_B1;
    unsigned char pad_B2[0x226];
    unsigned int unk_2D8;
} Obj_ov121_0229c3a8;

extern int func_ov002_02208014(void);
extern unsigned char *func_ov121_0229b008(Obj_ov121_0229c3a8 *self);
extern int func_ov002_02207d24(void *ptr, int arg);
extern int func_ov002_02208008(Obj_ov121_0229c3a8 *self);
extern int func_ov121_02299ccc(Obj_ov121_0229c3a8 *self, int a, int b);
extern void func_ov121_0229a450(Obj_ov121_0229c3a8 *self);
extern void func_ov121_0229a2e4(Obj_ov121_0229c3a8 *self);
extern int func_ov121_02299fc8(Obj_ov121_0229c3a8 *self);
extern void func_ov121_0229a170(Obj_ov121_0229c3a8 *self);
extern void func_ov121_0229a130(Obj_ov121_0229c3a8 *self);
extern int func_ov090_02299078(int arg);
extern int func_ov090_02299098(int arg);
extern int func_ov121_0229bc70(Obj_ov121_0229c3a8 *self, int arg);
extern void func_ov002_02207d00(void *ptr);

extern struct {
    unsigned short pad;
    unsigned short flags;
} data_021fbe40;

void func_ov121_0229b484(Obj_ov121_0229c3a8 *self)
{
    unsigned short flags;

    if (func_ov002_02208014() != 0) {
        func_ov121_0229b008(self);
        func_ov002_02207d24(&self->unk_2D8, 1);
        return;
    } else {
        if (func_ov121_02299ccc(self, func_ov002_02208008(self), 0) != 0) {
            func_ov121_0229a450(self);
            func_ov121_0229a2e4(self);
            func_ov002_02207d24(&self->unk_2D8, 0);
            return;
        }

        if ((data_021fbe40.flags & 1) != 0) {
            func_ov002_02207d24(&self->unk_2D8, 1);
            if (func_ov121_02299fc8(self) != (int) -1) {
                func_ov121_0229a170(self);
                return;
            }
            if (self->unk_B1 <= 7) {
                func_ov121_0229a130(self);
                return;
            }
        }

        flags = data_021fbe40.flags;
        if ((flags & 0x100) != 0) {
            func_ov121_0229bc70(self, func_ov090_02299078(1));
            return;
        }
        if ((flags & 0x200) != 0) {
            func_ov121_0229bc70(self, func_ov090_02299098(1));
            return;
        }
        if ((flags & 2) != 0) {
            func_ov121_0229bc70(self, 7);
            return;
        }
        func_ov002_02207d00(&self->unk_2D8);
        return;
    }
}
