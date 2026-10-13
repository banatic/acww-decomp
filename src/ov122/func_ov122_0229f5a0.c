/* func_ov122_0229f5a0 @ 0x0229f5a0, 0x26 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_ov122_0229f5a0(unsigned char *self)
{
    if (self[0xAA] == 1) {
        return (unsigned char) (self[0xAC] + (*(unsigned char **) (self + 0xBC))[0xF8]);
    }
    return self[0xAC];
}
