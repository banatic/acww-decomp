/* func_0207ddd0 @ 0x0207ddd0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_0207dfd4(int, int);
extern int func_0204c878(unsigned short *);

void func_0207ddd0(unsigned short *out, int arg2)
{
    unsigned short *p;
    int best;
    int score;
    int i;

    *out = 0xfff1;
    p = func_0207dfd4(arg2, 0);
    best = 0;
    for (i = 0; i < 4; p++, i++) {
        if (*p == 0xfff1) {
            continue;
        }
        score = func_0204c878(p);
        if (score < best) {
            continue;
        }
        *out = *p;
        best = score;
    }
}
