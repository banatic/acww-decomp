/* func_ov004_0222b540 @ 0x0222b540, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *data_020ccf94;
extern int func_02073908(char *a, int b);
extern int func_02051dfc(void);
extern int func_ov004_0222b3e8(void *self, int a, int b, int c);
extern int func_ov004_0222b4e0(void *self, int a, int b, int c);

void func_ov004_0222b540(char *self)
{
    unsigned char *q;

    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        q = (unsigned char *) (self + 0x7d4);
        if (q[0] < 3) {
            q[0] = q[0] + 1;
        }
        switch (func_02051dfc()) {
            case 0:
                break;
            case 1:
                if (q[0] >= 3) {
                    func_ov004_0222b3e8(self, q[1], 6, -1);
                }
                break;
            case 2:
                if (q[0] >= 3) {
                    func_ov004_0222b4e0(self, q[1], 6, -1);
                }
                break;
        }
    }
}
