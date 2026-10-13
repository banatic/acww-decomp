/* func_ov120_0229b6b8 @ 0x0229b6b8, 0x2c bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e930(void *ptr);
extern void func_ov120_0229a6f0(void *ptr);
extern void func_ov120_0229a428(void *ptr, int param);

void func_ov120_0229b6b8(void *obj)
{
    if (func_0208e930((char *) obj + 0x674)) {
        func_ov120_0229a6f0(obj);
        func_ov120_0229a428(obj, 0x1000);
    }
}
