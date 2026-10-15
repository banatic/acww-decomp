/* func_0209ea24 @ 0x0209ea24, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern void func_0209e79c(void *);
extern void func_0204e728(void *, void *);
extern void *data_021fbe94; // at 0x021fbe94
extern void func_0209e7fc(void *receiver);
extern int func_0209faac(void *, int);
extern void func_0209e974(void *);
extern void func_0209e828(void *);
extern int func_020b03f8(void);
extern void func_020b0518(void *);
extern void func_0204e938(void *);
extern void func_0209d7e8(void);
extern void func_02098ff8(void *, int);
extern void func_02098fd0(void *, int);
extern void func_020791a4(int);
extern void func_0207c754(void *, int);
extern int func_0208602c(void);
extern int func_020860c8(int);
extern void func_02087eb0(void *);
extern void func_0207ac20(void *);

void func_0209ea24(void *self)
{
    void *r4;

    r4 = func_020984e8();
    func_0209e79c(self);
    func_0204e728(((char *) self) + 0xd304, data_021fbe94);
    func_0209e7fc(self);
    func_0209faac(((char *) self) + 0x173dd, 0);
    func_0209e974(self);
    func_0209e828(self);
    func_020b0518((void *) func_020b03f8());
    func_0204e938((char *) ((unsigned int) self + 0xd304));
    func_0209d7e8();
    func_02098ff8(r4, 1);
    func_02098ff8(r4, 0x23);
    func_02098fd0(r4, 9);
    func_020791a4(-1);
    func_0207c754(((char *) self) + 0x9284, 1);
    func_02087eb0((void *) func_020860c8((int) func_0208602c()));
    func_0207ac20((char *) ((unsigned int) self + 0x9284));
}
