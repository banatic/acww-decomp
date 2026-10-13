/* func_ov004_02233264 @ 0x02233264, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee660();
extern void func_02055210();
extern void func_02138d6c();
extern void func_ov004_022329e0();
extern void func_ov004_02232754();
extern void func_ov004_0223248c();
extern void func_020324fc();
extern void func_ov004_022322fc();
extern void func_ov004_022324d8();
extern void func_ov004_022324f0();
extern void *data_020da13c;
extern void *data_ov004_02255ac8;
extern void *data_0213efe8;

void *func_ov004_02233264(char *self)
{
    func_020ee660(self);
    *(void **) (self) = &data_020da13c;
    *(void **) (self) = &data_ov004_02255ac8;
    func_02055210(self + 0x50);
    func_02138d6c(self + 0x108, 0x1, 0x20, (void *) func_ov004_022324f0, (void *) func_ov004_022324d8);
    func_ov004_022329e0(self + 0x128);
    func_ov004_02232754(self + 0x1228);
    func_ov004_0223248c(self + 0x3328);
    func_020324fc(self + 0x3460);
    func_ov004_022322fc(self + 0x34fc);
    *(void **) (self + 0x3534) = &data_0213efe8;
    *(char *) (self + 0x3520) = *(char *) (self + 0x3521) = *(char *) (self + 0x3540) = -1;
    return self;
}
