/* func_02066db0 @ 0x02066db0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02068d38(void *);

void func_02066db0(void *arg0)
{
    void *r4 = arg0;
    func_02068d38((char *) arg0 + 0x1c);
    *(unsigned int *) ((char *) r4 + 0xc) = 1;
}
