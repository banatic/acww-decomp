/* func_020bdc14 @ 0x020bdc14, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bf5f0(void *);

void func_020bdc14(void *arg0, int arg1)
{
    void *r5;
    void *r6;
    void *r4;
    int *r4_ptr;
    int r0;

    r5 = arg0;
    r6 = (char *) r5 + 0x1b30;
    r4 = (char *) r5 + 0x2f14;
    while (r5 < r6) {
        if (arg1 == *(int *) r5) {
            func_020bf5f0(r5);
            r4_ptr = (int *) r4;
            r0 = *r4_ptr;
            *r4_ptr = r0 - 1;
        }
        r5 = (char *) r5 + 0x74;
    }
}
