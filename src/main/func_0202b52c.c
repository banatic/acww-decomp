/* func_0202b52c @ 0x0202b52c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209c310(unsigned int);
extern int func_02099f7c(void *, void *);
extern int func_020644cc(unsigned char);
extern unsigned short func_0209a034(int);
extern void *data_020c8f38[];

void func_0202b52c(unsigned short *out, unsigned int p1)
{
    struct {
        unsigned short mask;
        unsigned char flag;
    } local;
    int count;
    unsigned short mask;
    int i;

    *out = 0xFFF1;
    if (func_0209c310(p1) != 0) {
        return;
    }
    if (p1 >= 5) {
        return;
    }
    if (func_02099f7c(&local, data_020c8f38[p1]) > 0) {
        count = func_020644cc(local.flag);
        mask = local.mask;
        for (i = 0; i < 15; i++) {
            if ((mask >> i) & 1) {
                if (count == 0) {
                    *out = func_0209a034(i);
                    return;
                } else {
                    count--;
                }
            }
        }
    }
}
