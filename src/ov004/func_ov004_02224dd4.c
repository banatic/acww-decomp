/* func_ov004_02224dd4 @ 0x02224dd4, 0x15c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *data_020ccf94;
extern void func_0201c054(void *, int, int, int);
extern int func_0201c0e0(void *);
extern int func_0201c014(void *);
extern int func_0201c040(void *, int *, int *);
extern int func_020a7278(void);
extern void func_ov004_022256ec(void *, int);
void func_ov004_02224dd4(unsigned char *self, unsigned int kind, int value)
{
    int a, b;
    switch (kind) {
        case 3:
            self[0x560] = value;
            if (value != 4) {
                func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), value);
                func_ov004_022256ec(self, 6);
            } else if (func_0201c0e0(self)) {
                func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), *(int *) (data_020ccf94 + 0x64));
                func_ov004_022256ec(self, 6);
            }
            break;
        case 1:
            func_ov004_022256ec(self, 1);
            break;
        case 0:
            self[0x560] = value;
            if (value != 4 && value != *(int *) (data_020ccf94 + 0x64)) {
                func_0201c054(self, 1, value, value);
                func_ov004_022256ec(self, 5);
            } else if (func_0201c0e0(self)) {
                func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), *(int *) (data_020ccf94 + 0x64));
                func_ov004_022256ec(self, 1);
            }
            break;
        case 8:
            if (value == 4) {
                if (func_020a7278()) {
                    func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), 4);
                    func_ov004_022256ec(self, 3);
                } else {
                    func_0201c054(self, 1, 4, *(int *) (data_020ccf94 + 0x64));
                    func_ov004_022256ec(self, 4);
                }
            }
            break;
        case 4:
            if (func_0201c014(self) && func_0201c0e0(self)) {
                a = 4;
                b = 4;
                if (func_0201c040(self, &a, &b)) {
                    if ((value != 4 && value == b) || value == 4) {
                        func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), 4);
                        func_ov004_022256ec(self, 0);
                    }
                }
            }
            break;
    }
}
