/* func_020ab348 @ 0x020ab348, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ab51c(int param);

typedef struct {
    char pad_00[0x20];
    int unk_20;
} UnkStruct_020ab348;

void func_020ab348(UnkStruct_020ab348 *obj)
{
    func_020ab51c(obj->unk_20);
}
