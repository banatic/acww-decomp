/* func_0209ee54 @ 0x0209ee54, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void func_0209e79c(char *);
extern void func_0204e728(char *, int);
extern void func_0209e7fc(void *receiver);
extern int func_0209faac(char *, int);
extern int func_02099870(int);
extern void func_02095038(int, char *);
extern int func_020996b8(int);
extern void func_02072c50(int, int);
extern void func_0209e828(char *);
extern int func_020b03f8(void);
extern void func_020b0518(void *);
extern void func_0204e938(char *);
extern void func_0209d7e8(void);
extern void func_02098ff8(int, int);
extern void func_02098fd0(int, int);
extern void func_020791a4(int);
extern void func_0207c754(char *, int);
extern int func_0208602c(void);
extern int func_020860c8(int);
extern void func_02087eb0(void *);
extern void func_0207ac20(char *);
extern int data_021fbe94;

void func_0209ee54(char *self)
{
    int r4;
    int r6;

    r4 = func_020984e8();
    func_0209e79c(self);
    func_0204e728(self + 0xd304, data_021fbe94);
    func_0209e7fc(self);
    func_0209faac(self + 0x173dd, 0);
    func_02095038(func_02099870(r4), self + 2);
    r6 = func_020996b8(r4);
    func_02072c50(r6, func_02099870(r4));
    func_0209e828(self);
    func_020b0518((void *) func_020b03f8());
    func_0204e938(self + 0xd304);
    func_0209d7e8();
    func_02098ff8(r4, 1);
    func_02098ff8(r4, 0x23);
    func_02098fd0(r4, 9);
    func_020791a4(-1);
    func_0207c754(self + 0x9284, 1);
    func_02087eb0((void *) func_020860c8((int) func_0208602c()));
    func_0207ac20(self + 0x9284);
}
