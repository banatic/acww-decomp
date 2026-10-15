/* func_ov120_0229a4bc @ 0x0229a4bc, 0xc8 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229a448(void *p, int n);
extern void func_ov120_0229adc4(void *p, unsigned char n);
extern void func_ov120_0229b22c(void *p);
extern void func_ov120_0229b214(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void *func_0208e95c(void *p, int n);
extern void func_ov120_0229a438(void *p, int n);

struct UnkStruct_0229a4bc {
    unsigned char pad_00[0xa3];
    unsigned char unk_A3;
    unsigned char pad_A4[7];
    unsigned char unk_AB;
    unsigned char unk_AC;
};

int func_ov120_0229a4bc(struct UnkStruct_0229a4bc *s)
{
    unsigned char v;

    if (func_ov120_0229a448(s, 0x800) != 0) {
        func_ov120_0229adc4(s, (unsigned char) (s->unk_AC + 1));
        return 0;
    }

    v = s->unk_AB;

    if (v == 8) {
        func_ov002_02208098(s, 6);
        func_0208e95c((char *) s + 0x674, 2);
        func_ov120_0229a438(s, 0x1000);
        return 1;
    } else if (v == 0) {
        if (func_ov120_0229a448(s, 1) != 0) {
            func_ov120_0229adc4(s, 0);
            func_ov120_0229b22c(s);
            return 2;
        }
        return 0;
    } else if (v == 1) {
        if (func_ov120_0229a448(s, 1) == 0) {
            func_ov120_0229adc4(s, 0);
            func_ov120_0229b214(s);
            return 2;
        }
        return 0;
    } else if (v >= 2 && v <= 7) {
        func_ov120_0229adc4(s, (unsigned char) (s->unk_A3 + v + 0xd));
        return 0;
    }

    return 0;
}
