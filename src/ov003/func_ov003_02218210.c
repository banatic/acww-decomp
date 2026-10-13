/* func_ov003_02218210 @ 0x02218210, 0x120 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc];
    unsigned char byte0;
    unsigned char byte1;
} B_ov003_big;

typedef struct {
    unsigned char pad_00[0x7d4];
    unsigned char dbyte0;
    unsigned char dbyte1;
    unsigned char pad_7D6[0x7f8 - 0x7d6];
    int flagfield;
    unsigned char pad_7FC[0x800 - 0x7fc];
    int fieldBig;
    unsigned char pad_804[0x8f0 - 0x804];
    unsigned char unk_8F0[1];
} Self_ov003_big;

extern void func_0200f268(Self_ov003_big *self, int flag);
extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern int func_ov003_022203ac(void);
extern void *func_020984e8(void);
extern int func_020b65c4(void *d);
extern int func_02099020(void *d, int a);
extern void *func_020b65b8(void);
extern int func_020b67e8(void *g);
extern void *func_0208602c(void);
extern int func_02086108(void *i, int a);
extern void func_020109a0(Self_ov003_big *self, int a, int b, int c);
extern int func_020b29c0(void *p);
extern void func_020109fc(Self_ov003_big *self, int a, int b, int c);
extern void func_ov003_0221833c(void *field3, int a, int b);
extern void func_ov003_02220368(Self_ov003_big *self);

void func_ov003_02218210(Self_ov003_big *self, B_ov003_big *b)
{
    int local0;
    void *gv;
    int kind;
    int caseResult;
    void *dres, *gres, *ires;
    unsigned char *destp;
    unsigned char *bsub;

    func_0200f268(self, 0);

    bsub = &b->byte0;
    destp = &self->dbyte0;
    kind = 0;
    gv = data_020ccf94;

    if (func_02073908(gv, self->fieldBig)) {
        local0 = func_ov003_022203ac();
    } else {
        local0 = bsub[0];
    }

    if (func_02073908(gv, self->fieldBig)) {
        dres = func_020984e8();
        if (func_020b65c4(dres) != 0) {
            goto L_else;
        }
        if (dres == 0) {
            goto L_else;
        }
        if (func_02099020(dres, 0x23) == 0) {
            goto L_else;
        }
        gres = func_020b65b8();
        if (func_020b67e8(gres) != 0) {
            goto L_kind1;
        }
        if ((int) func_020b65b8() != 6) {
            goto L_else;
        }
    L_kind1:
        kind = 1;
        goto L_after;

    L_else:
        ires = func_0208602c();
        if (func_02086108(ires, 0) != 0) {
            kind = 2;
            goto L_after;
        }
        ires = func_0208602c();
        if (func_02086108(ires, 5) != 0) {
            kind = 3;
        }
    L_after:;
    } else {
        kind = bsub[1];
    }

    if (local0 != 0) {
        func_020109a0(self, 0x34, 0, 0);
        caseResult = 0;
        self->flagfield = 1;
    } else {
        int lres = func_020b29c0((unsigned char *) self + 0x5c);
        caseResult = (unsigned char) lres;
        if ((unsigned int) caseResult <= 1) {
            func_020109a0(self, 0x35, 0, 0);
        } else {
            func_020109fc(self, 0x36, 0, 0);
        }
        self->flagfield = 1;
    }

    destp[1] = (unsigned char) caseResult;
    destp[0] = (unsigned char) kind;
    func_ov003_0221833c((unsigned char *) self + 0x8f0, local0, kind);

    self = (Self_ov003_big *) ((unsigned char *) self + 0x5c);
    func_ov003_02220368(self);
}
