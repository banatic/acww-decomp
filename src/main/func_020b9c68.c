/* func_020b9c68 @ 0x020b9c68, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ccc(void);

void func_020b9c68(void *arg)
{
    void *r4 = arg;
    func_020b9ccc();
    ((unsigned char *) r4)[0xd] = 1;
}
