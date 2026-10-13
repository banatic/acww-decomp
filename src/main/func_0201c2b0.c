/* func_0201c2b0 @ 0x0201c2b0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c314(void);

int func_0201c2b0(struct UnkStruct *r4)
{
    int r0;
    int r1;
    int result;

    r0 = func_0201c314();
    r1 = *(short *) ((char *) r4 + 0x8e);
    result = r0 - r1;
    result = (result << 16) >> 16;
    return result;
}
