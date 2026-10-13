/* func_020a7a2c @ 0x020a7a2c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a7a2c(void *arg0);

void func_020a7a2c(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x3c) == 0xa) {
        *(unsigned int *) ((char *) arg0 + 0x54) = *(unsigned int *) ((char *) arg0 + 0x54) + 1;
        if (*(unsigned int *) ((char *) arg0 + 0x54) == *(unsigned int *) ((char *) arg0 + 0x50)) {
            *(unsigned char *) ((char *) arg0 + 0x58) = 1;
        }
    }
}
