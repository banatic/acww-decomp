/* func_ov003_02210c08 @ 0x02210c08, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020778b0(void *p, int a2);

struct UnkStruct_02210c08 {
    char pad_00;
    char pad_01;
    char unk_02;
    char unk_03;
    char unk_04;
};

void func_ov003_02210c08(struct UnkStruct_02210c08 *p, int a2, char a3, char a4, unsigned char a5)
{
    func_020778b0(p, a2);
    p->unk_02 = a3;
    p->unk_03 = a4;
    p->unk_04 = a5;
}
