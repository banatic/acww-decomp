/* func_ov004_022361c4 @ 0x022361c4, 0x128 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern short func_ov004_02239474(int, int);
extern int func_ov004_02239460(int, int);
void func_ov004_022361c4(unsigned char *self)
{
    *(int *) (self + 0x20c) = 0;
    if (self[0x1fd] == 2) {
        *(short *) (self + 0x1c2) += func_ov004_02239474(180, 150);
        ++self[0x1eb];
    } else {
        *(short *) (self + 0x1c2) += func_ov004_02239474(*(unsigned short *) (self + 0x230), 0);
        self[0x1eb] = 0;
    }
    *(int *) (self + 0x158) = 0;
    self[0x202] = func_ov004_02239460(self[0x205], self[0x204]);
    self[0x203] = func_ov004_02239460(self[0x207], self[0x206]);
    *(int *) (self + 0x23c) = 0;
    if (self[0x1e8] == *(int *) (self + 0x15c)) {
        if (*(int *) (self + 0x1ac) >= *(int *) (self + 0x1cc)) {
            *(signed char *) (self + 0x1ca) = -1;
        } else if (*(int *) (self + 0x1ac) <= *(int *) (self + 0x228)) {
            *(signed char *) (self + 0x1ca) = 1;
        } else {
            *(signed char *) (self + 0x1ca) = func_ov004_02239460(0, 2) > 0 ? 1 : -1;
        }
    }
    self[0x24e] = 0;
    self[0x1ee] = 3;
    self[0x22f] = 1;
}
