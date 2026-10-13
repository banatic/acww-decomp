/* func_ov003_0221ed60 @ 0x0221ed60, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bb80(void *addr);

typedef struct {
    char pad_00[0x136];
    char unk_136;
    char pad_137[0x2b4 - 0x136 - 1];
    int unk_2B4;
} UnkStruct_0221ed60;

int func_ov003_0221ed60(UnkStruct_0221ed60 *this)
{
    this->unk_2B4 = func_0204bb80(&this->unk_136);
    return 1;
}
