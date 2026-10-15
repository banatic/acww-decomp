/* func_020669b8 @ 0x020669b8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02066a84(void *p);
extern void func_020a8188(void *p);
extern void func_020edb3c(void *p);

extern unsigned char data_020df008[];

void *func_020669b8(void *p)
{
    *(unsigned int *) p = (unsigned int) data_020df008;
    func_02066a84((char *) p + 0x20);
    func_020a8188(p);
    func_020edb3c(p);
    return p;
}
