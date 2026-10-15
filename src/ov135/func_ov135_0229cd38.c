/* func_ov135_0229cd38 @ 0x0229cd38, 0x7c bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[];
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *);
extern int func_ov135_0229c588(void *, int);
extern void func_ov135_0229ca58(void *);
extern void func_ov135_0229c6e8(void *);
extern void func_ov135_0229c654(void *);
extern void func_ov135_0229c738(void *);
extern void func_ov135_0229c97c(void *);
extern void func_ov135_0229c954(void *);

void func_ov135_0229cd38(void *arg)
{
    if (func_ov002_02208014(arg)) {
        func_ov135_0229ca58(arg);
        return;
    }
    if (func_ov135_0229c588(arg, func_ov002_02208008(arg))) {
        func_ov135_0229c6e8(arg);
        return;
    }
    {
        unsigned short flags = data_021fbe40[1];
        int bit;
        bit = flags & 1;
        if (bit != 0) {
            func_ov135_0229c654(arg);
            return;
        }
        bit = flags & 8;
        if (bit != 0) {
            func_ov135_0229c738(arg);
            func_ov135_0229c97c(arg);
            return;
        }
        bit = flags & 2;
        if (bit != 0) {
            func_ov135_0229c738(arg);
            func_ov135_0229c954(arg);
        }
    }
}
