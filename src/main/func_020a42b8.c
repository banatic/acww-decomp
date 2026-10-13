/* func_020a42b8 @ 0x020a42b8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a42b8 {
    unsigned char pad_00[0xa1];
    unsigned char unk_A1;
};

extern int func_020984e8(struct UnkStruct_020a42b8 *p);
extern void func_02098fd0(int a, int b);

void func_020a42b8(struct UnkStruct_020a42b8 *p)
{
    func_02098fd0(func_020984e8(p), 2);
    p->unk_A1 = 0;
}
