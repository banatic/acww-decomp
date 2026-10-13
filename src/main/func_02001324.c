/* func_02001324 @ 0x02001324, 0x178 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_0213fdc4;
extern unsigned int data_0213fdc8;
#define gInput2 (*(unsigned short *) 0x027fffa8)

extern void func_020014b4(void);
extern void func_02001610(void);
extern void func_0200184c(void);
extern void func_0204f8b8(void);
extern void func_0200149c(void);
extern int OS_GetProcMode(void);
extern void func_020e9e78(unsigned int arg);

extern unsigned int data_021fbe8c;
extern unsigned int data_021fbe94;
extern unsigned int sSubOBJExtPltt;

void func_02001324(void)
{
    unsigned char state = data_0213fdc4;
    unsigned int keys = (unsigned short) (((*(volatile unsigned short *) 0x04000130 | gInput2) ^ 0x2fff) & 0x2fff) & 0x3ff;
    unsigned int prev = data_0213fdc8;
    unsigned int pressed = keys & (prev ^ keys);
    data_0213fdc8 = keys;

    switch (state) {
        case 0:
            if (pressed & 0x2000) {
                state = 5;
            }
            if (keys == 0x321) {
                state++;
            }
            break;
        case 1:
            if (keys == 0) {
                state++;
            }
            break;
        case 2:
            if ((keys & ~0x82) != 0) {
                state = 0;
            } else if (keys == 0x82) {
                state++;
            }
            break;
        case 3:
            if (keys == 0) {
                state++;
            }
            break;
        case 4:
            if ((keys & ~0xc) != 0) {
                state = 0;
            } else if (keys == 0xc) {
                state++;
            }
            break;
        case 5:
            func_020014b4();
            func_02001610();
            state++;
            // fall through
        case 6:
            func_02001610();
            func_0200184c();
            {
                unsigned int k4 = keys & 4;
                if (k4 != 0) {
                    if ((pressed & 1) != 0) {
                        if (k4 != 0) {
                            if (OS_GetProcMode() == 0x1f) {
                                unsigned int g1v = data_021fbe8c;
                                unsigned int g2v = data_021fbe94;
                                unsigned int g3v = sSubOBJExtPltt;
                                if (keys & 0x20) {
                                    func_020e9e78(g1v);
                                } else if (keys & 0x10) {
                                    func_020e9e78(g3v);
                                } else if (keys & 0x40) {
                                    func_020e9e78(g2v);
                                }
                            }
                        }
                    }
                    if ((pressed & 2) != 0) {
                        if (k4 != 0) {
                            func_0204f8b8();
                        }
                    }
                }
            }
            break;
    }

    func_0200149c();
    data_0213fdc4 = state;
}
