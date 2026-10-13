/* func_ov003_02219438 @ 0x02219438, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209129c(int);
extern void func_0204fdbc(int);
extern void func_ov003_0222e6c4(unsigned char, int);

typedef struct {
    int pad_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0C;
} UnkStruct_02219438;

void func_ov003_02219438(void *base)
{
    UnkStruct_02219438 *sub = (UnkStruct_02219438 *) ((char *) base + 0x7d4);
    if (sub->unk_04 > -1) {
        func_0209129c(sub->unk_04);
    }
    if (sub->unk_0C == 0) {
        func_ov003_0222e6c4((unsigned char) (*(unsigned int *) ((char *) base + 0x800)), 1);
    } else {
        func_0204fdbc(sub->unk_08);
    }
}
