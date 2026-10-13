/* func_020399c8 @ 0x020399c8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8fb8(void *ptr);

void func_020399c8(void *obj)
{
    void *ptr;
    ptr = *(void **) ((char *) obj + 0x9c);
    if (ptr != 0) {
        func_020a8fb8(ptr);
        *(void **) ((char *) obj + 0x9c) = 0;
    }
}
