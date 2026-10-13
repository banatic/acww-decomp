/* func_ov003_02220460 @ 0x02220460, 0xc0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1f24[];
extern void *data_021c80bc;

extern void func_0204f794(int *dst, void *x, void *y);
extern void func_020b2a68(void *obj, void *table);
extern int func_020b2a60(void *obj);
extern int func_02003348(int a, unsigned short b, int *c, int d, int e);
extern void func_020b2a64(void *obj);
extern void func_0204eb1c(void *a, unsigned short *b, void *c, void *d, int e);
extern void func_ov003_0222040c(void *a, unsigned short *b, void *c, void *d);

int func_ov003_02220460(void *a, unsigned short *b, void *c, void *d, unsigned char e)
{
    int local[3];
    struct {
        unsigned int pad[3];
    } obj;
    unsigned short val;
    unsigned int flag;
    unsigned int index;
    void *table;

    local[0] = 0;
    local[1] = 0;
    local[2] = 0;
    func_0204f794(local, c, d);

    flag = 0;
    val = *b;
    if (val >= 0x5000 && val <= 0x5021) {
        flag = 1;
    }

    if (flag) {
        index = val & 0xfff;
    } else {
        index = -1;
    }

    if (index < 0x22) {
        table = data_020d1f24 + index * 10;
    } else {
        table = data_020d1f24;
    }

    func_020b2a68(&obj, table);

    if (func_02003348(func_020b2a60(&obj), *b, local, 0, 0) != 0) {
        if (e != 0) {
            func_0204eb1c(data_021c80bc, b, c, d, 0);
            func_ov003_0222040c(a, b, c, d);
        }
        func_020b2a64(&obj);
        return 1;
    } else {
        func_020b2a64(&obj);
        return 0;
    }
}
