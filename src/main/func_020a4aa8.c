/* func_020a4aa8 @ 0x020a4aa8, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021e5a2c;
extern int data_021dc7a8;

extern int func_020a259c(unsigned char *self, int);
extern void func_0209dfc0(void);
extern void func_0207bddc(int *p, int);
extern void func_0209e6ec(int *p, int);
extern void func_02042458(void);
extern void func_0209e604(int *p);
extern void func_020a4e94(unsigned char *self, int);

void func_020a4aa8(unsigned char *self)
{
    switch (self[0xa1]) {
        case 0:
            if (func_020a259c(self, 0) == 0) {
                break;
            }
            func_0209dfc0();
            self[0xa1]++;
            break;
        case 1:
            func_0207bddc(&data_021e5a2c, 0);
            self[0xa1]++;
            break;
        case 2:
            func_0209e6ec(&data_021dc7a8, 2);
            self[0xa1]++;
            break;
        case 3:
            func_02042458();
            self[0xa1]++;
            break;
        case 4:
            func_0209e604(&data_021dc7a8);
            self[0xa1]++;
            break;
        default:
            func_020a4e94(self, 4);
            break;
    }
}
