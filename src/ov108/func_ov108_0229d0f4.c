/* func_ov108_0229d0f4 @ 0x0229d0f4, 0x3c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov108_0229c628(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_02208e28(void *);

void func_ov108_0229d0f4(void *arg0)
{
    if (func_ov002_02208e28((char *) arg0 + 0x24fc) == 0) {
        return;
    }
    if (func_0206fe54() != 0) {
        func_ov108_0229c628(arg0);
        func_ov002_02208098((void *) (arg0), 8);
    } else {
        func_ov002_02208098((void *) (arg0), 5);
    }
}
