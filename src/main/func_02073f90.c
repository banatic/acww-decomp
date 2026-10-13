/* func_02073f90 @ 0x02073f90, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x68];
    unsigned int unk_68;
} UnkStruct_02073f90;

extern void func_020738e8(UnkStruct_02073f90 *ptr);
extern void func_020732e4(UnkStruct_02073f90 *ptr, int value);
extern void func_020732cc(UnkStruct_02073f90 *ptr, int value);

void func_02073f90(UnkStruct_02073f90 *ptr)
{
    ptr->unk_68 = 4;
    func_020738e8(ptr);
    func_020732e4(ptr, 0);
    func_020732cc(ptr, 0);
}
