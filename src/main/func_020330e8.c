/* func_020330e8 @ 0x020330e8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034294(void *arg);
extern void func_02030658(void *arg);

void *func_020330e8(void *p)
{
    func_02034294((char *) p + 0x14);
    func_02030658(p);
    return p;
}
