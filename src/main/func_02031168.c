/* func_02031168 @ 0x02031168, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02031168(int *out, int p1, const int *in, int p4, int p5)
{
    int s4 = p4 >> 1;
    int s5 = p5 >> 1;
    int a = in[0];
    int low1 = p1 + (a - s4);
    int high1 = (a + s4) - p1;
    int b = in[2];
    int low2 = p1 + (b - s5);
    int high2 = (b + s5) - p1;
    int changed = 0;

    if (out[0] < low1) {
        out[0] = low1;
        changed = 1;
    } else if (out[0] > high1) {
        out[0] = high1;
        changed = 1;
    }

    if (out[2] < low2) {
        out[2] = low2;
        changed = 1;
    } else if (out[2] > high2) {
        out[2] = high2;
        changed = 1;
    }

    return changed;
}
