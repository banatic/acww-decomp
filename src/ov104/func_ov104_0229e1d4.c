/* func_ov104_0229e1d4 @ 0x0229e1d4, 0x8c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void func_ov104_0229cfe4(char *param);
extern int func_ov002_02208008(char *param);
extern int func_ov104_0229c364(char *param, unsigned int arg);
extern int func_ov002_02209044(char *p1, int p2, char *p3, unsigned char p4);
extern void func_ov104_0229d2b4(char *param);
extern void func_ov002_0220a1dc(char *param);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov104_0229d250(char *param);
extern unsigned short data_021fbe40[];

void func_ov104_0229e1d4(char *param)
{
    int ret;

    if (func_ov002_02208014(param) != 0) {
        func_ov104_0229cfe4(param);
        return;
    }

    ret = func_ov002_02208008(param);
    {
        unsigned char b = (unsigned char) func_ov104_0229c364(param, 0x8000);
        if (func_ov002_02209044(param + 0x2504, ret, param + 0xbd, b) != 0) {
            func_ov104_0229d2b4(param);
        } else {
            unsigned short flags = data_021fbe40[1];
            if (flags & 1) {
                func_ov002_0220a1dc(param + 0x24a0);
                func_ov002_02208098((void *) (param), 0xc);
            } else if (flags & 2) {
                func_ov104_0229d250(param);
            }
        }
    }
}
