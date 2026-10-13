/* func_ov004_02242d84 @ 0x02242d84, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02242d84 {
    char unk_00[0x22];
    unsigned char unk_22;
    char unk_23[0x9a - 0x23];
    unsigned char unk_9A;
    char unk_9B[0x168 - 0x9b];
    short unk_168;
    char unk_16A[0x172 - 0x16a];
    short unk_172;
} UnkStruct_02242d84;

extern void func_ov004_02242c64(UnkStruct_02242d84 *self);
extern int func_020644cc(int a);
extern void func_02056fcc(void *p, int a, int b, int c, int d);

extern unsigned char data_ov004_02259a24;

void func_ov004_02242d84(UnkStruct_02242d84 *self)
{
    if (self->unk_172 == 0) {
        func_ov004_02242c64(self);
    } else if (self->unk_22 != 0) {
        self->unk_9A = 0;
        self->unk_172 = 0;
        self->unk_168 = 0;
    } else if (data_ov004_02259a24 % 0x28 == 0) {
        if (func_020644cc(0x64) > 0x50) {
            func_02056fcc((char *) self + 0x14c, 8, 1, 0x1000, 0);
        }
    }
}
