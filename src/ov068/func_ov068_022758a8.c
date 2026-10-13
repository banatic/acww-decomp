/* func_ov068_022758a8 @ 0x022758a8, 0x8c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov068_02277fdc[2];
extern void func_02019d0c(void *p, int a, int b, unsigned int c, unsigned int d, int e, int f, int g, int h, int i, int j);
extern int func_02019de8(void *p);
extern void func_ov068_02275c78(void *self, int a);

typedef struct {
    unsigned int lo, hi;
} UnkPair;

struct UnkStruct_022758a8 {
    unsigned char pad_00[0x564];
    unsigned char unk_564[0x4e0];
    unsigned int unk_A44;
    unsigned int unk_A48;
    unsigned char pad_A4C[4];
    unsigned char unk_A50;
    unsigned char pad_A51[0x1f];
    unsigned int unk_A70;
    unsigned char pad_A74[4];
    unsigned int unk_A78;
};

void func_ov068_022758a8(struct UnkStruct_022758a8 *self)
{
    if (self->unk_A50 == 1) {
        *(UnkPair *) ((char *) self + 0xa44) = *(UnkPair *) &data_ov068_02277fdc;
        func_02019d0c(&self->unk_564, 1, 2, self->unk_A70, self->unk_A78, 0, 0, 0, 0, 0, 0);
    } else if (self->unk_A50 == 0) {
        if (func_02019de8(&self->unk_564) != 0) {
            func_ov068_02275c78(self, 4);
        }
    }
    if (self->unk_A50 != 0) {
        self->unk_A50--;
    }
}
