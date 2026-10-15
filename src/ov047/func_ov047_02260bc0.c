/* func_ov047_02260bc0 @ 0x02260bc0, 0x20 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014f60(int argument0);

void func_ov047_02260bc0(void *param)
{
    unsigned short *p;
    int *q;

    func_02014f60((int) param);
    p = (unsigned short *) ((char *) param + 0xce);
    *p = 0xfff1;
    q = (int *) ((char *) param + 0xd0);
    *q = 0x23;
}
