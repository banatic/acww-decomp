/* func_02073b84 @ 0x02073b84, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020739b8(void *arg);

void func_02073b84(void *arg)
{
    int *p;
    int i;
    p = (int *) ((char *) arg + 0x28);
    for (i = 4; i >= 0; i--) {
        *p++ = 0;
    }
    func_020739b8(arg);
}
