/* func_020a4d84 @ 0x020a4d84, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern int func_020a1954(char *, void *, int);
extern void func_0206f74c(void);
extern void func_02098fd0(void *, int);
extern void func_0204cdc8(void *);
extern int data_020e3c40;
extern int data_021f39fc;

void func_020a4d84(char *self)
{
    void *r = func_020984e8();
    func_020a1954(self, &data_020e3c40, 1);
    func_0206f74c();
    func_02098fd0(r, 2);
    func_0204cdc8(&data_021f39fc);
    self[0xa1] = 0;
}
