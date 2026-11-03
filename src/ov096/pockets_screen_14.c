/* pockets_screen_14: 3 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229f9dc @ 0x0229f9dc, 0x68 bytes, Thumb
 * func_ov096_0229f970 @ 0x0229f970, 0x6c bytes, Thumb
 * func_ov096_0229f90c @ 0x0229f90c, 0x64 bytes, Thumb
 */

struct UnkStruct_0229f9dc {
    unsigned char pad_00[0xB1];
    unsigned char mode;
    unsigned char pad_B2[2];
    unsigned char unk_B4;
    unsigned char pad_B5[4];
    unsigned char unk_B9;
    char pad_BA[0x2418 - 0xBA];
    char unk_2418[1];
};

typedef struct {
    unsigned char pad_00[0xb1];
    unsigned char b1;
    unsigned char pad_B2[2];
    unsigned char b4;
    unsigned char pad_B5[5];
    unsigned char ba;
    unsigned char bb;
    unsigned char pad_BC[0x2418 - 0xbc];
    unsigned char unk_2418;
} UnkStruct_0229f970;

extern int func_ov002_02207d24(void *p, int n);
extern void func_ov096_0229e90c(struct UnkStruct_0229f9dc *self, int param);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov096_0229ea88(struct UnkStruct_0229f9dc *self);
extern void func_ov096_0229c2dc(struct UnkStruct_0229f9dc *self, unsigned int size);
extern void func_ov094_022999c0(void);
extern void func_ov096_0229e8e0(UnkStruct_0229f970 *self, int val);
extern int func_ov096_0229ea5c(UnkStruct_0229f970 *self);
extern void func_ov002_02209d68(void *p, int a, int b);
extern int func_ov096_0229f290(void *p, unsigned char c);
extern int func_ov096_0229f200(void *p, unsigned char c);
extern int func_ov002_02209d38(void *p, int a, int b, int c);
extern int func_ov002_02209d8c(void *p);
extern void func_ov096_0229ea34(void *p);

void func_ov096_0229f9dc(struct UnkStruct_0229f9dc *self, int param)
{
    unsigned char mode;

    self->unk_B4 = param;
    func_ov002_02207d24((char *) self + 0x2418, 1);
    func_ov096_0229e90c(self, param);

    mode = self->mode;
    switch (mode) {
        case 1:
            func_ov002_02208098((void *) (self), 6);
            break;
        case 2:
            func_ov002_02208098((void *) (self), 5);
            break;
        default:
            break;
    }

    func_ov096_0229ea88(self);
    ((void) (func_ov096_0229c2dc(self, 0x4000)), func_ov094_022999c0());

    self->unk_B9 = 0x26;
}

void func_ov096_0229f970(UnkStruct_0229f970 *self, int val)
{
    self->b4 = val;
    func_ov002_02207d24(&self->unk_2418, 1);
    if (self->bb == 0) {
        func_ov096_0229e8e0(self, val);
    } else {
        func_ov096_0229e90c((struct UnkStruct_0229f9dc *) self, val);
    }
    switch (self->b1) {
        case 1:
            self->ba = 0xc;
            break;
        case 2:
            self->ba = 0xb;
            break;
    }
    ((void) (func_ov096_0229ea5c(self)), func_ov094_022999c0());
}

unsigned char *func_ov096_0229f90c(unsigned char *param0, unsigned char param1, int param2)
{
    *(unsigned char *) (param0 + 0xb4) = param1;
    func_ov002_02209d68(param0 + 0x24e8, *(int *) (param0 + 0xa4), *(int *) (param0 + 0xa8));
    {
        int ret1 = func_ov096_0229f290(param0, param1);
        int ret2 = func_ov096_0229f200(param0, param1);
        func_ov002_02209d38(param0 + 0x24e8, ret1, ret2, param2);
    }
    func_ov002_02209d8c(param0 + 0x24e8);
    func_ov096_0229ea34(param0);
    return func_ov002_02208098((void *) (param0), 0x1b);
}
