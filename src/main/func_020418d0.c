/* func_020418d0 @ 0x020418d0, 0x130 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020412a0(void);
extern int func_02073d90(void *);
extern int func_020b65c4(void);
extern int func_020b6640(void);
extern void func_020417ac(void);
extern void func_0204762c(void);
extern void func_0203e334(void);
extern void func_02046a74(int);
extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, const void *, unsigned int);
extern int func_0203fc78(int, void *, int);
extern void func_020b23c8(void);

extern unsigned char data_021dc7a8[];
extern void *data_020ccf94;
extern int data_021c7588;
extern unsigned char data_021c75a0[4];
extern unsigned int data_020db6dc, data_020db6e0, data_020db6e4;

int func_020418d0(void)
{
    unsigned char *base;
    unsigned char b;
    int res;
    unsigned int local1[2];
    unsigned char local3[8];

    if (func_020412a0() != 0) {
        return 0;
    }

    base = data_021dc7a8;

    if (func_02073d90(data_020ccf94) == 0 && func_020b65c4() != 0xd) {
        if (data_021c7588 != 0) {
            local1[0] = 0;
            local1[1] = 0;
            func_0209e474(local1);
            func_020417ac();
            b = base[0x17229];
            MI_CpuCopy8(local1, local3, 8);
            res = func_0203fc78(b, local3, 0);
            if (res != 0 && res != 3) {
                data_020db6dc = b;
                data_020db6e4 = b;
                data_020db6e0 = b;
            }
        }
        base[0x17229] = 0x63;
        data_021c7588 = 0;
        if (func_020b6640() != 0 && data_021c75a0[3] == 0) {
            func_0204762c();
        }
    } else {
        func_020417ac();
        b = base[0x17229];
        data_020db6dc = b;
        data_020db6e4 = b;
        data_020db6e0 = b;
        data_021c7588 = 1;
    }

    switch (data_021c75a0[0]) {
        case 0:
        case 2:
        case 3:
            break;
        case 1:
            func_020417ac();
            break;
        default:
            if (func_020b6640() == 0) {
                func_020417ac();
            } else {
                func_0203e334();
                data_021c75a0[0] = 5;
                if (data_021c75a0[3] != 0) {
                    func_02046a74(0);
                    data_021c75a0[3] = 0;
                }
                if (data_020db6e4 != 0x63) {
                    data_020db6dc = data_020db6e4;
                }
                func_020b23c8();
            }
            break;
    }

    return 1;
}
