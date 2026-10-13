/* func_02030690 @ 0x02030690, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203072c(void *);

struct UnkStruct_02030690 {
    char pad_00[16];
    int unk_10;
};

struct UnkStruct_02030690 *func_02030690(struct UnkStruct_02030690 *arg)
{
    func_0203072c(arg);
    arg->unk_10 = 0;
    return arg;
}
