/* func_ov122_0229f5f8 @ 0x0229f5f8, 0x3c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

int func_ov122_0229f5f8(unsigned char *self)
{
    switch (self[0xAA]) {
        case 0:
        case 1:
            return *(int *) (self + 0xBC) + 0x44;
        case 2:
            return *(int *) (self + 0xBC) + 0x58;
        case 3:
            return *(int *) (self + 0xBC) + 0xD8;
        default:
            return 0;
    }
}
