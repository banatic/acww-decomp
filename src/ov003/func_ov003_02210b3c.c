/* func_ov003_02210b3c @ 0x02210b3c, 0xcc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f794(int *out, int a, int b);
extern int func_02073908(int a, int b);
extern int func_02043d18(int a, int b, int c, unsigned short d);
extern int func_020e8ed8(int a, int b);
extern void func_ov003_02210c08(void *p, int h, unsigned char b, unsigned char c, int k);
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_0200f268(void *self, int a);

extern int data_020ccf94;

typedef struct {
    unsigned short h;
    unsigned char unk_02, unk_03, unk_04;
} UnkStruct_02210b3c_3;
typedef struct {
    char pad_00[0xc];
    UnkStruct_02210b3c_3 s;
} UnkStruct_02210b3c;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char unk_04, unk_05, unk_06, unk_07;
} UnkStruct_02210b3c_2;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x64 - 0x60];
    int unk_64;
    char pad_68[0x704 - 0x68];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    UnkStruct_02210b3c_2 q;
    char pad_7DC[0x800 - 0x7dc];
    int unk_800;
    char pad_804[0x80c - 0x804];
    int unk_80C;
    char pad_810[0x820 - 0x810];
    unsigned short unk_820;
    char pad_822[0x8f0 - 0x822];
    int unk_8F0;
} UnkStruct_02210b3c_4;

void func_ov003_02210b3c(UnkStruct_02210b3c_4 *self, UnkStruct_02210b3c *a)
{
    UnkStruct_02210b3c_3 *p;
    UnkStruct_02210b3c_2 *q;
    int h;
    int kind, c, d;
    int out[3];

    p = &a->s;
    q = &self->q;
    kind = p->unk_04;
    c = p->unk_02;
    d = p->unk_03;
    func_0204f794(out, c, d);
    h = p->h;
    if (kind == 2) {
        if (func_02073908(data_020ccf94, self->unk_800) != 0) {
            self->unk_80C = func_02043d18(self->unk_800, 2, 0, self->unk_820);
        }
    } else {
        if (self->unk_704 == 0x6c) {
            kind = 3;
        }
    }
    q->unk_00 = h;
    q->unk_05 = c;
    q->unk_06 = d;
    q->unk_04 = kind;
    q->unk_07 = 0;
    q->unk_02 = func_020e8ed8(out[0] - self->unk_5C, out[2] - self->unk_64);
    func_ov003_02210c08(&self->unk_8F0, h, c, d, kind);
    func_020109a0(self, 0x49, 7, 0);
    func_0200f268(self, 0xd);
}
