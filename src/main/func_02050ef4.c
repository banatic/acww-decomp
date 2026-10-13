/* func_02050ef4 @ 0x02050ef4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02050ef4 {
    unsigned char pad_00[0x40];
    unsigned int a;
    unsigned int b;
    unsigned char pad_48[0x30];
    unsigned int c;
};

int func_02050ef4(struct UnkStruct_02050ef4 *s)
{
    int result = 0;
    if (s->c >= s->a && s->c < s->a + s->b) {
        result = 1;
    }
    return result;
}
