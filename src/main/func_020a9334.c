/* func_020a9334 @ 0x020a9334, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9cac(void *param1, void *param2);

void func_020a9334(void *param0, void *param1)
{
    void *r5 = param0;
    void *r4 = param1;

    if (r4 != 0) {
        func_020a9cac((char *) r5 + 8, (char *) r5 + 4);
        *(void **) ((char *) r5 + 4) = r4;
    }
}
