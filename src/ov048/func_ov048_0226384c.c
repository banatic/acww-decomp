/* func_ov048_0226384c @ 0x0226384c, 0x118 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int);
extern void *func_0203f130(void *arg0);
extern void *func_0205467c(void *);
extern void func_0201b394(void *);
extern void *func_0201a430(void *);
extern int func_020169a8(void *);
extern int func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void *func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void *func_02032c64(void *);
extern void *func_02089c88(void *);
extern void *func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_ov048_02262738(void *);

extern char data_020d8c64;
extern char data_020da088;
extern char data_ov048_02264298;

void *func_ov048_0226384c(void)
{
    char *obj;
    obj = func_020edf70(0x0e74);
    if (obj == 0) {
        goto done;
    }
    func_0203f130((void *) obj);
    *(void **) obj = (void *) &data_020d8c64;
    *(unsigned short *) (obj + 0xea) = 0xfff1;
    func_0205467c(obj + 0xec);
    func_0201b394(obj + 0x2a0);
    func_0201a430(obj + 0x2ac);
    func_020169a8(obj + 0x334);
    func_0201b324(obj + 0x350);
    func_0201af14(obj + 0x3a8);
    func_0201b370(obj + 0x3aa);
    func_0201adec(obj + 0x3b0);
    func_0201a7ec(obj + 0x418);
    func_0201a794(obj + 0x420);
    func_02032c64(obj + 0x49c);
    func_02089c88(obj + 0x4cc);
    func_020f55cc(obj + 0x514);
    func_02013c2c(obj + 0x558);
    func_02019eb0(obj + 0x564);
    func_0201489c(obj + 0x618);
    *(void **) obj = (void *) &data_020da088;
    func_02082f60(obj + 0x640);
    *(void **) obj = (void *) &data_ov048_02264298;
    func_ov048_02262738(obj + 0x658);
done:
    return obj;
}
