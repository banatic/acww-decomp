/* func_020a9530 @ 0x020a9530, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a9530(void *r0);

void *func_020a9530(void *r0)
{
    unsigned char r1;
    void *r2;

    r2 = 0;
    r1 = *(unsigned char *) ((char *) r0 + 4);
    if (r1 != 0) {
        r2 = (char *) r0 + 0x90;
    }
    return r2;
}
