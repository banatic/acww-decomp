/* func_ov003_02235d88 @ 0x02235d88, 0x188 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02235f2c(void *element);
extern void func_ov003_02235f30(void *element);
extern void *func_ov003_02235f10(void *base);
extern void __cxa_vec_ctor(void *a, int b, int c, void (*d)(void *), void (*e)(void *));
extern void __register_global_object(void *a, void *(*b)(void *), void *node);
extern void func_ov003_02236028(void *base);
extern void func_0204f800(int *ox, int *oz, int ax, int ay, int j, int i);
extern int func_020319e4(int x, int z);
extern int func_020319ac(int x, int z);
extern void func_ov003_02235fb8(void *base, int x, int z);
extern unsigned short *func_0204f5e0(void *grid, int ax, int az, int x, int z, unsigned char w);
extern void func_0204f818(int *ox, int *oz, void *p);
extern int func_ov003_02235f34(void *base, int *ox, int *oz);
extern void func_0204f794(void *a, int x, int z);

extern int data_ov003_02262b28;
extern void *data_021c80bc;
extern unsigned char data_ov003_02262b58[];
extern unsigned char data_ov003_02262b2c[];

int func_ov003_02235d88(void *a0, void *a1, void *a2, int a3)
{
    void *grid;
    long tx;
    long tz;
    int ux, uz;
    unsigned int ax;
    int px, pz;
    int qx, qz;
    int rx, rz;
    unsigned int ay;
    unsigned int i, j;
    int lz, lx;
    unsigned short *it;

    grid = data_021c80bc;
    if ((data_ov003_02262b28 & 1) == 0) {
        __cxa_vec_ctor(data_ov003_02262b58, 0x10, 0x22, func_ov003_02235f30, func_ov003_02235f2c);
        __register_global_object(data_ov003_02262b58, func_ov003_02235f10, data_ov003_02262b2c);
        data_ov003_02262b28 |= 1;
    }
    func_ov003_02236028(data_ov003_02262b58);

    for (ay = 1; ay < 6; ay++) {
        for (ax = 1; ax < 6; ax++) {
            for (i = 0; i < 0x10; i++) {
                for (j = 0; j < 0x10; j++) {
                    func_0204f800(&px, &pz, ax, ay, j, i);
                    if (func_020319e4(px, pz) == 0 || func_020319ac(px, pz + 1) == 0 || func_020319ac(px, pz + 2) == 0) {
                        func_ov003_02235fb8(data_ov003_02262b58, px, pz);
                    } else if (a3 != 0) {
                        // Distinct long snapshots preserve both coordinate lifetimes.
                        tx = px;
                        tz = pz;
                        ux = (int) tx >> 4;
                        uz = (int) tz >> 4;
                        it = func_0204f5e0(grid, ux, uz, tx - (ux << 4), tz - (uz << 4), 0);
                        if (it != 0 && *it != 0xfff1) {
                            func_ov003_02235fb8(data_ov003_02262b58, px, pz);
                        }
                    }
                }
            }
        }
    }

    if (a2 != 0) {
        func_0204f818(&qx, &qz, a2);
        for (lz = qz - 7; lz <= qz + 7; lz++) {
            for (lx = qx - 7; lx <= qx + 7; lx++) {
                func_ov003_02235fb8(data_ov003_02262b58, lx, lz);
            }
        }
    }
    if (func_ov003_02235f34(data_ov003_02262b58, &rx, &rz) != 0) {
        func_0204f794(a1, rx, rz);
        return 1;
    }
    if (a3 != 0) {
        return func_ov003_02235d88(a0, a1, a2, 0);
    }
    return 0;
}
