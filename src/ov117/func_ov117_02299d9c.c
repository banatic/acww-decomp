/* func_ov117_02299d9c @ 0x02299d9c, 0xa8 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(int);
extern int func_0204f3e4(int, int *, int *, int *, int *, unsigned short *, unsigned short *, int, int);
extern void func_0204f800(int *, int *, int, int, int, int);
extern int func_020b3b50(unsigned short *);
extern void func_020b3c58(int, int *, int *, int *, int *);
extern void func_ov117_0229a2a4(int, int, int, int, int);

void func_ov117_02299d9c(int arg)
{
    unsigned short h;
    int v18, v1c, v20, v24, v28, v2c, v30, v34, v38, v3c;
    int ret1;

    ret1 = func_0204e414(arg);
    if (ret1) {
        h = 0x5000;
        if (func_0204f3e4(ret1, &v20, &v24, &v28, &v2c, &h, &h, 0x200, 0)) {
            func_0204f800(&v18, &v1c, v20, v24, v28, v2c);
            v18 <<= 1;
            v1c <<= 1;
            v18 += 1;
            v1c += 1;
            {
                int ret3 = func_020b3b50(&h);
                if (ret3) {
                    func_020b3c58(ret3, &v30, &v34, &v38, &v3c);
                    v18 += v30 >> 11;
                    v1c += v34 >> 11;
                }
            }
            func_ov117_0229a2a4(arg, 0xC, v18, v1c, 0);
        }
    }
}
