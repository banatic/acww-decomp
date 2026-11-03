/* insurer_3: 2 functions, module ov071
 * mwccarm 1.2/base -O4,s
 * func_ov071_022798f8 @ 0x022798f8, 0xc8 bytes, Thumb
 * func_ov071_02279858 @ 0x02279858, 0xa0 bytes, Thumb
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
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_ov071_02279b2c(UnkStruct_022798f8_2 *self, int a);
extern unsigned short data_020c80f8;
extern void *data_020c814c;
extern int func_02096190(int);
extern int func_02019c20(void *p, int a, int b, int c, int d, int e);
extern void func_02013c0c(void *p);
extern void func_0201ad18(void *p, int a, int b, int c, void *d, int e, void *f, int g);
extern unsigned char data_021fbee8[];

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

int func_ov071_02279858(void *self)
{
    *((unsigned int *) ((char *) self + 0x734)) = func_02096190(4);
    {
        unsigned int *src = (unsigned int *) ((char *) self + 0x5c);
        *((unsigned int *) ((char *) self + 0x738)) = *((unsigned int *) ((char *) self + 0x5c));
        *((unsigned int *) ((char *) self + 0x73c)) = src[1];
        *((unsigned int *) ((char *) self + 0x740)) = src[2];
    }
    func_02019c20((char *) self + 0x564, 1, 0xdf, 1, data_020c80f8, 0);
    func_02013c0c((char *) self + 0x558);
    func_0201ad18((char *) self + 0x3b0, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    *((unsigned char *) self + 0x729) = 0;
    return 1;
}
