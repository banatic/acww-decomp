/* func_0209ebec @ 0x0209ebec, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern char data_020e368c[];

extern void func_0209dbb4(char *);
extern void func_0209dfc0(void);
extern void func_0204e728(char *, int);
extern void func_0209e7fc(void);
extern void func_02064244(char *, char *);
extern void func_0209e828(char *);
extern int func_020b03f8(void);
extern void func_020b0518(void *);
extern void func_0204e938(char *);
extern void func_020791a4(int);
extern void func_0207c754(char *, int);
extern void func_0209fb5c(char *);
extern void func_020ba38c(void);
extern int func_0208602c(void);
extern int func_020860c8(int);
extern void func_02087eb0(void *);

void func_0209ebec(char *arg)
{
    func_0209dbb4(arg + 0x173cc);
    func_0209dfc0();
    func_0204e728(arg + 0xd304, data_021fbe94);
    asm { add r0, arg, #0 }
    func_0209e7fc();
    func_02064244(arg + 2, data_020e368c);
    func_0209e828(arg);
    func_020b0518((void *) func_020b03f8());
    func_0204e938(arg + 0xd304);
    func_020791a4(-1);
    func_0207c754(arg + 0x9284, 0);
    func_0209fb5c(arg + 0x173f8);
    func_020ba38c();
    func_02087eb0((void *) func_020860c8((int) func_0208602c()));
}
