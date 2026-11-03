/* room_object_map_3: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220fed0 @ 0x0220fed0, 0x2c bytes, Thumb
 * func_ov004_0220feac @ 0x0220feac, 0x22 bytes, Thumb
 * func_ov004_0220fe24 @ 0x0220fe24, 0x86 bytes, Thumb
 * func_ov004_0220fdec @ 0x0220fdec, 0x38 bytes, Thumb
 */

extern int func_020984e8(void);
extern int func_02099870(int object);
extern int func_02094ffc(void *object);
extern int func_020ea990(int a, int c);
extern void *func_020961a8(int i);
extern unsigned int func_020826cc(void);
extern void *func_02082664(unsigned int i);
extern int func_ov004_0220d4c0(void *argument0);
extern int func_ov004_0220d4c8(short *argument0);
extern int func_ov004_0223cd58(int *argument0, unsigned int argument1);
extern int func_ov004_0223ce84(void);

int func_ov004_0220fed0(void)
{
    int object;
    int child;
    if ((object = func_020984e8()) != 0 && (child = func_02099870(object)) != 0) {
        if (func_02094ffc((void *) child) == 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}

int func_ov004_0220feac(int a, int b, int c, int d)
{
    int r;
    if (func_020ea990(a, c) < b + d) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

int func_ov004_0220fe24(void *self, int a1, int a2, int a3, int a4)
{
    void *base;
    void *o;
    unsigned int i;
    unsigned int j;
    unsigned int n;

    base = func_020961a8(4);
    if (base != 0) {
        for (i = 0; i < 4; i++) {
            o = func_020961a8(i);
            if (o != 0 && base != o && func_ov004_0220feac((int) self, a1, (int) ((char *) o + 0x5c), a3) != 0) {
                return 0;
            }
        }
        n = func_020826cc();
        for (j = 0; j < n; j++) {
            o = func_02082664(j);
            if (o != 0 && func_ov004_0220feac((int) self, a2, (int) ((char *) o + 0x5c), a4) != 0) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int func_ov004_0220fdec(char *self)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_0220d4c8((short *) (self + 0x17c));
    if (v1 != 0x0) {
        v2 = func_ov004_0223ce84();
        return func_ov004_0223cd58((int *) (v2), (unsigned int) (func_ov004_0220d4c0(self + 0x17c)));
    }
    return 0x0;
}
