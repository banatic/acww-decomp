/* func_020a44f0 @ 0x020a44f0, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021dc7a8;
extern void *func_020682e0(int);
extern void func_02068320(void *);
extern int func_020a1c9c(void);
extern void func_0209ef7c(int *);
extern void func_02098540(void);
extern void func_020792c8(void);
extern void func_0209e6ec(int *, int);
extern void func_0209e604(int *);
extern void func_020792b4(void);
extern void *func_020b5e10(void);
extern int func_020b6434(void *, int, int, int);
extern void func_020a4e94(int *, int);
void func_020a44f0(int *param)
{
    void *p;
    int x;
    p = func_020682e0(0);
    if (((int *) p)[1] != 0) {
        return;
    }
    func_02068320(p);
    x = func_020a1c9c();
    if ((x == 4) || (x == 1)) {
        func_0209ef7c(&data_021dc7a8);
        func_02098540();
        func_020792c8();
        func_0209e6ec(&data_021dc7a8, 3);
    } else {
        func_0209e6ec(&data_021dc7a8, 4);
    }
    func_0209e604(&data_021dc7a8);
    func_020792b4();
    func_020b6434(func_020b5e10(), 0x2c, 3, 2);
    func_020a4e94(param, 0);
}
