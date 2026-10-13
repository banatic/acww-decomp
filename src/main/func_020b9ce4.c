/* func_020b9ce4 @ 0x020b9ce4, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ba1bc(void *);
extern void func_020ba108(void *);

void func_020b9ce4(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_020ba1bc(r4);
    r4 = (char *) r4 + 0x10;
    func_020ba108(r4);
}
