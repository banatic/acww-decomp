/* func_ov048_02261514 @ 0x02261514, 0x2c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xB4];
    int count;
} UnkStruct_02261514;

extern int func_0209ff0c(UnkStruct_02261514 *p);
extern void func_ov048_022616b8(UnkStruct_02261514 *p, int value);

void func_ov048_02261514(UnkStruct_02261514 *p)
{
    if (func_0209ff0c(p)) {
        func_ov048_022616b8(p, p->count + 1);
    } else {
        func_ov048_022616b8(p, p->count + 2);
    }
}
