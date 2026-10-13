/* func_020a0340 @ 0x020a0340, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int *data_020ccf94;

extern int func_02073dd4(int *g, int i);
extern int func_02073918(int *g, int i);
extern int func_020a7330(int i);
extern int func_020a72d0(int i);
extern void func_02073d6c(int *g, int i);
extern int func_02073d70(int *g);
extern int func_02075cc4(void);

void func_020a0340(int unused, unsigned char *p, int v, int w, int e)
{
    if (*p == v) {
        int flag = 1;
        int i = 3;
        int *g = data_020ccf94;
        while (i >= 0) {
            if (func_02073dd4(g, i) != 0 && func_02073918(g, i) == 0) {
                if (!((w == func_020a7330(i) || e == func_020a7330(i)) && func_020a72d0(i) == 0)) {
                    flag = 0;
                    break;
                }
            }
            i--;
        }
        if (flag) {
            func_02073d6c(g, 1);
            *p = v + 1;
        }
    } else {
        if (*p == v + 1 && func_02073d70(data_020ccf94) == 1 && func_02075cc4() != 0) {
            *p = v + 2;
        }
    }
}
