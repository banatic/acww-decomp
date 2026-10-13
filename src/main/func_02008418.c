/* func_02008418 @ 0x02008418, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02008458(void *obj, int arg, unsigned short val);

void func_02008418(void *obj, unsigned short val)
{
    int state;

    state = *(int *) ((char *) obj + 0x7f0);
    if (state == 0x85) {
        return;
    }
    if (state == 0x86) {
        *(unsigned short *) ((char *) obj + 0x0c84) = val;
    } else {
        func_02008458(obj, 6, val);
    }
}
