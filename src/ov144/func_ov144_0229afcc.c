/* func_ov144_0229afcc @ 0x0229afcc, 0x60 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f58c(void *obj);
extern int func_0206f56c(int arg);
extern void func_ov144_0229a17c(void *obj);
extern void func_ov144_0229a798(void *obj);
extern void func_ov002_022080a0(void *obj, int arg);
extern void func_ov144_0229add8(void *obj);
extern void func_ov144_0229b02c(void *obj);
extern void func_ov144_0229add0(void *obj);

int func_ov144_0229afcc(void *obj)
{
    if (func_0206f56c(func_0206f58c(obj)) != 0) {
        unsigned char val = ((unsigned char *) obj)[0x8d];
        switch (val) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                func_ov144_0229a17c(obj);
                func_ov144_0229a798(obj);
                func_ov002_022080a0(obj, 1);
                break;
        }
    }
    func_ov144_0229add8(obj);
    func_ov144_0229b02c(obj);
    func_ov144_0229add0(obj);
    return 1;
}
