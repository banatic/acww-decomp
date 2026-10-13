/* func_02089b20 @ 0x02089b20, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a07c(void *p);
extern int data_020e2030;

struct UnkStruct_02089b20 {
    void *unk_00;
};

struct UnkStruct_02089b20 *func_02089b20(struct UnkStruct_02089b20 *arg)
{
    arg->unk_00 = &data_020e2030;
    func_0208a07c(arg);
    return arg;
}
