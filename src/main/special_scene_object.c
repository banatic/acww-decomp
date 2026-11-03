/* special_scene_object: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202ec38 @ 0x0202ec38, 0x20 bytes, Thumb
 * func_0202ec14 @ 0x0202ec14, 0x24 bytes, Thumb
 * func_0202ec04 @ 0x0202ec04, 0x10 bytes, Thumb
 * func_0202ebf8 @ 0x0202ebf8, 0xc bytes, Thumb
 * func_0202ebcc @ 0x0202ebcc, 0x2c bytes, Thumb
 * func_0202ebc0 @ 0x0202ebc0, 0xc bytes, Thumb
 * func_0202eb94 @ 0x0202eb94, 0x2c bytes, Thumb
 * func_0202eb88 @ 0x0202eb88, 0xc bytes, Thumb
 */

extern int func_0203efdc(char *);
extern void func_02082544(void *);
extern int func_0201b744(unsigned char *);
extern void func_02083068(void *);
extern int func_02082438(char *p1, char *p2);
extern int func_02082374(int arg);
extern unsigned char data_020e54a8;
extern unsigned char data_021c30ac[];

int func_0202ec38(void *arg0)
{
    int r4;
    int result;

    r4 = (int) arg0;
    if (func_0203efdc(arg0) == 0) {
        return 0;
    }
    func_02082544((void *) (r4 + 0xea));
    return 1;
}

int func_0202ec14(void *arg0)
{
    int result;
    void *ptr;

    if (func_0201b744(arg0) == 0) {
        return 0;
    }
    ptr = (char *) arg0 + 0x640;
    func_02083068(ptr);
    return 1;
}

void func_0202ec04(char *a, char *b)
{
    func_02082438(b, a + 234);
}

int func_0202ebf8(int arg)
{
    return func_02082374(arg + 0xea);
}

int func_0202ebcc(unsigned char *p)
{
    unsigned int ok;
    if (data_020e54a8 == 1) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok == 0 || p[0x650] == 0) {
        return 1;
    }
    return 0;
}

void func_0202ebc0(unsigned char *r0)
{
    r0[0x650] = 1;
}

unsigned short func_0202eb94(const void *ptr)
{
    unsigned short value = *(const unsigned short *) ((const char *) ptr + 0xEA);
    if (((value & 0xF000) >> 12) == 0xD) {
        return (unsigned short) ((value & 0xFFF) + 0xC8);
    } else {
        return 0xFFFF;
    }
}

unsigned int *func_0202eb88(void *object)
{
    return *(unsigned int **) data_021c30ac;
}
