/* func_ov003_022140a8 @ 0x022140a8, 0x158 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(void *p, int a);
extern int func_ov003_0220c934(void *p);
extern unsigned int *func_0200f27c(void *p, int a);
extern int func_0200f328(void *p, int a);
extern void func_0205eae0(void *p, int a, int b, int c);
extern void func_0200fa1c(void *out, void *self, void *b, void *c, void *d);
extern void func_0204f7e0(void *a, void *b);
extern int func_020310d0(void *a, void *b, int c);
extern int func_ov003_02213f74(void *self, void *a, void *b, void *flag);

extern unsigned char data_ov003_0223811c[];
extern unsigned char data_ov003_02238120[];

int func_ov003_022140a8(char *self, unsigned char *flag, int *a, int *b)
{
    int hash1;
    int hash2;
    int buf1[3];
    int buf2[3];

    if (func_02056f28(self + 0x2d0, 4) != 0) {
        if (func_ov003_0220c934(self) != 0) {
            func_0200f27c(self, 9);
            func_0200f328(self, 0x846);
            *(int *) (self + 0x2e0) = 0;
            func_0205eae0(self + 0x5a0, 4, 3, 1);
            if (*(unsigned char *) (self + 0x16c) == 4) {
                return 3;
            }
            if (*flag != 0) {
                return 1;
            }
            return 2;
        }
        func_0200fa1c(buf1, self, self + 0x5c, self + 0x8e, (void *) data_ov003_0223811c);
        func_0204f7e0(buf1, buf1);
        if (func_020310d0(buf1, &hash1, 0x19) >= 0x400) {
            func_0200f27c(self, 9);
            func_0200f328(self, 0x846);
            *(int *) (self + 0x2e0) = 0;
            func_0205eae0(self + 0x5a0, 4, 3, 1);
            if (*flag != 0) {
                if (func_ov003_02213f74(self, buf1, a, b) != 0) {
                    return 1;
                }
                return 2;
            }
            return 2;
        }
    } else if (func_02056f28(self + 0x2d0, 3) != 0) {
        if (*flag != 0) {
            func_0200fa1c(buf2, self, self + 0x5c, self + 0x8e, (void *) data_ov003_02238120);
            func_0204f7e0(buf2, buf2);
            if (func_020310d0(buf2, &hash2, 0x19) >= 0x400) {
                if (func_ov003_02213f74(self, buf2, a, b) != 0) {
                    return 1;
                }
                return 2;
            }
        }
    }
    return 0;
}
