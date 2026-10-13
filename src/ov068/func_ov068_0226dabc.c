/* func_ov068_0226dabc @ 0x0226dabc, 0x14c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x174];
    short unk_174;
    char pad_176[0x21c - 0x176];
    short unk_21C;
    short unk_21E;
    unsigned char unk_220;
    unsigned char pad_221;
    unsigned char unk_222;
    unsigned char pad_223;
    unsigned char unk_224;
    unsigned char unk_225;
} UnkStruct_0226dabc;

extern int func_020e8840(void *);
extern int func_020644cc(int);
extern int FX_MulFunc(int, int);
extern void func_ov068_0226dc64(UnkStruct_0226dabc *, int);
extern void func_ov068_0226dc08(UnkStruct_0226dabc *, int);
extern unsigned char data_020ca180[];
extern unsigned char data_020ca184[];
extern unsigned char FX_SinCosTable_[];

int func_ov068_0226dabc(UnkStruct_0226dabc *self)
{
    short val, val2, s5, s4, t, t2;
    unsigned char b, b2, b5, b4;
    unsigned char *p224, *p225;
    int idx5, idx5b, idx4, idx4b, q, q2, r, r2, w, w2, res, res2, r0, sum, sum2;

    if (func_020e8840(&self->unk_220) == 0) {
        val = self->unk_21C;
        if (val < 0) {
            val = -val;
        }
        if (val < 0x100) {
            b = self->unk_224;
            if (b == 0) {
                r0 = func_020644cc(0x64);
                if (r0 < 0x50) {
                    self->unk_224 = 1;
                } else {
                    self->unk_224 = 2;
                }
            } else {
                if (b == 2) {
                    self->unk_224 = 1;
                } else {
                    self->unk_224 = 0;
                }
            }
            func_ov068_0226dc64(self, self->unk_224);
        }
    }

    if (func_020e8840(&self->unk_222) == 0) {
        val2 = self->unk_21E;
        if (val2 < 0) {
            val2 = -val2;
        }
        if (val2 < 0x100) {
            b2 = self->unk_225;
            if (b2 == 0) {
                self->unk_225 = 1;
            } else {
                if (b2 == 2) {
                    self->unk_225 = 1;
                } else {
                    self->unk_225 = 0;
                }
            }
            func_ov068_0226dc08(self, self->unk_225);
        }
    }

    p225 = &self->unk_225;
    b5 = *p225;
    idx5 = b5 * 12;
    s5 = *(short *) (data_020ca180 + idx5);
    if (s5 != 0) {
        sum = self->unk_21E + (int) s5;
        self->unk_21E = (short) sum;
        q = (unsigned short) self->unk_21E >> 4;
        r = q * 4;
        t = *(short *) (FX_SinCosTable_ + r);
        b5 = *p225;
        idx5b = b5 * 12;
        w = *(int *) (data_020ca184 + idx5b);
        res = FX_MulFunc(t, w);
        self->unk_174 = (short) res;
    }

    p224 = &self->unk_224;
    b4 = *p224;
    idx4 = b4 * 12;
    s4 = *(short *) (data_020ca180 + idx4);
    if (s4 != 0) {
        sum2 = self->unk_21C + (int) s4;
        self->unk_21C = (short) sum2;
        q2 = (unsigned short) self->unk_21C >> 4;
        r2 = q2 * 4;
        t2 = *(short *) (FX_SinCosTable_ + r2);
        b4 = *p224;
        idx4b = b4 * 12;
        w2 = *(int *) (data_020ca184 + idx4b);
        res2 = FX_MulFunc(t2, w2);
        return res2;
    } else {
        return 0;
    }
}
