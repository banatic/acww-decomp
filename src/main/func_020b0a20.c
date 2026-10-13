/* func_020b0a20 @ 0x020b0a20, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b0a20 {
    unsigned char pad_00[2];
    unsigned short a : 7;
    unsigned short b : 7;
    unsigned short c : 2;
};

int func_020b0a20(struct UnkStruct_020b0a20 *s)
{
    if (s->a != 0 && s->b != 0) {
        return 1;
    }
    return 0;
}
