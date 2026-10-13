/* func_020a9dc8 @ 0x020a9dc8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020aa7e8(void *);

void func_020a9dc8(void *arg)
{
    void *p = arg;
    func_020aa7e8((char *) p + 4);
    *(void **) p = (char *) p + 4;
}
