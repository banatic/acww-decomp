/* func_0209984c @ 0x0209984c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x243c];
    unsigned char low_nibble : 4;
} UnkStruct_0209984c;

unsigned int func_0209984c(UnkStruct_0209984c *s)
{
    return s->low_nibble;
}
