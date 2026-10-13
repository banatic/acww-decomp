/* func_ov083_02278e64 @ 0x02278e64, 0x34 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(char *ptr, int a, int b, int c);

int func_ov083_02278e64(char *self)
{
    volatile struct {
        int a;
        int b;
        int c;
        int d;
        int e;
        unsigned int f;
        int g;
    } local;

    local.a = 0;
    local.b = 0;
    local.c = 0;
    local.d = 0;
    local.e = 0;
    local.f = data_020c80f8;
    local.g = 0;

    func_02019d0c(self + 0x564, 0, 1, 0);
    return 1;
}
