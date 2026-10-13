/* func_02039510 @ 0x02039510, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct El El;
struct El {
    char pad_00[0xc];
    void *unk_0C;
    char pad_10[0x34];
    int unk_44;
};

typedef struct UnkStruct_02039510 UnkStruct_02039510;
struct UnkStruct_02039510 {
    char pad_00[0x2f4];
    El *array[4];
};

void func_02039510(UnkStruct_02039510 *param)
{
    int idx;
    int val;
    El *el;

    idx = 3;
    val = 0;

    do {
        el = param->array[idx];
        if (el != 0 && el->unk_0C != 0) {
            el->unk_44 = val;
            val += 0x10;
        }
    } while (--idx >= 0);
}
