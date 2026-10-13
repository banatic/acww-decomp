/* func_02012844 @ 0x02012844, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *a, int *b, int c);

struct UnkStruct_02012844 {
    char pad_00[0xC];
    int unk_0C;
    int unk_10;
};

int func_02012844(struct UnkStruct_02012844 *p, int c)
{
    int a = 0;
    int b = 0;
    func_0204f818(&a, &b, c);
    if (a == p->unk_0C && b == p->unk_10) {
        return 1;
    }
    return 0;
}
