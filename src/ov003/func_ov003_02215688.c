/* func_ov003_02215688 @ 0x02215688, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(int a, int b);
extern int func_020604b0(void *p);
extern void func_0200f2a0(unsigned char *a, int b, unsigned char *c);
extern void func_ov003_02215494(unsigned char *a, int b, int c);
extern void func_02035624(int a);
extern void func_ov003_0221535c(unsigned char *a, int b, int c);

extern int data_020ccf94;

void func_ov003_02215688(unsigned char *self)
{
    unsigned char *p = self + 0x5d0;

    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        switch (func_020604b0(self + 0x5c8)) {
            case 0:
                func_0200f2a0(self, 0x7f6, p);
                break;
            case 1:
                func_ov003_02215494(self, 6, -1);
                func_02035624(0x12);
                break;
            case 2:
                func_ov003_0221535c(self, 6, -1);
                break;
            default:
                break;
        }
    } else {
        func_0200f2a0(self, 0x7f6, p);
    }
}
