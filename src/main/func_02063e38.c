/* func_02063e38 @ 0x02063e38, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(unsigned int *p);

unsigned char func_02063e38(void)
{
    unsigned int buf[3];
    buf[0] = 0;
    buf[1] = 0;
    func_0209e474(buf);
    return ((unsigned char *) buf)[4];
}
