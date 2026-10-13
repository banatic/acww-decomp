/* func_020c19ec @ 0x020c19ec, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020c19ec {
    char pad_00[0x14];
    int value;
};

struct UnkStruct_020c19ec_2 {
    char pad_00[0x1e];
    unsigned char flag;
    char pad_1F[0x21];
    struct UnkStruct_020c19ec *inner;
};

void func_020c19ec(struct UnkStruct_020c19ec_2 *arg0)
{
    if (arg0->flag == 0x14) {
        arg0->inner->value = 0;
    }
}
