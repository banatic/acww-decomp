/* func_020a9a40 @ 0x020a9a40, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3d34;
extern void func_020a99d8(void *);

void *func_020a9a40(void *p)
{
    *(void **) p = &data_020e3d34;
    func_020a99d8(p);
    return p;
}
