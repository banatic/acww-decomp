/* func_0200a764 @ 0x0200a764, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Self4 {
    unsigned char pad_00[0x7d4];
    unsigned char unk_7D4;
    unsigned char pad_7D5[1];
    unsigned char unk_7D6;
    unsigned char unk_7D7;
    unsigned char pad_7D8[0x7f0 - 0x7d8];
    int unk_7F0;
    unsigned char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
};

struct Pair {
    int a;
    int b;
};

extern unsigned char data_020e54a8;

extern void func_0200f27c(void *self, int code);
extern void func_02045df8(struct Pair *p, int flags);
extern void func_02045f08(struct Pair *p, int flags);
extern void func_0200f268(void *self, int code);
extern void func_0200f328(void *self, int code);
extern unsigned char func_02008258(void *self, int idx);

void func_0200a764(struct Self4 *self)
{
    unsigned char state, b6, b7;
    unsigned int cond;
    unsigned char *base;

    func_0200f27c(self, 0xd);
    base = (unsigned char *) self + 0x7d4;
    b6 = base[2];
    b7 = base[3];
    state = base[0];
    if (state != 0) {
        struct Pair p1;
        p1.a = b6;
        p1.b = b7;
        func_02045df8(&p1, 0);
    } else {
        struct Pair p2;
        p2.a = b6;
        p2.b = b7;
        func_02045f08(&p2, 0);
    }
    func_0200f268(self, 0x1c);
    cond = (data_020e54a8 != 0) ? 0 : 1;
    if (cond != 0) {
        func_0200f328(self, 0x5d);
    }
    self->unk_7FC = func_02008258(self, self->unk_7F0);
    func_0200f268(self, 0x12);
}
