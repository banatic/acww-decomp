/* func_020701a8 @ 0x020701a8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    int a;
    int b;
    int c;
} data_021cfcb4;
extern int func_0206ff48(int);
extern int func_020700cc(int);

void func_020701a8(void)
{
    if (data_021cfcb4.a || data_021cfcb4.b || data_021cfcb4.c) {
        unsigned char i;
        for (i = 0; i < 46; i++) {
            if (func_0206ff48(i)) {
                func_020700cc(i);
            }
        }
    }
}
