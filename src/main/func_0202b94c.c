/* func_0202b94c @ 0x0202b94c, 0x148 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0202b94c {
    unsigned char pad_00[0x830];
    void *unk_830;
} UnkStruct_0202b94c;

typedef struct UnkStruct_0202b94c_2 {
    unsigned char pad_00[0x100];
    UnkStruct_0202b94c *unk_100;
    unsigned char arr_104[0x1e];
    unsigned char unk_122;
    unsigned char pad_123[5];
    unsigned int unk_128;
    unsigned int unk_12C;
    unsigned int unk_130;
    unsigned int unk_134;
} UnkStruct_0202b94c_2;

typedef struct UnkStruct_0202b94c_3 {
    void *ptr;
    unsigned char byte;
} UnkStruct_0202b94c_3;

typedef struct UnkStruct_0202b94c_4 {
    unsigned int a;
    unsigned char b;
} UnkStruct_0202b94c_4;

extern UnkStruct_0202b94c_4 data_020d8f40;
extern unsigned int data_020d9d4c[];
extern unsigned char data_020c8940[];

extern void func_0202d8f8(void *self, void *p12c, void *p128, void *p830, int zero);
extern UnkStruct_0202b94c *func_0201ce50(void *a);
extern void *func_0208150c(void *a);
extern int func_020036e8(void *a);
extern int func_0202da38(void *self, void *p104, void *p122, int d, int e, int offset, int scale, int h, int i);
extern void func_02015e10(void *self, void *q, int flag);
extern int func_0202bd7c(void *self, int i, unsigned char val);

void func_0202b94c(UnkStruct_0202b94c_2 *self, UnkStruct_0202b94c_3 *out)
{
    UnkStruct_0202b94c_4 ls;
    int someVal;
    unsigned int idx;
    void *p;
    void *q;
    int i;

    ls = data_020d8f40;
    someVal = func_020036e8(func_0208150c(self->unk_100->unk_830));
    idx = 0;
    func_0202d8f8(self, (void *) &self->unk_12C, (void *) &self->unk_128, self->unk_100->unk_830, 0);

    if (func_0201ce50(self->unk_100) != 0) {
        p = func_0201ce50(self->unk_100)->unk_830;
        idx = func_020036e8(func_0208150c(p));
        func_0202d8f8(self, (void *) &self->unk_134, (void *) &self->unk_130, p, 0);
    }

    if (idx < 6) {
        ls.a = data_020d9d4c[idx];
    }

    if (ls.a != 0) {
        func_0202da38(self, (void *) &self->arr_104, (void *) &self->unk_122, 0x1e, someVal, ls.a, ls.b, 0, 0);
        out->ptr = (void *) &self->arr_104;
        out->byte = self->unk_122;
    }

    out->ptr = (void *) &self->arr_104;
    out->byte = self->unk_122;

    q = func_0208150c(self->unk_100->unk_830);
    func_02015e10(self, q, 0);

    if (func_0201ce50(self->unk_100) != 0) {
        p = func_0201ce50(self->unk_100)->unk_830;
        q = func_0208150c(p);
        func_02015e10(self, q, 1);
    }

    for (i = 0; i < 5; i++) {
        func_0202bd7c(self, i + 2, data_020c8940[i]);
    }
}
