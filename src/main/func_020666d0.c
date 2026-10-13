/* func_020666d0 @ 0x020666d0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020951dc(void *a, void *b);

void func_020666d0(void *arg0, void *arg1)
{
    unsigned char *p = (unsigned char *) arg0;
    p[0x1e] = 2;
    func_020951dc(arg1, arg0);
}
