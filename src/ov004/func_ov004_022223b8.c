/* func_ov004_022223b8 @ 0x022223b8, 0x164 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206837c(int);
extern void func_020ab670(void *, int, int);
extern void func_020ab628(void *, int, unsigned char *, int, void *, int, int);
extern void func_020ab5f8(void *);
extern void func_02068388(int, int);
extern int func_020644cc(int);
extern char data_021f43f8[];
extern int func_ov004_02222178(void *, int);
extern void func_0200467c(int);
void func_ov004_022223b8(unsigned char *self)
{
    unsigned char *owner = *(unsigned char **) (self + 0x1a8);
    void *window;
    unsigned char values[5];
    if (owner[0x899] == 0) {
        switch (self[0x1e]) {
            case 0:
            case 1:
            case 2:
                window = func_0206837c(*(int *) (self + 0x40));
                if (window) {
                    func_020ab670(window, 3, 2);
                    values[0] = 21;
                    func_020ab628(window, 0, &values[0], 0, data_021f43f8, 0, 0);
                    values[1] = 22;
                    func_020ab628(window, 1, &values[1], 0, data_021f43f8, 0, 0);
                    values[2] = func_020644cc(10) + 10;
                    func_020ab628(window, 2, &values[2], 0, data_021f43f8, 0, 0);
                    func_020ab5f8(window);
                    func_02068388(*(int *) (self + 0x40), 1);
                }
                break;
            case 3:
            case 4:
            case 5:
                window = func_0206837c(*(int *) (self + 0x40));
                if (window) {
                    func_020ab670(window, 2, 1);
                    values[3] = 23;
                    func_020ab628(window, 0, &values[3], 0, data_021f43f8, 0, 0);
                    values[4] = func_020644cc(10) + 120;
                    func_020ab628(window, 1, &values[4], 0, data_021f43f8, 0, 0);
                    func_020ab5f8(window);
                    func_02068388(*(int *) (self + 0x40), 1);
                }
                break;
        }
    } else {
        switch (self[0x1e]) {
            case 7:
            case 8:
            case 9:
                func_ov004_02222178(owner, 5);
                break;
            case 16:
            case 17:
            case 18:
                func_0200467c(95);
                break;
        }
    }
}
