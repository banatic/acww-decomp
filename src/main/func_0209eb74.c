/* func_0209eb74 @ 0x0209eb74, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e7fc(void);
extern void func_0204de34(void);
extern void func_0204dde0(void);
extern void func_0209dfc0(void);
extern void func_0207bddc(char *ptr, int val);
extern void func_0207bbb8(char *ptr);
extern void func_020791a4(int val);
extern void func_0207c754(char *ptr, int val);
extern void func_020ba39c(void);
extern int func_0208602c(void);
extern int func_020860c8(int);
extern void func_02087eb0(void *);
extern int func_02098844(char *ptr, int idx);
extern void func_02099740(int a, int b);

extern char data_021dc7a8[];

void func_0209eb74(char *self)
{
    func_0209e7fc();
    func_0204de34();
    func_0204dde0();
    func_0209dfc0();
    func_0207bddc(self + 0x9284, 1);
    func_0207bbb8(self + 0x9284);
    func_020791a4(-1);
    func_0207c754(self + 0x9284, 1);
    func_020ba39c();
    func_02087eb0((void *) func_020860c8((int) func_0208602c()));
    {
        char *p = (char *) data_021dc7a8;
        int i = 0;
        int arg = i;
        p += 0x14;
        for (; i < 4; i++) {
            int ret = func_02098844(p, i);
            if (ret) {
                func_02099740(ret, arg);
            }
        }
    }
}
