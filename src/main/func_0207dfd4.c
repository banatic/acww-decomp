/* func_0207dfd4 @ 0x0207dfd4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0207dfd4 {
    char pad_00[0x7b0];
    unsigned short arr[4];
};

unsigned short *func_0207dfd4(struct UnkStruct_0207dfd4 *s, unsigned int index)
{
    if (index < 4) {
        return &s->arr[index];
    }
    return 0;
}
