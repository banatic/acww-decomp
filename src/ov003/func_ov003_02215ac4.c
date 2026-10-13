/* func_ov003_02215ac4 @ 0x02215ac4, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02215bc0(void *obj, int arg, unsigned short val);

void func_ov003_02215ac4(void *obj, unsigned short val)
{
    int state;

    state = *(int *) ((char *) obj + 0x7f0);
    if (state == 0x4d) {
        return;
    }
    if (state == 0x4f) {
        *(unsigned short *) ((char *) obj + 0x0c84) = val;
    } else {
        func_ov003_02215bc0(obj, 6, val);
    }
}
