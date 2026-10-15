/* func_ov004_02221bbc @ 0x02221bbc, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202de4c(void *argument0);
extern void *func_0202e5e0(void *argument0);
extern void func_02084f84(void *object);
extern void *data_ov004_02254148;
extern void *data_ov004_022541d8;

void *func_ov004_02221bbc(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022541d8;
    func_02084f84(self + 0xa54);
    *(void **) (self + 0x8a0) = &data_ov004_02254148;
    func_0202de4c(self + 0x8a0);
    func_0202e5e0(self);
    return self;
}
