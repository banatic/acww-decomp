/* func_02036f08 @ 0x02036f08, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02036f08 {
    unsigned char pad_00[0x15];
    unsigned char flag;
};

extern void func_02036a30(struct UnkStruct_02036f08 *);
extern void func_02036ddc(struct UnkStruct_02036f08 *);

void func_02036f08(struct UnkStruct_02036f08 *arg)
{
    if (arg->flag) {
        func_02036a30(arg);
        func_02036ddc(arg);
    }
}
