/* func_ov103_0229ca00 @ 0x0229ca00, 0x48 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov103_0229c2f4(void *obj, int arg);
extern void func_ov094_0229b5e8(void *arg0, int arg1, int arg2, void *arg3);

void func_ov103_0229ca00(void *obj)
{
    unsigned char b;

    if (func_ov103_0229c2f4(obj, 0x40)) {
        return;
    }

    b = ((unsigned char *) obj)[0x2da0];
    if (b != 0 && b == 1) {
        func_ov094_0229b5e8((char *) obj + 0xb2c, *(int *) ((char *) obj + 0x2b98), *(int *) ((char *) obj + 0x2b9c),
                            (char *) obj + 0x2ba0);
    }
}
