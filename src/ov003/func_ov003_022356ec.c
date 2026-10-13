/* func_ov003_022356ec @ 0x022356ec, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020961a8(int i);

void *func_ov003_022356ec(const int *p)
{
    void *best = 0;
    int bestd = 0x0fffffff;
    unsigned char i = 0;
    // dx/dz are declared at function scope; o and q stay in the loop body.
    int dx, dz;
    do {
        void *o = func_020961a8(i);
        if (o != 0) {
            int *q = (int *) ((char *) o + 0x5c);
            dx = p[0] - *(int *) ((char *) o + 0x5c);
            if (dx < 0) {
                dx = -dx;
            }
            dz = p[2] - q[2];
            if (dz < 0) {
                dz = -dz;
            }
            if (dx + dz < bestd) {
                bestd = dx + dz;
                best = o;
            }
        }
        i = (unsigned char) (i + 1);
    } while (i < 4);
    return best;
}
