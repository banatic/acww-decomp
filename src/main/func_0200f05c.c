/* func_0200f05c @ 0x0200f05c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c7a20[];

int func_0200f05c(unsigned char *r0, int r1)
{
    if (r1 == 0x1e) {
        if (r0[0x7d5] == 0) {
            if (*(unsigned int *) (r0 + 0xc7c) == 0) {
                return 1;
            }
        }
    } else if (r1 == 0x4f) {
        if (*(unsigned int *) (r0 + 0xc7c) == 0) {
            return 1;
        }
    }
    return data_020c7a20[r1];
}
