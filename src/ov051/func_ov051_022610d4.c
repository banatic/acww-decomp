/* func_ov051_022610d4 @ 0x022610d4, 0xe0 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75b8;
extern int data_021dc7a8;

extern void func_02041c88(int, int, int);
extern void func_020b22d0(void);
extern int func_020a12ac(void);
extern int func_020a12d4(void);
extern int func_020a12c0(void);
extern void func_0209e474(int *);
extern void func_0206f820(int *);
extern void func_0209e6ec(int *, int);
extern void func_0209e604(int *);
extern void func_0209f100(int *, int);
extern int func_0204e414(void);
extern void func_0204dfe0(int, int *, int, int);
extern int func_020b5e10(void);
extern void func_020b63f4(int, int, int *, int, int, int, int);
extern void func_ov051_0226122c(int, int);

int func_ov051_022610d4(int param)
{
    unsigned int flag = (data_021c75b8 == 0) ? 1 : 0;
    if (flag > 0) {
        int pair[2];
        int buf[3];

        func_02041c88(3, 0, 1);
        func_020b22d0();

        if (func_020a12ac() != 0 || func_020a12d4() != 0) {
            pair[0] = 0;
            pair[1] = 0;
            func_0209e474(pair);
            func_0206f820(pair);
        }

        if (func_020a12d4() != 0) {
            func_0209e6ec(&data_021dc7a8, 0);
            func_0209e604(&data_021dc7a8);
        } else if (func_020a12ac() != 0) {
            func_0209e6ec(&data_021dc7a8, 6);
            func_0209e604(&data_021dc7a8);
        } else if (func_020a12c0() != 0) {
            func_0209e6ec(&data_021dc7a8, 1);
            func_0209e604(&data_021dc7a8);
        }

        func_0209f100(&data_021dc7a8, 0x12);
        func_0204dfe0(func_0204e414(), buf, 0, 0);
        func_020b63f4(func_020b5e10(), 0, buf, 0x00400000, -32768, 3, 2);
        func_ov051_0226122c(param, 2);
    }
    return 1;
}
