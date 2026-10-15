/* func_02098cf8 @ 0x02098cf8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xA68];
    int unk_A68;
} Struct02098cf8;

extern int func_02098d84(Struct02098cf8 *obj);

int func_02098cf8(Struct02098cf8 *obj, int param)
{
    int value = obj->unk_A68;
    if (param) {
        value += func_02098d84(obj);
    }
    return value;
}
