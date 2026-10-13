/* func_020033ec @ 0x020033ec, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm int func_01ffd3e8(void *ptr);

struct UnkStruct_020033ec {
    char pad_00[0xb0];
    unsigned int flags;
};

int func_020033ec(struct UnkStruct_020033ec *s)
{
    if (func_01ffd3e8(s) == 0) {
        return 0;
    }
    if ((s->flags & 4) && (s->flags & 2)) {
        return 0;
    }
    return 1;
}
