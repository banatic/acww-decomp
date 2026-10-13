/* func_02037260 @ 0x02037260, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020371c8(void *);
extern void func_0203710c(void *);

struct UnkStruct_02037260 {
    char unk_00[0x10];
    unsigned char unk_10;
};

void func_02037260(struct UnkStruct_02037260 *arg)
{
    arg->unk_10 = 1;
    func_020371c8(arg);
    func_0203710c(arg);
}
