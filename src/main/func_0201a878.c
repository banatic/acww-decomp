/* func_0201a878 @ 0x0201a878, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1A];
    short unk_1A;
    short unk_1C;
    short unk_1E;
    char pad_20[2];
    short unk_22;
    short unk_24;
    short unk_26;
} Func0201A878Struct;

extern void func_020e8870(short *ptr, int a, int b);

void func_0201a878(Func0201A878Struct *obj)
{
    {
        short a = obj->unk_26;
        if (obj->unk_22 != a) {
            func_020e8870(&obj->unk_22, a, obj->unk_24);
        }
    }
    {
        short b = obj->unk_1E;
        if (obj->unk_1A != b) {
            func_020e8870(&obj->unk_1A, b, obj->unk_1C);
        }
    }
}
