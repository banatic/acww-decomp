/* func_ov003_022174a4 @ 0x022174a4, 0xec bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern unsigned int *func_0200f27c(void *self, int a);
extern void func_0200f268(void *self, int a);
extern int func_ov003_022188d0(void *self, int a, int b, short c, int d, int e);
extern int func_ov003_022186cc(void *self, unsigned char k, int a, int b, short c, int d, int e);
extern int func_02008258(void *self, int a);
extern int func_0200c3b0(void *self, int a, int b, int c);
extern int func_0203e110(void);
extern int func_0200d4e8(void *self, int a, int b, int c);

typedef struct {
    int kind;
    int unk_04;
    int unk_08;
    short unk_0C;
    unsigned char unk_0E;
} UnkStruct_022174a4;

typedef struct {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x7d4 - 0x2d4];
    UnkStruct_022174a4 q;
    char pad_7E4[0x7f0 - 0x7e4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
} UnkStruct_022174a4_2;

void func_ov003_022174a4(UnkStruct_022174a4_2 *self)
{
    UnkStruct_022174a4 *q;

    q = &self->q;
    if (func_02056f94(&self->unk_2D0) == 0) {
        return;
    }
    func_0200f27c(self, 1);
    switch (q->kind) {
        case 0x38:
            func_0200f268(self, 0);
            func_ov003_022188d0(self, q->unk_04, q->unk_08, q->unk_0C, 6, -1);
            break;
        case 0x39:
            func_0200f268(self, 0);
            func_ov003_022186cc(self, (unsigned char) ((q->unk_0E & 0xc) >> 2), q->unk_04, q->unk_08, q->unk_0C, 6, -1);
            break;
        case 0x10:
            func_0200f268(self, 0);
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200c3b0(self, 3, 5, -1);
            break;
        case 2:
            func_0203e110();
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            break;
    }
}
