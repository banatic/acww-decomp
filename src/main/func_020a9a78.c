/* func_020a9a78 @ 0x020a9a78, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a99d8(void *p);
extern char data_020e3d34;

void *func_020a9a78(void *p)
{
    *(void **) p = (void *) &data_020e3d34;
    func_020a99d8(p);
    return p;
}
