/* func_0206c234 @ 0x0206c234, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206c038(unsigned int *);

int func_0206c234(char *buf, int val)
{
    signed char b0 = (signed char) val;
    signed char b1 = (signed char) (val >> 8);
    int count = *(int *) (buf + 0x400);
    int flag = (unsigned) (0x400 - count) > 2 ? 1 : 0;
    if (flag) {
        int *ptr = (int *) (buf + 0x400);
        *ptr = *ptr + 1;
        buf[count] = b0;
        count = *ptr;
        *ptr = count + 1;
        buf[count] = b1;
        func_0206c038((unsigned int *) buf);
    }
    return flag;
}
