/* func_020a9508 @ 0x020a9508, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a94a4(void *);

void func_020a9508(void *r4)
{
    func_020a94a4(*(void **) r4);
    *(int *) ((char *) r4 + 4) = 0;
    *(int *) ((char *) r4 + 8) = 0;
}
