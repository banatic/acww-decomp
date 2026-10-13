/* func_0208bf48 @ 0x0208bf48, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203ec98(void *p);
extern unsigned int func_020960d8(int x);

struct UnkStruct_0208bf48 {
    unsigned char pad_00[0x26];
    unsigned char unk_26;
};

int func_0208bf48(struct UnkStruct_0208bf48 *arg)
{
    int r4 = func_0203ec98(arg) != 0;
    unsigned int a = func_020960d8(4);
    int r1 = (a - 8) <= 7;
    int r2 = (a - 0x24) <= 8;
    if (arg->unk_26 != 0 && !r4 && !r1 && !r2) {
        return 1;
    }
    return 0;
}
