/* func_ov120_0229a7cc @ 0x0229a7cc, 0x50 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229a448(void *, unsigned int);
extern int func_ov002_0220a4d4(void *);

typedef struct {
    unsigned char pad_00[0xab];
    unsigned char unk_AB;
    unsigned char pad_AC[2];
    unsigned char unk_AE;
} Struct_ov120_0229a7cc;

int func_ov120_0229a7cc(Struct_ov120_0229a7cc *p)
{
    if (func_ov120_0229a448(p, 0x800)) {
        return p->unk_AE;
    } else {
        unsigned char b = p->unk_AB;
        if (b >= 2 && b <= 7) {
            return 0x58 + ((b - 2) << 4);
        } else if (b <= 1) {
            return 0x40;
        } else if (b == 8) {
            return func_ov002_0220a4d4((char *) p + 0x674);
        } else {
            return 0x60;
        }
    }
}
