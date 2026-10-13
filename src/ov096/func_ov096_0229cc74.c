/* func_ov096_0229cc74 @ 0x0229cc74, 0x118 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229cc74 {
    unsigned char pad_00[0xb6];
    unsigned char unk_B6;
    unsigned char pad_B7[0x2361];
    char unk_2418;
    unsigned char pad_2419[0x533];
    char unk_294C;
};

extern void func_ov096_0229c2dc(void *, int);
extern void func_ov002_02208d30(void *, int);
extern int func_ov096_0229f830(void *, int);
extern int func_ov096_0229f820(void *, int);
extern void func_ov096_0229cf84(void *, int);
extern void func_ov096_0229ce4c(void *, int);
extern void func_ov096_0229cdec(void *);
extern void func_ov096_0229cd8c(void *);
extern int func_ov002_02208d18(void *);
extern void func_ov002_02208d4c(void *, int, int);
extern void func_ov096_0229ddd8(void *);
extern void func_ov002_02207d24(void *, int);
extern void func_ov096_0229d1d4(void *, int);
extern void func_ov096_0229c414(void *);

void func_ov096_0229cc74(struct UnkStruct_0229cc74 *self, int kind, int flag)
{
    func_ov096_0229c2dc(self, 0x00040000);
    self->unk_B6 = (char) kind;
    func_ov002_02208d30(&self->unk_294C, 0x22);

    if (func_ov096_0229f830(self, kind)) {
        func_ov096_0229cf84(self, kind);
        goto common;
    } else if (func_ov096_0229f820(self, kind)) {
        func_ov096_0229ce4c(self, kind);
        goto common;
    } else if (kind == 0x25) {
        func_ov096_0229cdec(self);
        goto common;
    } else if (kind == 0x24) {
        func_ov096_0229cd8c(self);
        goto common;
    } else if (kind != 0x27) {
        return;
    }

common:
    if (func_ov002_02208d18(&self->unk_294C) == 0) {
        if (func_ov096_0229f830(self, kind) || func_ov096_0229f820(self, kind)) {
            func_ov002_02208d4c(&self->unk_294C, 0x7c, 0x22);
        } else {
            if (kind == 0x25 || kind == 0x27) {
                func_ov002_02208d4c(&self->unk_294C, 0x7b, 0x22);
                self->unk_B6 = 0x25;
            } else if (kind == 0x24) {
                func_ov002_02208d4c(&self->unk_294C, 0x7a, 0x22);
            }
        }
    } else {
        func_ov002_02208d4c(&self->unk_294C, 2, 0x22);
    }

    func_ov096_0229ddd8(self);
    if (flag == 0) {
        func_ov002_02207d24(&self->unk_2418, 1);
    }
    func_ov096_0229d1d4(self, flag);
    if (func_ov096_0229f830(self, kind) == 0 && kind != 0x24) {
        func_ov096_0229c414(self);
    }
}
