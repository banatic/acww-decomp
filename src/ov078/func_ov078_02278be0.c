/* func_ov078_02278be0 @ 0x02278be0, 0x238 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

typedef struct Msg {
    unsigned char code;
    unsigned char pad_01;
    unsigned short a;
    unsigned short b;
    unsigned short c;
    unsigned short d;
} Msg;

typedef struct Fmt {
    int w[2];
} Fmt;

typedef struct UnkStruct_02278be0 {
    int w[9];
} UnkStruct_02278be0;

typedef struct UnkStruct_02278be0_2 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
    unsigned short unk_B8;
    unsigned short unk_BA;
} UnkStruct_02278be0_2;

extern int data_ov078_02279bd8;

extern void func_02094fd4(UnkStruct_02278be0 *t);
extern void func_02094fbc(UnkStruct_02278be0 *t);
extern void func_020984e8(void);
extern void func_02099640(void);
extern void *func_0209a850(void);
extern int func_02099fe8(void);
extern void func_0209b0f4(void *o);
extern void *func_0209b0f0(void *o);
extern unsigned short *func_0209bb70(void *o);
extern int func_0204bcdc(void);
extern int func_0204bc64(unsigned short *p);
extern int func_0209a000(unsigned short *p, int a);
extern void func_020154b4(UnkStruct_02278be0_2 *self, unsigned short *p, int a, int b, int c);
extern int func_0209b0c4(void *o, UnkStruct_02278be0 *t);
extern void func_02068404(int a, int b, UnkStruct_02278be0 *t);
extern void func_02063ccc(Fmt *f, int a, int b);
extern void func_020638d4(unsigned short *p, Fmt *f, int a, int b, int c, int d, int e);
extern void func_02063cc8(Fmt *f);
extern void func_02015de4(UnkStruct_02278be0_2 *self, unsigned short *p, int a, int b);
extern void func_0209bb90(void *o, int a);
extern void func_0204093c(int a);
extern int func_020644cc(int a);
extern void func_0206844c(int a, Msg *m, int *t);

void func_ov078_02278be0(UnkStruct_02278be0_2 *self)
{
    Msg m;
    Fmt s[2];
    UnkStruct_02278be0 tmp;
    void *obj;
    unsigned short *p;
    int n;
    unsigned int ok;
    int status;
    int *tail;

    m.a = 0xfff1;
    func_02094fd4(&tmp);
    func_020984e8();
    func_02099640();
    obj = func_0209a850();
    tail = &data_ov078_02279bd8;
    status = 0;
    switch (self->unk_1E) {
        case 5:
        case 0xa:
            if (func_02099fe8() < 0) {
                status = 0x1d;
                break;
            }
            if (self->unk_1E == 5) {
                func_0209b0f4(obj);
            }
            p = func_0209bb70(func_0209b0f0(obj));
            if (func_0204bcdc() != 0) {
                m.d = 0x155f;
                n = func_0204bc64(p);
                ok = (n == func_0204bc64(&m.d));
            } else {
                ok = (*p == 0x155f);
            }
            if (ok > 0) {
                status = 6;
            } else {
                status = 7;
            }
            if (self->unk_1E != 0xa) {
                break;
            }
        case 6:
        case 7:
            func_0209a000(func_0209bb70(func_0209b0f0(obj)), 2);
            func_020154b4(self, func_0209bb70(func_0209b0f0(obj)), 2, 5, 0);
            if (func_0209b0c4(obj, &tmp) != 0) {
                func_02068404(self->unk_40, 0, &tmp);
            }
            if (self->unk_1E != 0xa) {
                status = 8;
            } else {
                status = 0xb;
            }
            break;
        case 0xc:
            func_02063ccc(&s[0], 4, 0x23);
            func_020638d4(&m.b, &s[0], 0, 0, 1, 1, 0);
            self->unk_B8 = m.b;
            func_02063cc8(&s[0]);
            func_02015de4(self, &self->unk_B8, 1, 7);
            func_02063ccc(&s[1], 3, 0x23);
            func_020638d4(&m.c, &s[1], 0, 0, 1, 1, 0);
            self->unk_BA = m.c;
            func_02063cc8(&s[1]);
            func_02015de4(self, &self->unk_BA, 2, 7);
            status = 0xd;
            break;
        case 0xe:
            func_0209bb90(func_0209b0f0(obj), 3);
            func_0204093c(0x3e);
            break;
        case 0x15:
            self->unk_B4 = -2;
            break;
        case 0x16:
            m.a = 0x37e0;
            status = 0x17;
            if (func_020644cc(2) == 0) {
                m.a = 0x34a8;
                status = 0x18;
            }
            self->unk_B4 = -2;
            func_02015de4(self, &m.a, 0, 7);
            func_020154b4(self, &m.a, 0, 5, 0);
            func_0209a000(&m.a, 0);
            break;
    }
    if (status != 0) {
        m.code = (unsigned char) status;
        func_0206844c(self->unk_40, &m, tail);
    }
    func_02094fbc(&tmp);
}
