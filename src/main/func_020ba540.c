/* func_020ba540 @ 0x020ba540, 0x178 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001c08(int);
extern void func_02001c30(int);
extern void func_0209def4(unsigned char *);
extern void func_02001afc(int);
extern void func_02001b0c(int);
extern void func_02001b34(int);
extern void func_02001b44(int);
extern void func_0205bfd0(int, int, void *);
extern int func_020961a8(int);
extern int func_020ba86c(int);
extern int func_020ba78c(int);
extern int func_020ba6f4(int);
extern void func_020ba6b8(void);
extern int data_021f75b0;
extern int data_021f8b44;

extern void func_020babb4(void);
extern void func_020bad44(void);

extern unsigned char data_021f6d2c[];
extern void func_01ffcd50(void);
extern void func_01ffceb8(void);

int func_020ba540(int param)
{
    int result = 0;
    unsigned char data[8];

    if (param == 0) {
        func_02001c08(1);
        func_0209def4(data);
        if (data[1] >= 6 && data[1] < 0x12) {
            func_02001afc(2);
        } else {
            func_02001b0c(2);
        }
        func_02001b0c(0x10);
        func_02001b0c(8);

        *(volatile unsigned short *) 0x0400100a = (*(volatile unsigned short *) 0x0400100a & ~3) | 3;
        *(volatile unsigned short *) 0x0400100e = (*(volatile unsigned short *) 0x0400100e & ~3) | 2;
        *(volatile unsigned short *) 0x0400100a = (*(volatile unsigned short *) 0x0400100a & 0x43) | 0x4c00;
        *(volatile unsigned short *) 0x0400100e = (*(volatile unsigned short *) 0x0400100e & 0x43) | 0x6f00;

        func_0205bfd0((unsigned int) data_021f6d2c, (unsigned int) func_01ffceb8, (void *) func_020bad44);
    } else {
        func_02001c30(1);
        func_0209def4(data);
        if (data[1] >= 6 && data[1] < 0x12) {
            func_02001b34(2);
        } else {
            func_02001b44(2);
        }
        func_02001b44(0x10);
        func_02001b44(8);

        *(volatile unsigned short *) 0x0400000a = (*(volatile unsigned short *) 0x0400000a & ~3) | 3;
        *(volatile unsigned short *) 0x0400000e = (*(volatile unsigned short *) 0x0400000e & ~3) | 2;
        *(volatile unsigned short *) 0x0400000a = (*(volatile unsigned short *) 0x0400000a & 0x43) | 0x4400;
        *(volatile unsigned short *) 0x0400000e = (*(volatile unsigned short *) 0x0400000e & 0x43) | 0x6700;

        func_0205bfd0((unsigned int) data_021f6d2c, (unsigned int) func_01ffcd50, (void *) func_020babb4);
    }

    if (param != data_021f75b0 || param == 1) {
        if (func_020ba86c(param) && func_020ba78c(param) && func_020ba6f4(param)) {
            data_021f75b0 = param;
            func_020ba6b8();
            result = 1;
        }
    }

    {
        int *p = (int *) func_020961a8(4);
        int *tail = &data_021f8b44;
        *tail = 0;
        if (p != 0) {
            p = (int *) ((char *) p + 0x5c);
            if (p != 0) {
                *tail = *(int *) ((char *) p + 8);
            }
        }
    }

    return result;
}
