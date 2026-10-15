/* func_020290b0 @ 0x020290b0, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern unsigned int func_0207b86c(void *, int, void *);
extern int func_0209bd10(unsigned int);
extern int func_0209bc94(unsigned int);
extern int func_020292b4(int, int, int, unsigned int);
extern int func_0202a1cc(int, int, int, unsigned int);
extern int func_0202913c(int, int, int, unsigned int);
extern int data_021e5a2c;

int func_020290b0(int a, int b, int c)
{
    int ret;
    void *x;
    unsigned int idx;

    x = func_020984e8();
    ret = 0;
    if (func_02099020(x, 1) == 0) {
        idx = func_0207b86c(&data_021e5a2c, b, x);
        if (idx < 0x16) {
            switch (func_0209bd10(idx)) {
                case 0:
                    ret = func_020292b4(a, b, c, idx);
                    break;
                case 1:
                    switch (func_0209bc94(idx)) {
                        case 0:
                            break;
                        case 1:
                            ret = func_0202a1cc(a, b, c, idx);
                            break;
                        case 3:
                            ret = func_0202913c(a, b, c, idx);
                            break;
                    }
                    break;
            }
        }
    }
    return ret;
}
