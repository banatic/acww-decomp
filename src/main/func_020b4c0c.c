/* func_020b4c0c @ 0x020b4c0c, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a94a4(void *p);
extern void func_020a9354(void *p, void *q);

void func_020b4c0c(void *p)
{
    func_020a94a4(p);
    func_020a9354(p, *(void **) ((char *) p + 0x30));
}
