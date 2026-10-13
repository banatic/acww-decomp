/* func_ov004_02243048 @ 0x02243048, 0xb0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02243048 {
    char unk_00[0xac];
    short unk_AC;
    char unk_AE[0x154 - 0xae];
    unsigned long unk_154;
    char unk_158[0x168 - 0x158];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
    int unk_174;
    char unk_178[0x192 - 0x178];
    short ang;
} UnkStruct_02243048;

extern int func_ov004_02242fe8(UnkStruct_02243048 *self);
extern void func_ov004_02242f1c(UnkStruct_02243048 *self);
extern int func_ov004_02244c20(UnkStruct_02243048 *self);
extern int func_020e8870(short *a, int b, int c);
extern void func_020550e4(void *p, int a);
extern int func_020644cc(int a);

void func_ov004_02243048(UnkStruct_02243048 *self)
{
    short t;

    switch (self->unk_172) {
        case 3:
            if (func_ov004_02242fe8(self) != 0) {
                t = self->ang;
                if (func_020e8870(&t, self->unk_AC, 0x38e) != 0) {
                    self->unk_172 = 4;
                }
                self->ang = t;
            }
            break;
        case 4:
            func_ov004_02242f1c(self);
            break;
        default:
            if (func_ov004_02244c20(self) != 0 && func_ov004_02242fe8(self) != 0) {
                if (((self->unk_154 << 4) >> 16) != 1) {
                    func_020550e4((char *) self + 0xb0, 1);
                }
                self->unk_168 = 0;
                self->unk_172 = 4;
                self->unk_174 = (func_020644cc(9) + 4) * 0x14;
            }
            break;
    }
}
