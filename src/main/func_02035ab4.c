/* func_02035ab4 @ 0x02035ab4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035684(int, int, int);

void func_02035ab4(void *obj)
{
    unsigned char *p = (unsigned char *) obj;
    p[0xa] = 1;
    func_02035684(0xa, 0xf, 0);
}
