/* func_020ab338 @ 0x020ab338, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x20];
    int unk_20;
} UnkStruct_020ab338;

extern int func_020ab504(int a);

int func_020ab338(UnkStruct_020ab338 *obj)
{
    return func_020ab504(obj->unk_20);
}
