/* func_0206ab60 @ 0x0206ab60, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8750(void *);

void func_0206ab60(void *param)
{
    unsigned char *p;
    unsigned char *q;
    int offset;

    func_020a8750((char *) param + 0x38);
    p = (unsigned char *) param + 0x4e;
    *p = 0;
    q = *(unsigned char **) ((char *) param + 0x24);
    offset = 0x1a49;
    q[offset] = 0;
}
