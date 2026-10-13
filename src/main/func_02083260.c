/* func_02083260 @ 0x02083260, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205ebb4(void *);

void func_02083260(void *arg)
{
    unsigned char *p = (unsigned char *) arg;
    func_0205ebb4(p + 4);
    *p = 0;
}
