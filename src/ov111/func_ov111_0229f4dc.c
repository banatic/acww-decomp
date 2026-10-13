/* func_ov111_0229f4dc @ 0x0229f4dc, 0x28 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229efd8(unsigned char *, int);
int func_ov111_0229f4dc(unsigned char *p)
{
    if ((func_ov111_0229efd8(p, 1) == 0) || (p[0x9f] == p[0xa0])) {
        return 0;
    }
    return 1;
}
