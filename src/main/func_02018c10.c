/* func_02018c10 @ 0x02018c10, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x98];
    unsigned char unk_98;
} UnkStruct_02018c10;

extern int func_020164cc(int, int);
extern void func_02019af0(UnkStruct_02018c10 *, int);

void func_02018c10(UnkStruct_02018c10 *obj, int arg1)
{
    if (obj->unk_98 >= 1) {
        if (func_020164cc(arg1 + 0x334, arg1)) {
            func_02019af0(obj, 1);
        }
    }
}
