/* func_0205ef90 @ 0x0205ef90, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020606bc(void *ptr);
extern void func_0205eff4(void *ptr);

struct UnkStruct_0205ef90 {
    char pad_00[8];
    char unk_08;
    char pad_09[31];
    char unk_28;
};

void *func_0205ef90(struct UnkStruct_0205ef90 *arg)
{
    func_020606bc(&arg->unk_28);
    func_0205eff4(&arg->unk_08);
    return arg;
}
