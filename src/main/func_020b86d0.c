/* func_020b86d0 @ 0x020b86d0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b90a4(void *);

void func_020b86d0(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_020b90a4((void *) ((unsigned int) arg0 + 8));
    *(unsigned int *) ((unsigned int) r4 + 4) = 3;
}
