/* func_ov134_0229ac38 @ 0x0229ac38, 0x4c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229ac84(void *a, void *b, int c, int d, int e);
extern void func_ov134_0229af14(void *a);
extern void func_02004644(int a, int b);
extern void RtcSendPxiCommand(int a);

int func_ov134_0229ac38(void *obj)
{
    int a, b, ret;
    a = *(int *) ((char *) obj + 0x88);
    b = *(int *) ((char *) obj + 0x84);
    if (b == a) {
        ret = 1;
    } else {
        ret = func_ov134_0229ac84(obj, (char *) obj + 0x84, a, 0x30, 3);
        func_ov134_0229af14(obj);
    }
    if (ret == 1) {
        func_02004644(0x54, 1);
        RtcSendPxiCommand(0x2e);
    }
    return ret;
}
