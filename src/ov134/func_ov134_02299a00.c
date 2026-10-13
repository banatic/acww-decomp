/* func_ov134_02299a00 @ 0x02299a00, 0x14 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208ea70(void *, int, int);

struct UnkStruct_02299a00 {
    char pad_00[0x60];
    int unk_60;
    int unk_64;
};

int func_ov134_02299a00(struct UnkStruct_02299a00 *arg)
{
    return func_0208ea70((char *) arg + 0x18, arg->unk_60 - 0x78, arg->unk_64 - 0x60);
}
