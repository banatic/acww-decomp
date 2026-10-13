/* func_020a7a14 @ 0x020a7a14, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps the goal y, goal x and cur x loads in that order; the plain compare loads cur x first */

void func_020a7a14(void *p)
{
    int d = *(unsigned int *) ((char *) p + 0x44);
    int b = *(unsigned int *) ((char *) p + 0x40);
    if ((b && b) && b) {
    }
    if (*(unsigned int *) ((char *) p + 0x28) == b && *(unsigned int *) ((char *) p + 0x2c) == d) {
        *(unsigned char *) ((char *) p + 0x58) = 1;
    }
}
