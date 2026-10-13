/* func_020be160 @ 0x020be160, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020be160(void *r0, int r1)
{
    if (r1 == 0) {
        *(int *) ((char *) r0 + 0x1b54) = 0x34;
        return;
    }
    if (r1 == 1) {
        *(int *) ((char *) r0 + 0x1b60) = 0x34;
        return;
    }
    if (r1 == 2) {
        *(int *) ((char *) r0 + 0x1b54) = 0x34;
        *(int *) ((char *) r0 + 0x1b60) = 0x34;
        return;
    }
    if (r1 == 3) {
        *(int *) ((char *) r0 + 0x1b30) = 0x34;
        *(int *) ((char *) r0 + 0x1b48) = 0x34;
        *(int *) ((char *) r0 + 0x1b60) = 0x34;
        return;
    }
    if (r1 == 4) {
        *(int *) ((char *) r0 + 0x1b3c) = 0x34;
        *(int *) ((char *) r0 + 0x1b48) = 0x34;
        *(int *) ((char *) r0 + 0x1b54) = 0x34;
    }
}
