/* func_ov121_0229b40c @ 0x0229b40c, 0x78 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov121_02299a3c(void *p, int n);
extern int func_ov121_0229bc70(void *p, int n);
extern int func_ov002_02208008(void *p);
extern int func_ov121_02299ccc(void *p, int n, int flag);
extern void func_ov121_0229a2e4(void *p);
extern unsigned short data_021fbe40[];
extern int func_ov121_0229adac(void *p, unsigned char c);
extern void func_ov121_0229a108(void *p);
extern void func_ov121_0229a0e0(void *p);

void func_ov121_0229b40c(unsigned char *param)
{
    if (func_0206f56c() != 0) {
        func_ov121_02299a3c(param, 4);
        func_ov121_0229bc70(param, 7);
    } else {
        int result = func_ov002_02208008(param);
        if (func_ov121_02299ccc(param, result, 1) != 0) {
            func_ov121_0229a2e4(param);
        } else {
            if (data_021fbe40[1] & 1) {
                if (func_ov121_0229adac(param, param[0xb1]) == 0) {
                    func_ov121_0229a108(param);
                }
            }
            if (data_021fbe40[1] & 2) {
                func_ov121_0229a0e0(param);
            }
        }
    }
}
