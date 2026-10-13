/* func_ov146_0229a8ec @ 0x0229a8ec, 0x64 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *obj);
extern int func_ov002_02208008(void *obj);
extern int func_ov146_0229985c(void *obj, int arg);
extern void func_ov146_0229a760(void *obj);
extern void func_ov146_0229a534(void *obj);
extern void func_ov146_0229a490(void *obj);
extern void func_ov146_0229a578(void *obj);
extern void func_ov146_0229a6a4(void *obj);
extern struct {
    unsigned char pad[2];
    unsigned short flags;
} data_021fbe40;

void func_ov146_0229a8ec(void *obj)
{
    if (func_ov002_02208014(obj)) {
        func_ov146_0229a760(obj);
        return;
    }
    if (func_ov146_0229985c(obj, func_ov002_02208008(obj))) {
        func_ov146_0229a534(obj);
        return;
    }
    {
        unsigned short f = data_021fbe40.flags;
        if ((f & 1) != 0) {
            func_ov146_0229a490(obj);
            return;
        } else if ((f & 2) != 0) {
            func_ov146_0229a578(obj);
            func_ov146_0229a6a4(obj);
            return;
        }
    }
}
