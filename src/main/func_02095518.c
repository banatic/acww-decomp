/* func_02095518 @ 0x02095518, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_0200f290(int, int);
extern int func_0200f27c(int, int);

int func_02095518(int a, int b, int c)
{
    int r4;
    int r5 = a;
    int r6 = b;
    int r0 = c;

    r4 = func_02096718(r0);
    if (r4 != 0) {
        if (func_0200f290(r4, 0x15) == 0) {
            func_0200f27c(r4, 0x15);
        }
        *(unsigned short *) ((char *) r4 + 0x460) = r5;
        *(unsigned short *) ((char *) r4 + 0x462) = r6;
        return 1;
    }
    return 0;
}
