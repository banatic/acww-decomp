/* func_ov136_0229c794 @ 0x0229c794, 0x44 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_022999e0(void *ptr);
extern int func_ov002_0220a768(void *ptr, int arg);
extern int func_ov136_0229c574(void *ptr, int arg);
extern int data_ov136_0229d428[];

int func_ov136_0229c794(void *ptr)
{
    if (func_ov136_0229c574(ptr, 2) != 0) {
        return func_ov134_022999e0((char *) ptr + 0x2c4);
    } else {
        unsigned char b = ((unsigned char *) ptr)[0x2b77];
        if (b == 2) {
            ptr = (char *) ptr + 0xf8;
            return func_ov002_0220a768(ptr, 6);
        } else {
            return data_ov136_0229d428[b];
        }
    }
}
