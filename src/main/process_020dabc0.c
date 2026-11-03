/* process_020dabc0: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203fb3c @ 0x0203fb3c, 0x44 bytes, Thumb
 * func_0203fb18 @ 0x0203fb18, 0x24 bytes, Thumb
 * func_0203fb14 @ 0x0203fb14, 0x4 bytes, Thumb
 * func_0203fb10 @ 0x0203fb10, 0x4 bytes, Thumb
 * func_0203fae4 @ 0x0203fae4, 0x2c bytes, Thumb
 * func_0203fabc @ 0x0203fabc, 0x28 bytes, Thumb
 * func_0203fa9c @ 0x0203fa9c, 0x20 bytes, Thumb
 */

extern void func_0203fe58(int);
extern int func_02073d90(void *);
extern void *data_020ccf94;
extern int data_021c74b4;
extern int data_021c8188;
extern int func_02050974(int *ptr);
extern void func_0203fe1c(int arg);
extern void func_02040bfc(void);
extern int func_020a12e8(void);
extern int func_020984e8(void);
extern int func_02099020(int, int);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020dabc0[];

int func_0203fb3c(void)
{
    if (func_02073d90(data_020ccf94) == 0) {
        if (data_021c74b4) {
            func_0203fe58(0);
        }
        data_021c74b4 = 0;
    } else {
        func_0203fe58(0);
        data_021c74b4 = 1;
    }
    return 1;
}

int func_0203fb18(int arg0)
{
    if (func_02050974(&data_021c8188) != 3) {
        (func_0203fe1c(arg0), func_02040bfc());
    }
    return 1;
}

int func_0203fb14(void)
{
    return 1;
}

int func_0203fb10(void)
{
    return 1;
}

int func_0203fae4(void)
{
    int ret = 0;
    int r;
    if (func_020a12e8()) {
        ret = 1;
    } else {
        r = func_020984e8();
        if (r == 0 || func_02099020(r, 1)) {
            ret = 1;
        }
    }
    return ret;
}

void *func_0203fabc(void *self)
{
    *(volatile unsigned int *) self = (unsigned int) data_020dabc0;
    *(volatile unsigned int *) self = (unsigned int) data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

void *func_0203fa9c(void *ptr)
{
    *(volatile void **) ptr = (void *) data_020dabc0;
    *(volatile void **) ptr = (void *) data_020da13c;
    func_020ee62c(ptr);
    return ptr;
}
