/* func_ov133_0229b4b0 @ 0x0229b4b0, 0x50 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fc4c(int x);
extern void *func_ov002_0220a720(void *p, int x);
extern void func_ov002_02208090(void *p, int x);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern int func_ov133_0229c3d4(void *p, int x);
extern int func_0206fca4(void);
extern int func_ov133_0229b714(void *receiver);
extern void func_02077c40(void *p);
extern void func_0200467c(int cmd);

void func_ov133_0229b4b0(char *self)
{
    func_0206fc4c(0);
    func_ov002_0220a720(self + 0x180, 7);
    func_ov002_02208090(self, 3);
    func_ov002_02208098(self, 0xa);
    func_ov133_0229c3d4(self, 6);
    if (func_0206fca4() == 0xe) {
        func_02077c40((void *) func_ov133_0229b714(self));
    }
    func_0200467c(0x28);
}
