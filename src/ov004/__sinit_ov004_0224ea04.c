/* __sinit_ov004_0224ea04 @ 0x0224ea04, 0xf4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __register_global_object(void *, void *, void *);
extern struct {
    long f0;
    long f4;
    long f8;
} data_ov004_0225836c;
extern struct {
    long f0;
    long f4;
    long f8;
} data_ov004_02258384;
extern struct {
    long f0;
    long f4;
    long f8;
} data_ov004_0225839c;
extern struct {
    long f0;
    long f4;
    long f8;
} data_ov004_02258318;
extern struct {
    long f0;
    long f4;
    long f8;
} data_ov004_02258330;
extern struct {
    long f0;
    long f4;
    long f8;
} data_ov004_02258348;
extern void func_020012dc(void);
extern unsigned char data_ov004_02258354;
extern unsigned char data_ov004_02258378;
extern unsigned char data_ov004_02258390;
extern unsigned char data_ov004_02258360;
extern unsigned char data_ov004_02258324;
extern unsigned char data_ov004_0225833c;

void __sinit_ov004_0224ea04(void)
{
    data_ov004_0225836c.f0 = 0;
    data_ov004_0225836c.f4 = 0;
    data_ov004_0225836c.f8 = 0;
    __register_global_object((void *) &data_ov004_0225836c, (void *) &func_020012dc, (void *) &data_ov004_02258354);
    data_ov004_02258384.f0 = 96000;
    data_ov004_02258384.f4 = 6400;
    data_ov004_02258384.f8 = 88064;
    __register_global_object((void *) &data_ov004_02258384, (void *) &func_020012dc, (void *) &data_ov004_02258378);
    data_ov004_0225839c.f0 = 96256;
    data_ov004_0225839c.f4 = 6656;
    data_ov004_0225839c.f8 = 78848;
    __register_global_object((void *) &data_ov004_0225839c, (void *) &func_020012dc, (void *) &data_ov004_02258390);
    data_ov004_02258318.f0 = 68608;
    data_ov004_02258318.f4 = 5632;
    data_ov004_02258318.f8 = 110592;
    __register_global_object((void *) &data_ov004_02258318, (void *) &func_020012dc, (void *) &data_ov004_02258360);
    data_ov004_02258330.f0 = 92672;
    data_ov004_02258330.f4 = 6400;
    data_ov004_02258330.f8 = 77824;
    __register_global_object((void *) &data_ov004_02258330, (void *) &func_020012dc, (void *) &data_ov004_02258324);
    data_ov004_02258348.f0 = 91648;
    data_ov004_02258348.f4 = 6400;
    data_ov004_02258348.f8 = 73216;
    __register_global_object((void *) &data_ov004_02258348, (void *) &func_020012dc, (void *) &data_ov004_0225833c);
}
