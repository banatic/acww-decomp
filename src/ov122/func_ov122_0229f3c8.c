/* func_ov122_0229f3c8 @ 0x0229f3c8, 0x7c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov122_0229efc8(void *p, unsigned int v);

void func_ov122_0229f3c8(unsigned char *p)
{
    if (p[0xb2] == p[0xb3]) {
        func_ov122_0229efc8(p, 0x800);
        return;
    }
    if (p[0xb2] < p[0xb3]) {
        p[0xb2] += 8;
        if (p[0xb2] > p[0xb3]) {
            p[0xb2] = p[0xb3];
        }
    } else {
        if (p[0xb2] < 8) {
            p[0xb2] = p[0xb3];
        } else {
            p[0xb2] -= 8;
            if (p[0xb2] < p[0xb3]) {
                p[0xb2] = p[0xb3];
            }
        }
    }
}
