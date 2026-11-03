/* fox_tent_2: 2 functions, module ov052
 * mwccarm 1.2/base -O4,s
 * func_ov052_022611f0 @ 0x022611f0, 0x50 bytes, Thumb
 * func_ov052_022611ac @ 0x022611ac, 0x44 bytes, Thumb
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *argument0, int argument1, int argument2, int argument3, int argument4, short argument5,
                         short argument6, int argument7, int argument8, unsigned short argument9, unsigned short argument10);
extern int func_0201c2c8(void *, int);
extern void func_0201aff4(void *, int);
extern int func_02019e00(int);
extern int func_02019de8(int);
extern int func_02019c6c(int, int, unsigned short);
extern int func_0203e0a8(int, int);

int func_ov052_022611f0(void *p)
{
    int ret;

    func_02019d0c((void *) ((void *) ((char *) p + 0x564)), (int) ((int) (3)), (int) ((int) (1)), (int) ((int) (0)),
                  (int) ((int) (0)), (short) ((short) (0)), (short) ((short) (0)), (int) ((int) (0)), (int) ((int) (0)),
                  (unsigned short) ((unsigned short) (data_020c80f8)), (unsigned short) ((unsigned short) (0)));
    ret = func_0201c2c8(p, 4);
    func_0201aff4((char *) p + 0x350, ret);

    return 1;
}

int func_ov052_022611ac(int p)
{
    if (func_02019e00(p + 0x564) == 3) {
        if (func_02019de8(p + 0x564) != 0) {
            func_02019c6c(p + 0x564, 1, *(unsigned short *) (p + 0x71c));
        }
    }
    func_0203e0a8(p, 0);
    return 1;
}
