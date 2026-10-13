/* func_020bdbe0 @ 0x020bdbe0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bf5f0(void *);

void func_020bdbe0(void *arg0)
{
    void *r5;
    void *r6;
    int *r4;
    int *r0;

    r5 = arg0;
    r6 = (char *) r5 + 0x1b30;
    r4 = (int *) ((char *) r5 + 0x2f14);

    while (r5 < r6) {
        if (*(int *) r5 != 0xd) {
            func_020bf5f0(r5);
            (*r4)--;
        }
        r5 = (char *) r5 + 0x74;
    }
}
