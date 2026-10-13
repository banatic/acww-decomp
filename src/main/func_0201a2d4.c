/* func_0201a2d4 @ 0x0201a2d4, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x80];
    int unk_80;
} UnkStruct_0201a2d4;

extern int func_0201a798(UnkStruct_0201a2d4 *ptr);

void func_0201a2d4(UnkStruct_0201a2d4 *ptr)
{
    ptr->unk_80 = func_0201a798(ptr);
}
