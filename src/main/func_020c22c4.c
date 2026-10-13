/* func_020c22c4 @ 0x020c22c4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020c22c4(void *self)
{
    unsigned int *p = (unsigned int *) ((char *) self + 0x4e8);
    *p &= ~2;
    *(unsigned short *) ((char *) self + 0x712) = 0x28;
    *(unsigned int *) ((char *) self + 0x718) = *(unsigned int *) ((char *) self + 0x5c);
    *(unsigned int *) ((char *) self + 0x71c) = *(unsigned int *) ((char *) self + 0x60);
    *(unsigned int *) ((char *) self + 0x720) = *(unsigned int *) ((char *) self + 0x64);
    return 1;
}
