/* func_020913b0 @ 0x020913b0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02091468(void *);

void func_020913b0(unsigned char *arg0)
{
    unsigned int val;

    func_02091468(arg0);
    val = 0;
    *(unsigned short *) (arg0 + 0x39c) = (unsigned short) val;
}
