/* func_0208829c @ 0x0208829c, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208829c {
    unsigned char pad_00[0xe];
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1;
};

int func_0208829c(struct UnkStruct_0208829c *s)
{
    if (s->bit5) {
        return 1;
    } else {
        return 0;
    }
}
