/* func_02034150 @ 0x02034150, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ea6e0(void *ptr, int value);

typedef struct {
    char pad_00[0x24];
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_02034150;

void func_02034150(UnkStruct_02034150 *obj, int a, int b, int c)
{
    int val;
    b -= a;
    val = 0;
    obj->unk_24 = val;
    obj->unk_28 = val;
    obj->unk_2C = 0x1000;
    if (b <= 0) {
        val = 0x8000;
    }
    func_020ea6e0(&obj->unk_24, (short) (c + (short) val));
}
