/* func_ov047_02260bc0 @ 0x02260bc0, 0x20 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_02014f60(void);

void func_ov047_02260bc0(void *param)
{
    unsigned short *p;
    int *q;

    func_02014f60();
    p = (unsigned short *) ((char *) param + 0xce);
    *p = 0xfff1;
    q = (int *) ((char *) param + 0xd0);
    *q = 0x23;
}
