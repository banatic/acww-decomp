/* func_ov004_022268b8 @ 0x022268b8, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02008258(void *self, int a);
extern void func_0200d4e8(void *self, int a, int b, int c);
extern void func_0200f268(void *self, int k);
extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern void func_0203e110(void);

void func_ov004_022268b8(void *self)
{
    if (*(int *) ((char *) self + 0x98) == 0 && *(int *) ((char *) self + 0x7f8) == 1) {
        *(int *) ((char *) self + 0x7fc) = func_02008258(self, *(int *) ((char *) self + 0x7f0));
        func_0200d4e8(self, 3, 5, -1);
        func_0200f268(self, 5);
        if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) != 0) {
            func_0203e110();
        }
    }
}
