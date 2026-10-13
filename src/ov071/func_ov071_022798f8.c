/* func_ov071_022798f8 @ 0x022798f8, 0xc8 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} Sub2;

typedef struct {
    char pad_00[0x5c];
    Sub2 unk_5C;
} UnkStruct_022798f8;

typedef struct {
    char pad_00[0x564];
    char unk_564;
    char pad_565[0x729 - 0x565];
    unsigned char unk_729;
    char pad_72A[0x72c - 0x72a];
    int unk_72C;
    int unk_730;
    UnkStruct_022798f8 *unk_734;
} UnkStruct_022798f8_2;

extern void func_ov071_02279d04(UnkStruct_022798f8_2 *self, int a);
extern int func_ov071_02279c08(UnkStruct_022798f8_2 *self, void *p);
extern int func_0201c314(UnkStruct_022798f8_2 *self, UnkStruct_022798f8 *p);
extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_ov071_02279b2c(UnkStruct_022798f8_2 *self, int a);
extern unsigned short data_020c80f8;

void func_ov071_022798f8(UnkStruct_022798f8_2 *self)
{
    if (self->unk_734 == 0) {
        func_ov071_02279d04(self, 3);
    } else if (func_ov071_02279c08(self, &self->unk_72C) == 0) {
        int t = func_0201c314(self, self->unk_734);
        func_02019d0c(&self->unk_564, 3, 1, 0, 0, 0, t, 0, 0, data_020c80f8, 0);
        self->unk_730 = 0xc8;
        func_ov071_02279d04(self, 3);
    } else if (func_ov071_02279b2c(self, 0x5000) == 0) {
        UnkStruct_022798f8 *p = self->unk_734;
        Sub2 *q = &p->unk_5C;
        func_02019d0c(&self->unk_564, 2, 1, q->unk_00, q->unk_08, 0, 0, 0, 0, data_020c80f8, 0);
        self->unk_72C = 0x12c;
        self->unk_729 = 1;
    }
}
