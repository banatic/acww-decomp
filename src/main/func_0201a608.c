/* func_0201a608 @ 0x0201a608, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_02018fdc(int);
extern void func_020044b0(int, int, int, int);
extern void func_020044c0(int, int, int, int);
extern void func_0200455c(int);
extern void func_0200456c(int);

struct UnkStruct_0201a608 {
    char pad_00[0x18];
    int unk_18;
    char pad_1C[8];
    unsigned char unk_24;
    unsigned char unk_25;
    unsigned char unk_26;
};

void func_0201a608(struct UnkStruct_0201a608 *a, unsigned char *b)
{
    unsigned char *p = func_02018fdc(a->unk_25);
    if (b[3] == 1 || a->unk_24 == 2) {
        a->unk_24 = p[0x19];
        if (a->unk_24 == 1) {
            if (a->unk_26 == 0) {
                func_020044b0(a->unk_18, a->unk_25 + 0x84, 0x7f, 0);
            } else {
                func_0200455c((unsigned short) (a->unk_25 + 0x84));
            }
        } else {
            if (a->unk_26 == 0) {
                func_020044c0(a->unk_18, a->unk_25 + 0x84, 0x7f, 0);
            } else {
                func_0200456c((unsigned short) (a->unk_25 + 0x84));
            }
        }
    }
}
