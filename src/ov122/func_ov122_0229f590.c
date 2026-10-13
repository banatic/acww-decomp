/* func_ov122_0229f590 @ 0x0229f590, 0xe bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov122_0229f590(void *arg0, unsigned char arg1);

void func_ov122_0229f590(void *arg0, unsigned char arg1)
{
    unsigned char *p1;
    unsigned char *p2;

    p1 = (unsigned char *) arg0 + 0xac;
    *p1 = arg1;
    p2 = (unsigned char *) arg0 + 0xab;
    *p2 = 0x10;
}
