/* func_ov118_0229c438 @ 0x0229c438, 0x3e bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(void *self);
extern void func_ov090_022993cc(int a, int b);
extern unsigned char *func_ov002_022080a0(void *self, unsigned char value);

int func_ov118_0229c438(void *self, int type)
{
    int result;

    result = func_020ee45c(self);
    if (type == -1 || type == 5) {
        // nothing
    } else {
        func_ov090_022993cc(result, (unsigned char) type);
        *((char *) self + 0x8C) = 7;
        func_ov002_022080a0(self, 1);
        return 1;
    }
    return 0;
}
