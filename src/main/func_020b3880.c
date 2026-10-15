/* func_020b3880 @ 0x020b3880, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int arg);
extern void func_02072998(void *ptr);

void func_020b3880(void *ptr)
{
    ((unsigned char *) ptr)[0x234] = func_020644cc(3);
    func_02072998(ptr);
}
