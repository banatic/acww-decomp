/* func_ov068_02271e7c @ 0x02271e7c, 0x1a bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *, int b, int c, unsigned short d);

void func_ov068_02271e7c(void *p, void *message, int previous)
{
    func_020109a0(p, 0x83, 3, 0);
    *(unsigned short *) ((unsigned char *) p + 0x8e) = 0;
}
