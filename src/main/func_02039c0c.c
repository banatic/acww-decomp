/* func_02039c0c @ 0x02039c0c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(int, int);

struct UnkStruct_02039c0c {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x94];
    int unk_A4;
    int unk_A8;
    char pad_AC[8];
    char unk_B4;
};

void func_02039c0c(struct UnkStruct_02039c0c *p)
{
    int res;

    p->unk_A4 = 3;
    p->unk_B4 = 1;
    if (p->unk_0C == 0) {
        res = func_0209d368(0x138, 2) + 2;
    } else {
        res = func_0209d368(0x12e, 2) + 2;
    }
    p->unk_A8 = res;
}
