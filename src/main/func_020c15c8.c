/* func_020c15c8 @ 0x020c15c8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209dbe4(int);
extern int func_020644cc(int);
extern unsigned char data_020d2ef0[][32];

int func_020c15c8(int a, int b)
{
    int result = 0;
    int idx = func_0209dbe4(b);
    int cap = func_020644cc(100);
    int i = result;
    while (i < 32) {
        cap -= data_020d2ef0[idx][i];
        if (cap < 0) {
            result = (unsigned char) i;
            break;
        }
        i++;
    }
    return result;
}
