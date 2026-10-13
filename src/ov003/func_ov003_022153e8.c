/* func_ov003_022153e8 @ 0x022153e8, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02056f94(void *p);
extern int func_02073908(void *a, int b);
extern void func_0203b144(void);
extern int func_02008258(void *self, int b);
extern void func_0200d4e8(void *a, int b, int c, int d);
extern void func_0205eae0(void *a, int b, int c, int d);

void func_ov003_022153e8(char *self)
{
    if (func_02056f94(self + 0x2d0) == 0) {
        return;
    }
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_0203b144();
    }
    *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
    func_0200d4e8(self, 3, 1, -1);
    func_0205eae0(self + 0x5a0, 19, 3, 0);
}
