/* func_ov102_0229d0ec @ 0x0229d0ec, 0x36 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov102_0229d124(void *p, int i);
extern int func_ov102_0229d400(void *p, int i);
extern void func_ov094_0229a888(void *p, int value);

void func_ov102_0229d0ec(void *p)
{
    unsigned char i;
    char *q;
    i = 0;
    q = (char *) p + 0xcc;
    do {
        if (func_ov102_0229d124(p, i)) {
            func_ov094_0229a888(q, func_ov102_0229d400(p, i));
        }
        i = (i + 1) & 0xff;
    } while (i <= 14);
}
