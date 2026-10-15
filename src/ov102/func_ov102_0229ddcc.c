/* func_ov102_0229ddcc @ 0x0229ddcc, 0xd8 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov102_0229cc60(void *self, unsigned char b);
extern void func_ov102_0229cb50(void *self);
extern int func_ov002_02207d24(void *obj, int val);
extern void func_ov102_0229c460(void *self, int val);
extern void func_ov102_0229cd80(void *self);
extern void func_ov102_0229cf74(void *self);
extern int func_ov102_0229d37c(void *self, void *a, void *b, int c);
extern int func_ov102_0229d0b0(void *self, int idx);
extern void func_ov102_0229d508(void *self, unsigned char b, void *p);
extern int func_ov102_0229d320(void *self, int idx);
extern void func_ov094_022999d8(void);
extern void func_ov102_0229d740(void *self);
extern void func_ov102_0229cf3c(void *self, int idx);

extern unsigned char data_021fbdd8;

typedef struct {
    unsigned char pad_00[0x218c];
    unsigned char sub; // 0x218c
    unsigned char pad_218D[0x24e0 - 0x218d];
    void *ptr0; // 0x24e0
    void *ptr1; // 0x24e4
    unsigned char pad_24E8[0x25a2 - 0x24e8];
    unsigned char state; // 0x25a2
} UnkStruct_0229ddcc;

void func_ov102_0229ddcc(UnkStruct_0229ddcc *self)
{
    int idx, ret;
    char *p1;

    if (func_0206f56c()) {
        func_ov102_0229cc60(self, self->state);
        func_ov102_0229cb50(self);
        func_ov002_02207d24((char *) self + 0x218c, 0);
        func_ov102_0229c460(self, 0);
        return;
    }

    func_ov102_0229cd80(self);
    func_ov102_0229cf74(self);

    p1 = (char *) self->ptr1 + 8;
    idx = func_ov102_0229d37c(self, (char *) self->ptr0 + 8, p1, 0);

    if (idx != 0x25) {
        if (data_021fbdd8) {
            goto L_special;
        }
        if (func_ov102_0229d0b0(self, idx) != 0) {
            func_ov102_0229d508(self, self->state, p1);
            return;
        }
        ret = func_ov102_0229d320(self, idx);
        if (ret == 0) {
            func_ov102_0229d508(self, self->state, p1);
            return;
        } else {
            func_ov094_022999d8();
            func_ov102_0229d740(self);
            return;
        }
    L_special:
        func_ov102_0229cf3c(self, idx);
        return;
    } else {
        if (!data_021fbdd8) {
            func_ov102_0229d508(self, self->state, p1);
        }
        return;
    }
}
