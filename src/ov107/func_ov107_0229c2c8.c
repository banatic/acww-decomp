/* func_ov107_0229c2c8 @ 0x0229c2c8, 0x8c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fca4(void);
extern int func_ov107_0229c354(void *receiver);
extern void func_02045d98(int key);
extern int func_02073d90(void *ptr);
extern void func_02073820(void *ptr);
extern void func_020737f0(void *ptr, unsigned char *buf, int len);
extern void func_02073770(void *ptr, int a, int b);
extern unsigned int *func_0206f7bc(void);
extern void func_ov003_0222e6c4(int a, int b);
extern int func_ov003_0222aae8(void *argument0);
extern void *data_020ccf94;

void func_ov107_0229c2c8(int a, int b)
{
    unsigned int r4;
    unsigned int r6;
    unsigned char buf[2];
    void *ptr;

    r4 = func_0206fca4();
    r6 = func_ov107_0229c354((void *) a);
    switch (r4 - 0x29) {
        case 0:
        case 1:
            if (b == 0) {
                return;
            }
            func_02045d98(r6);
            if (func_02073d90(data_020ccf94) == 0) {
                return;
            }
            buf[0] = 0x17;
            buf[1] = (unsigned char) r6;
            ptr = data_020ccf94;
            func_02073820(ptr);
            func_020737f0(ptr, buf, 2);
            func_02073770(ptr, 0x16, 4);
            break;
        case 2:
            func_ov003_0222e6c4(r6, 1);
            break;
        case 3:

            func_ov003_0222aae8(func_0206f7bc());
            break;
    }
}
