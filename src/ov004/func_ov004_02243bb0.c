/* func_ov004_02243bb0 @ 0x02243bb0, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02243bb0 {
    char unk_00[0x98];
    short unk_98;
    signed char unk_9A;
    char unk_9B[0x168 - 0x9b];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
} UnkStruct_02243bb0;

extern void func_ov004_02243af4(UnkStruct_02243bb0 *self, short *n);
extern void func_ov004_022439ec(UnkStruct_02243bb0 *self, short *n);

void func_ov004_02243bb0(UnkStruct_02243bb0 *self)
{
    short *p;
    short v;
    switch (self->unk_172) {
        case 3:
        case 0xf:
            func_ov004_02243af4(self, &self->unk_168);
            break;
        case 4:
            func_ov004_022439ec(self, &self->unk_168);
            break;
        default:
            p = &self->unk_98;
            v = self->unk_98;
            if (v <= 0) {
                self->unk_172 = 3;
            } else {
                *p = v - 1;
            }
            self->unk_9A = 0;
            break;
    }
}
