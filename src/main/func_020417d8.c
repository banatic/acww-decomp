/* func_020417d8 @ 0x020417d8, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020412a0(void);
extern int func_0203e340(void);
extern void func_0203e328(void);
extern void func_020417ac(void);
extern int func_02073d90(void *p);

extern int data_021c7590;
extern unsigned char data_021c75a0[3];
extern int data_020db6e0;
extern void *data_020ccf94;
extern unsigned char data_021f39c8[10];

int func_020417d8(void)
{
    if (func_020412a0() != 0) {
        return 1;
    }
    if (func_0203e340() != 0) {
        func_0203e328();
        data_021c7590 = 0;
        data_021c75a0[0] = 0;
        data_021c75a0[2] = 0;
    }
    switch (data_021c75a0[0]) {
        case 0:
            if (data_020db6e0 == 0x63) {
                func_020417ac();
            }
            break;
        case 1:
            data_021c75a0[0] = 2;
            break;
        default:
            break;
    }
    if (func_02073d90(data_020ccf94) == 0) {
        data_021f39c8[9] = data_020db6e0;
    }
    return 1;
}
