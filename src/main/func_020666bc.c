/* func_020666bc @ 0x020666bc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020951dc(void *a, void *b);

void func_020666bc(void *a, void *b)
{
    unsigned char *p = (unsigned char *) a;
    p[0x1e] = 1;
    func_020951dc(b, a);
}
