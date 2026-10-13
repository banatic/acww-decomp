/* func_ov107_0229d530 @ 0x0229d530, 0x26 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229c354(void *);
extern int func_ov003_0222ea84(int);
extern void func_ov002_02208098(void *, int);

void func_ov107_0229d530(unsigned char *param)
{
    if (func_ov003_0222ea84(func_ov107_0229c354(param)) != 3) {
        unsigned char *q = param + 0xbe;
        *q = 5;
        func_ov002_02208098(param, 19);
    }
}
