/* func_02091468 @ 0x02091468, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020914dc(void *);

void func_02091468(void *arg0)
{
    int i;
    void *ptr;

    ptr = (void *) ((unsigned int) arg0 + 0x380);
    func_020914dc(ptr);
    for (i = 0; i < 0x20; i++) {
        func_020914dc((void *) ((unsigned int) arg0 + (i * 0x1c)));
    }
}
