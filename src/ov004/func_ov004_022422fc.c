/* func_ov004_022422fc @ 0x022422fc, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02244c20(void *);
extern char *func_ov004_0223ee38(void);

void func_ov004_022422fc(char *self)
{
    if (func_ov004_02244c20(self) != 0) {
        *(short *) (self + 0x172) = 0x19;
        *(int *) (func_ov004_0223ee38() + 0x15c) = 0x1000;
        *(short *) (self + 0x168) = 0;
    }
}
