/* func_020b7e84 @ 0x020b7e84, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1c];
    int unk_1C;
    int unk_20;
    int unk_24;
} UnkStruct_020b7e84;

extern void func_020b7e9c(UnkStruct_020b7e84 *param, int param2);

void func_020b7e84(UnkStruct_020b7e84 *this)
{
    func_020b7e9c(this, 0);
    this->unk_1C = 0;
    this->unk_20 = 0;
    this->unk_24 = 0;
}
