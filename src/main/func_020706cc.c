/* func_020706cc @ 0x020706cc, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020706cc {
    unsigned char pad_00[0x8e];
    short unk_8E;
} UnkStruct_020706cc;

extern unsigned char data_020e54a8;
extern UnkStruct_020706cc *func_020961a8(int);
extern int func_ov003_0222ea84(int);
extern void func_ov003_0222e898(int, int);
extern void func_ov003_0222eabc(int, int);

void func_020706cc(unsigned char *p, int a1)
{
    unsigned int ok;
    int v;
    short acc;
    unsigned char *q;
    UnkStruct_020706cc *o;

    if (data_020e54a8 == 0) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok > 0) {
        q = p + 1;
        v = (unsigned char) a1;
        acc = (short) ((p[2] - 0x1e) * 0xb6);
        o = func_020961a8(v);
        if (o != 0) {
            acc = (short) (acc + o->unk_8E);
            if (func_ov003_0222ea84(v) == 0) {
                func_ov003_0222e898(*q, v);
                func_ov003_0222eabc(v, acc);
            }
        }
    }
}
