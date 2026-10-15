/* func_ov004_02226c94 @ 0x02226c94, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern int func_ov004_02228dfc(void *self, int a, int b, int c);
void func_ov004_02226c94(unsigned char *self)
{
    if (func_02056f94(self + 0x2d0) != 0) {
        switch (*(int *) (self + 0x704)) {
            case 0x95:
                func_020109a0(self, 0x96, 0, 0);
                break;
            case 0x96:
                func_020109a0(self, 0x97, 0, 0);
                break;
            case 0x97:
                break;
            case 0x98:
                func_ov004_02228dfc(self, 0, 6, -1);
                break;
        }
    }
}
