/* func_020ae3d4 @ 0x020ae3d4, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ae3c4(void *);
extern void func_020ae6fc(void *);

void func_020ae3d4(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_020ae3c4(r4);
    r4 = (char *) r4 + 8;
    func_020ae6fc(r4);
}
