/* func_02055124 @ 0x02055124, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02055124 {
    char pad_00[0x9c];
    int unk_9C;
    int pad_A0;
    int unk_A4;
    char pad_A8[0xc];
    int *unk_B4;
};

extern void func_02056ffc(void *p);

void func_02055124(struct UnkStruct_02055124 *arg)
{
    int value;
    int *ptr;
    func_02056ffc(&arg->unk_9C);
    value = arg->unk_A4;
    ptr = arg->unk_B4;
    *ptr = value;
}
