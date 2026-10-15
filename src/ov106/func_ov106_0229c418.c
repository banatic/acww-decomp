/* func_ov106_0229c418 @ 0x0229c418, 0x40 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov106_0229c458(void *);
extern void func_ov106_0229c354(void *, int);
extern void func_ov106_0229cc50(void *);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);

void func_ov106_0229c418(void *p)
{
    func_ov106_0229c458(p);
    func_ov106_0229c354(p, 0x8000);
    func_ov106_0229cc50(p);
    func_ov002_02208090(p, 9);
    func_ov002_022080a0((void *) (p), 1);
    func_ov092_02299324(func_020ee45c(p), 0x44, 1);
}
