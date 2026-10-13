/* func_ov076_0227933c @ 0x0227933c, 0x34 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void func_02019d0c(void *, int, int, int);

int func_ov076_0227933c(void *param)
{
    volatile struct {
        int a[5];
        int b;
        int c;
    } l;

    l.a[0] = 0;
    l.a[1] = 0;
    l.a[2] = 0;
    l.a[3] = 0;
    l.a[4] = 0;
    l.b = data_020c80f8;
    l.c = 0;

    func_02019d0c((char *) param + 0x564, 0, 1, 0);
    return 1;
}
