/* func_ov074_02278a90 @ 0x02278a90, 0x4c bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02088220(int arg);
extern int func_0203cfb0(void *x, void *y);
extern int func_ov074_02278adc(void *arg);
extern void func_020b9d3c(void *p, int b, void *c, int d, int e, int f);
extern void *data_ov074_02279b44;

extern unsigned char data_021f3278[];

void func_ov074_02278a90(void *a, void *b)
{
    void *r;
    int v;

    r = func_02088220((unsigned int) data_021f3278);
    if (r == 0) {
        return;
    }
    if (func_0203cfb0(*(void **) a, r) == 0) {
        return;
    }
    v = func_ov074_02278adc(a);
    if (v == 0) {
        return;
    }
    func_020b9d3c((char *) a + 4, *(int *) ((char *) b + 0x5c), data_ov074_02279b44, v, 0, 0);
}
