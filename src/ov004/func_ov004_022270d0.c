/* func_ov004_022270d0 @ 0x022270d0, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern void *func_020984fc(int k);
extern void *func_02099824(void *a);
extern void *func_020997f8(void *a);
extern void func_ov004_02225f70(void *self, void *b, void *c);

void func_ov004_022270d0(void *self)
{
    void *a, *b;

    if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) != 0) {
        a = func_020984fc(*(int *) ((char *) self + 0x800));
        b = func_02099824(a);
        func_ov004_02225f70(self, b, func_020997f8(a));
    }
}
