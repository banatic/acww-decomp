/* func_ov116_0229e168 @ 0x0229e168, 0x88 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(void *p);
extern int func_ov114_0229c410(void *p, int x);
extern int func_ov090_02299078(int x);
extern int func_ov090_02299098(int x);

extern void func_ov116_0229dfa8(void *p);
extern void func_ov116_0229de60(void *p);
extern void func_ov116_0229ddf8(void *p);
extern int func_ov116_0229e4cc(void *p, int x);

extern struct {
    unsigned short field0;
    unsigned short flags;
} data_021fbe40;

void func_ov116_0229e168(void *param)
{
    unsigned short flags;

    if (func_ov002_02208014(param)) {
        func_ov116_0229dfa8(param);
        return;
    }
    if (func_ov114_0229c410((char *) param + 0xF8, func_ov002_02208008(param))) {
        func_ov116_0229de60(param);
        return;
    }
    flags = data_021fbe40.flags;
    if (flags & 1) {
        func_ov116_0229ddf8(param);
        return;
    }
    if (flags & 0x100) {
        func_ov116_0229e4cc(param, func_ov090_02299078(3));
        return;
    }
    if (flags & 0x200) {
        func_ov116_0229e4cc(param, func_ov090_02299098(3));
    }
}
