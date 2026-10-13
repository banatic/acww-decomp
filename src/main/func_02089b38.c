/* func_02089b38 @ 0x02089b38, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e2030;

typedef struct {
    unsigned char *unk_00;
} UnkStruct_02089b38;

extern void func_0208a07c(UnkStruct_02089b38 *arg);

UnkStruct_02089b38 *func_02089b38(UnkStruct_02089b38 *arg)
{
    arg->unk_00 = &data_020e2030;
    func_0208a07c(arg);
    return arg;
}
