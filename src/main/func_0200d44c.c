/* func_0200d44c @ 0x0200d44c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(int, int);
extern int data_020ccf94;

struct UnkStruct_0200d44c {
    char pad_00[0x7f8];
    int unk_7F8;
    char pad_7FC[4];
    int unk_800;
};

void func_0200d44c(struct UnkStruct_0200d44c *s)
{
    if (func_02073908(data_020ccf94, s->unk_800) == 0) {
        s->unk_7F8 = 1;
    }
}
