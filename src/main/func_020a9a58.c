/* func_020a9a58 @ 0x020a9a58, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a99d8(void *p);
extern void func_020edb3c(void *p);
extern int data_020e3d34;

void *func_020a9a58(void *p)
{
    *(void **) p = &data_020e3d34;
    func_020a99d8(p);
    func_020edb3c(p);
    return p;
}
