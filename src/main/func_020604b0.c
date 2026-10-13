/* func_020604b0 @ 0x020604b0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0222ab4c(int x);

struct UnkStruct_020604b0 {
    char pad_00[0x2c];
    int unk_2C;
};

int func_020604b0(struct UnkStruct_020604b0 *p)
{
    if (p->unk_2C == 0) {
        return 1;
    }
    return func_ov003_0222ab4c(p->unk_2C);
}
