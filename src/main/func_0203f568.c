/* func_0203f568 @ 0x0203f568, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203f58c(void *param1);
extern void func_020e8ce0(void *param1, void *param2);

void func_0203f568(void *param1)
{
    void *r5;
    void *r4;
    void *r6;

    r6 = param1;
    r5 = *(void **) r6;
    while (r5) {
        r4 = *(void **) ((char *) r5 + 4);
        func_020e8ce0(r6, r5);
        func_0203f58c(r5);
        r5 = r4;
    }
}
