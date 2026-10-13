/* func_02041644 @ 0x02041644, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020db6e4;
extern int data_020db6e0;
extern int data_020db6dc;
extern unsigned char data_020ca508[];

extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, void *, int);
extern int func_0203fcb4(int, void *, int);
extern void func_0204130c(int, int, int);

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Eight;

void func_02041644(void)
{
    int x;
    Eight a, b, c;
    int i, zero;

    a.unk_00 = 0;
    a.w1 = 0;
    func_0209e474(&a);

    if (data_020db6e4 == 0x63) {
        i = 0;
        x = i;
        zero = i;
        do {
            int r;
            unsigned char ch;

            MI_CpuCopy8(&a, &b, 8);
            ch = data_020ca508[i];
            r = func_0203fcb4(ch, &b, zero);
            switch (r) {
                case 2:
                    if (ch == 0x13) {
                        data_020db6e4 = ch;
                        data_020db6e0 = ch;
                    } else {
                        if (((unsigned char *) &a)[2] < 6) {
                            data_020db6e0 = ch;
                        } else {
                            func_0204130c(ch, ch, x);
                        }
                    }
                    break;
                case 3:
                    if (ch == 0x12) {
                        data_020db6e4 = 0x12;
                        data_020db6e0 = 0x12;
                        data_020db6dc = 0x12;
                    }
                    break;
                default:
                    break;
            }
            i++;
        } while (i < 11);
    }

    if (data_020db6e0 != 0x63) {
        MI_CpuCopy8(&a, &c, 8);
        if (func_0203fcb4(data_020db6e0, &c, 0) == 0) {
            if (data_020db6e0 == 0x13) {
                data_020db6e4 = 0x63;
                data_020db6e0 = 0x63;
            } else {
                func_0204130c(data_020db6e0, 0x63, 1);
            }
        }
    }
}
