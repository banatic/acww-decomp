/* func_ov122_022a1290 @ 0x022a1290, 0x60 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov122_0229efc8(void *p, int v);
extern int func_ov122_0229fb54(void *unused0);
extern void func_0200467c(int v);
extern void func_ov122_0229f394(void *p);
extern void func_ov122_022a15b8(void *p, int a, int b);

void func_ov122_022a1290(char *p)
{
    int r5;

    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (p), 0);
        if (*(unsigned char *) (p + 0xad) == *(unsigned char *) (p + 0xae)) {
            func_ov122_0229efc8(p, 8);
        }
        r5 = 1;
    } else {
        r5 = func_ov122_0229fb54(p);
        if (r5 != 0) {
            func_0200467c(0x15);
        }
    }
    if (r5 != 0) {
        func_ov122_0229f394(p);
        func_ov122_022a15b8(p, 0, 1);
    }
}
