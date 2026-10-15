/* func_ov004_0220ede0 @ 0x0220ede0, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220e5c0(void *self);
extern int func_ov004_0220ee74(void);
extern int func_ov004_0220d2b8(void *p);
extern int func_ov004_0220d220(void *p, int a, void *b, int c);
extern int func_ov004_0223c264(void *fn);
extern int func_ov004_0221134c(void *arg0);
extern void func_ov004_02211414(int k);
extern unsigned char func_020b65c4(void);
extern void func_02052038(int x, int k);
extern void func_02064db8(int a, int b, int c);
extern int data_ov004_02250010;

void func_ov004_0220ede0(char *self)
{
    int a;
    int k;

    if (func_ov004_0220e5c0(self) != 0) {
        a = *(int *) (self + 0x594);
        (void) func_ov004_0220d220(self + 0x748, a, &data_ov004_02250010, func_ov004_0220d2b8(self + 0x740));
        if (func_ov004_0220ee74() != 0) {
            k = func_ov004_0223c264((void *) func_ov004_0221134c);
            if (func_ov004_0220d2b8(self + 0x740) != 0 && k == 1) {
                if (*(int *) (self + 0x76c) != 0) {
                    func_02052038(((void) (func_ov004_02211414(*(int *) (self + 0x794))), func_020b65c4()), 1);
                } else {
                    func_02064db8(0, 1, 0);
                }
            }
        }
    }
}
