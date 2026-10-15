/* func_ov004_02223440 @ 0x02223440, 0xa4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *self);
extern char *data_020ccf94;
extern int func_02073d90(void *g);
extern short *func_0209d358(int a, int b);
extern int func_020a7278(void);
extern void func_ov004_02223388(void *self, int a);
extern int func_0201bfd8(void *self, void *p, int a);
extern int func_0202ea40(void *self, short *buf, int a);

int func_ov004_02223440(char *self)
{
    short buf[2];

    if (func_0202ec58(self) == 0) {
        return 0;
    }
    *(short *) (self + 0x70c) = *(short *) (self + 0x8e);
    *(int *) (self + 0x4e8) |= 2;
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        if (func_020a7278() != 0) {
            func_ov004_02223388(self, 0);
        } else {
            func_0201bfd8(self, self + 0x712, 1);
            func_ov004_02223388(self, 4);
        }
    } else {
        func_ov004_02223388(self, 0);
        if (func_0202ea40(self, buf, 2) != 0) {
            *(char *) (self + 0x70e) = 1;
        }
    }
    return 1;
}
