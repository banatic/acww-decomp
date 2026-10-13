/* func_020f9f74 @ 0x020f9f74, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f9f74 {
    char pad_00[0xb];
    signed char unk_0B;
};

void func_020f9f74(struct UnkStruct_020f9f74 *p, int value)
{
    signed char tmp;
    p->unk_0B = value;
    p->unk_0B--;
    tmp = p->unk_0B;
    if (tmp < 0) {
        tmp = 15;
    }
    p->unk_0B = tmp;
}
