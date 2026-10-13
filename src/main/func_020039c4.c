/* func_020039c4 @ 0x020039c4, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020039c4(void *r0)
{
    void *r1;
    void *r2;

    r1 = *(void **) r0;
    r1 = *(void **) ((char *) r1 + 8);
    r1 = ((void *(*) (void *) ) r1)(r0);
}
