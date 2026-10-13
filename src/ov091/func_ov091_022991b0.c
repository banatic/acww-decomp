/* func_ov091_022991b0 @ 0x022991b0, 0x38 bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_0208f0c4(void *ptr, int value);
extern void func_ov002_02208090(void *ptr, int value);
extern void RtcSendPxiCommand(int cmd);

void func_ov091_022991b0(void *obj)
{
    if (func_0208e484((char *) obj + 0x434)) {
        func_0208f0c4((char *) obj + 0x3bc, 2);
        func_ov002_02208090(obj, 3);
        RtcSendPxiCommand(0x27);
    }
}
