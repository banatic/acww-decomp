/* func_020828c0 @ 0x020828c0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020828c0 {
    int a;
    unsigned short b;
};

int func_020828c0(int unused, struct UnkStruct_020828c0 *p)
{
    if (p->a) {
        if (((p->b & 0xF000) >> 12) == 0xD) {
            return 1;
        }
    }
    return 0;
}
