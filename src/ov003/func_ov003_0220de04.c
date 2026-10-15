/* func_ov003_0220de04 @ 0x0220de04, 0x200 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} Node;

typedef struct UnkStruct_0220de04 {
    char pad_00[0x8e];
    signed short unk_8E;
    char pad_90[0x10a - 0x90];
    unsigned char unk_10A;
    char pad_10B[0x12c - 0x10b];
    Node *unk_12C;
    char pad_130[0x704 - 0x130];
    unsigned int event;
    char pad_708[0x7d4 - 0x708];
    unsigned char state;
    char pad_7D5[0x7f0 - 0x7d5];
    unsigned int unk_7F0;
    char pad_7F4[0x7fc - 0x7f4];
    unsigned int unk_7FC;
} UnkStruct_0220de04;

extern int func_02056f94(void *);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern int func_0200faa8(void *, int);
extern int func_0200f328(void *, int);
extern void *func_020984e8(void);
extern void func_02099740(void *, int);
extern int func_0209984c(void *);
extern int func_0205dc94(void *, int);
extern int func_02099020(void *, int);
extern void func_02098ff8(void *, int);
extern int func_0200faf0(void *, int);
extern void func_02035624(int);
extern void func_020356c4(int, int, int, int);
extern void func_0203ee14(void *self, void *arg);
extern unsigned int *func_0200f27c(void *, int);
extern void func_020a8164(void *, void *);
extern void func_0203ae98(void);
extern void func_0203ee08(void *, void *);
extern void func_0200f268(void *, int);
extern int func_0203e19c(void);
extern unsigned int func_02008258(void *, unsigned int);
extern int func_0200d4e8(void *, int, int, int);
extern int func_0203b144(void);
extern void func_02035638(int);
extern void func_02035684(int, int, int);
extern char data_ov003_02238134[];

void func_ov003_0220de04(UnkStruct_0220de04 *self)
{
    volatile unsigned char scratch[8];
    unsigned char *st;
    signed short cur;
    void *p;
    int v;
    char *sub;

    (void) &scratch;
    switch (self->event) {
        case 0x71:
            if (func_02056f94((char *) self + 0x2d0) != 0) {
                func_020109a0(self, 0x72, 0, 0);
            }
            break;
        case 0x72:
            func_0200faa8(self, 0x3ae);
            if (func_02056f94((char *) self + 0x2d0) != 0) {
                func_020109a0(self, 0x73, 0, 0);
            }
            break;
        case 0x73:
            if (func_02056f94((char *) self + 0x2d0) != 0) {
                func_0200f328(self, 0x817);
                func_020109a0(self, 0x74, 0, 0);
                p = func_020984e8();
                if (p != 0) {
                    func_02099740(p, 1);
                    v = func_0209984c(p) + 0x10;
                    func_0205dc94((char *) self + 0x70d, v);
                    if (func_02099020(p, 0x17) != 0) {
                        func_02098ff8(p, 0x19);
                    }
                }
            }
            break;
        case 0x74:
            if (func_02056f94((char *) self + 0x2d0) != 0) {
                func_020109a0(self, 0x75, 0, 0);
            }
            break;
        case 0x75:
            st = (unsigned char *) self + 0x7d4;
            cur = self->unk_8E;
            func_0200faf0(self, 0x59a);
            if (cur != 0 && self->unk_8E == 0) {
                func_02035624(0x19);
                func_020356c4(0xd, 0x40, 0x7f, 1);
            }
            switch (*st) {
                case 0:
                    *st = 1;
                    sub = (char *) self;
                    if (self != 0) {
                        sub = sub + 0xec;
                    }
                    func_0203ee14(self, sub);
                    func_0200f27c(self, 0x11);
                    func_020a8164((char *) self + 0xec, data_ov003_02238134);
                    self->unk_10A = 0x14;
                    self->unk_12C->unk_08 = 1;
                    func_0203ae98();
                case 1:
                    if (self->unk_12C != 0 && self->unk_12C->unk_04 != 0) {
                        *st = 2;
                    }
                    break;
                case 2:
                    if (self->unk_12C != 0 && self->unk_12C->unk_04 == 0) {
                        sub = (char *) self;
                        if (self != 0) {
                            sub = sub + 0xec;
                        }
                        func_0203ee08(self, sub);
                        func_0200f268(self, 0x11);
                        func_0203e19c();
                        self->unk_7FC = func_02008258(self, self->unk_7F0);
                        func_0200d4e8(self, 3, 1, -1);
                        func_0200f268(self, 7);
                        func_0203b144();
                        func_02035638(0x40);
                        func_02035684(0xc, 0xf, 5);
                    }
                    break;
            }
            break;
    }
}
