/* func_02095f58 @ 0x02095f58, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x514];
    int unk_7F0;
} UnkStruct_02095f58;

extern UnkStruct_02095f58 *func_02096718(int arg);

int func_02095f58(void)
{
    UnkStruct_02095f58 *p;
    p = func_02096718(4);
    if (p != 0 && p->unk_7F0 == 7 && p->unk_2D8 < 0x13000) {
        return 1;
    }
    return 0;
}
