/* taxi_driver_2: 12 functions, module ov051
 * mwccarm 1.2/base -O4,s
 * func_ov051_02261224 @ 0x02261224, 0x8 bytes, Thumb
 * func_ov051_02261220 @ 0x02261220, 0x4 bytes, Thumb
 * func_ov051_0226121c @ 0x0226121c, 0x4 bytes, Thumb
 * func_ov051_022611e0 @ 0x022611e0, 0x3c bytes, Thumb
 * func_ov051_022611c4 @ 0x022611c4, 0x1c bytes, Thumb
 * func_ov051_022611c0 @ 0x022611c0, 0x4 bytes, Thumb
 * func_ov051_022611bc @ 0x022611bc, 0x4 bytes, Thumb
 * func_ov051_022611b8 @ 0x022611b8, 0x4 bytes, Thumb
 * func_ov051_022611b4 @ 0x022611b4, 0x4 bytes, Thumb
 * func_ov051_022610d4 @ 0x022610d4, 0xe0 bytes, Thumb
 * func_ov051_022610d0 @ 0x022610d0, 0x4 bytes, Thumb
 * func_ov051_02261088 @ 0x02261088, 0x48 bytes, Thumb
 */

typedef struct {
    int pad_00;
    int unk_04;
} UnkStruct_02261088;

extern unsigned char data_021c75b8;
extern int func_020e8840(void *ptr);
extern void func_ov051_0226122c(char *self, int arg);
extern int func_020147e0(void *a, int b, int c);
extern int data_021dc7a8;
extern int func_02041c88(int, int, int);
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
extern int func_0204dfe0(int, int *, int, int);
extern int func_020b5e10(void);
extern int func_020b63f4(int, int, int *, int, int, int, int);
extern UnkStruct_02261088 *func_020682e0(int);
extern int func_020644cc(int);
extern int func_ov068_02273030(void);
extern void func_0203ac18(void);
extern int func_02041d14(int, int);
extern void func_0200468c(void);

int func_ov051_02261224(void)
{
    return 65535;
}

int func_ov051_02261220(void)
{
    return 10;
}

int func_ov051_0226121c(void)
{
    return 1;
}

int func_ov051_022611e0(char *self)
{
    unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag > 0) {
        if (func_020e8840(self + 0x718) == 0) {
            func_ov051_0226122c(self, 1);
        }
    }
    return 1;
}

int func_ov051_022611c4(void *self)
{
    func_020147e0((char *) self + 0x618, 1, 0);
    return 1;
}

int func_ov051_022611c0(void)
{
    return 1;
}

int func_ov051_022611bc(void)
{
    return 1;
}

int func_ov051_022611b8(void)
{
    return 1;
}

int func_ov051_022611b4(void)
{
    return 1;
}

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
        func_ov051_0226122c((char *) param, 2);
    }
    return 1;
}

int func_ov051_022610d0(void)
{
    return 1;
}

int func_ov051_02261088(void *param)
{
    if (func_020682e0(0)->unk_04 == 0) {
        if (func_020644cc(4) == 0) {
            func_ov068_02273030();
            func_0203ac18();
            ((char *) param)[0x71a] = 0xa;
        }
        func_02041d14(0, 0xf);
        func_0200468c();
        func_ov051_0226122c((char *) param, 3);
    }
    return 1;
}
