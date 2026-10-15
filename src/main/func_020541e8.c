/* func_020541e8 @ 0x020541e8, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02054170(void *);
extern int func_02054ecc(int);
extern void func_02054240(void *, int, int, unsigned char, unsigned int, unsigned int, int, int);

typedef struct {
    char pad_00[0xa4];
    unsigned int unk_A4;
    char pad_A8[4];
    unsigned int unk_AC;
    unsigned char unk_B0;
} UnkStruct_020541e8;

void func_020541e8(UnkStruct_020541e8 *a, int b, int c)
{
    if (b == 0) {
        func_02054170(a);
        return;
    }
    func_02054240(a, func_02054ecc((int) a), b, a->unk_B0, a->unk_AC, (a->unk_A4 << 4) >> 16, c, 1);
}
