/* func_ov096_0229ce4c @ 0x0229ce4c, 0x138 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O1,s
 */

extern int func_ov096_0229f054(void *);
extern int func_0206fe54(void);
extern int func_02065ec0(int);
extern void func_ov096_0229c2dc(void *, int);
extern int func_ov096_0229c2fc(void *, int);
extern int func_02065f18(int);
extern void func_ov098_022a3060(void *);
extern void func_ov002_02208d4c(void *, int, int);
extern unsigned char data_020e54a8;

void func_ov096_0229ce4c(void *r4)
{
    int r6;
    unsigned int r5;

    r6 = func_ov096_0229f054(r4);
    if (func_0206fe54() != 0) {
        func_ov002_02208d4c((char *) r4 + 0x294c, 0, 1);
    }
    r5 = (unsigned int) func_02065ec0(r6);
    func_ov096_0229c2dc(r4, 8);

    switch (r5) {
        case 0:
            break;
        case 1:
            func_ov002_02208d4c((char *) r4 + 0x294c, 0x16, 5);
            func_ov002_02208d4c((char *) r4 + 0x294c, 0x20, 4);
            break;
        case 4: {
            int flag1 = (data_020e54a8 == 0) ? 1 : 0;
            if (flag1 != 0) {
                func_ov098_022a3060(r4);
            }
            func_ov002_02208d4c((char *) r4 + 0x294c, 0x16, 5);
            if (func_ov096_0229c2fc(r4, 8) == 0) {
                if (func_02065f18(r6) == 0xfff1) {
                    int flag2 = (data_020e54a8 == 0) ? 1 : 0;
                    if (flag2 != 0) {
                        func_ov002_02208d4c((char *) r4 + 0x294c, 0x15, 0xa);
                    }
                }
            }
        } break;
        case 7:
            func_ov002_02208d4c((char *) r4 + 0x294c, 0x17, 3);
            break;
        default:
            func_ov002_02208d4c((char *) r4 + 0x294c, 0x14, 3);
            break;
    }

    if (func_02065f18(r6) != 0xfff1) {
        func_ov002_02208d4c((char *) r4 + 0x294c, 0x18, 6);
    } else {
        if (r5 == 1 || r5 == 3 || r5 == 6) {
            int flag = (data_020e54a8 == 0) ? 1 : 0;
            if (flag != 0) {
                func_ov002_02208d4c((char *) r4 + 0x294c, 0x15, 0xa);
            }
        }
    }
}
