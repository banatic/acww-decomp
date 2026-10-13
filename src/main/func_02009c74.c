/* func_02009c74 @ 0x02009c74, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
} UnkStruct_02009c74;
typedef struct {
    int unk_00;
    unsigned short unk_04;
    unsigned char unk_06;
} UnkStruct_02009c74_2;

extern unsigned char data_020e54a8;

extern void func_020110c4(UnkStruct_02009c74 *p, void *self);
extern void *func_02011368(void *self);
extern void func_0209971c(void *o, unsigned short *p);
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_0200f328(void *self, int k);
extern void func_02009d30(char *p, unsigned short v);

void func_02009c74(void *self, char *a1, int a2)
{
    UnkStruct_02009c74 loc;
    void *o;
    unsigned int ok;
    UnkStruct_02009c74_2 *p;
    unsigned short *q;

    q = (unsigned short *) (a1 + 0xc);
    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok != 0) {
        func_020110c4(&loc, self);
        o = func_02011368(self);
        loc.unk_02 = 0xfff1;
        func_0209971c(o, &loc.unk_02);
        func_020109a0(self, 0x13, 5, 5);
        func_0209971c(o, &loc.unk_00);
    }
    p = (UnkStruct_02009c74_2 *) ((char *) self + 0x7d4);
    p->unk_00 = 0x1000;
    p->unk_04 = *q;
    if (a2 == 0x10) {
        p->unk_06 = 1;
    } else {
        p->unk_06 = 0;
    }
    if (p->unk_04 != 0xfff1) {
        func_0200f328(self, 0x31);
    } else {
        func_0200f328(self, 0x78);
    }
    func_02009d30((char *) self + 0x8f0, *q);
}
