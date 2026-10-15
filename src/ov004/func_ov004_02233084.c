/* func_ov004_02233084 @ 0x02233084, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022323d4(void *);
extern void func_ov004_0223232c(void *);
extern void func_ov004_0223228c(void *);
extern void func_ov004_02232edc(void *);
extern void func_ov004_02232a94(void *);
extern void func_ov004_02232a20(void *, void *);
extern void func_ov004_02232a68(void *);
extern void func_ov004_02232b48(void *);
extern int func_0205790c(void *, void *);
extern int func_02057a50(void *, const char *name);
extern void func_02055dc8(void *, int, int);
extern void func_ov004_02231c7c(void *);
extern int func_0200430c(void *);
extern void func_ov004_02231b38(void *);
extern void *data_ov004_022589fc;
extern char data_ov004_02255b50;
extern char data_ov004_02255b58;
extern char data_ov004_02255b60;
extern char data_ov004_02255b68;

int func_ov004_02233084(char *self)
{
    data_ov004_022589fc = self;
    func_ov004_022323d4(self + 0x3328);
    func_ov004_0223232c(self + 0x3460);
    func_ov004_0223228c(self + 0x34fc);
    func_ov004_02232edc(self);
    func_ov004_02232a94(self);
    func_ov004_02232a20(self, *(void **) (self + 0xac));
    func_ov004_02232a68(self);
    func_ov004_02232b48(self);
    self[0x3520] = func_0205790c(*(void **) (self + 0xac), &data_ov004_02255b50);
    self[0x3521] = func_0205790c(*(void **) (self + 0xac), &data_ov004_02255b58);
    self[0x3523] = func_0205790c(*(void **) (self + 0xac), &data_ov004_02255b60);
    self[0x3540] = func_02057a50(*(void **) (self + 0xac), (const char *) (&data_ov004_02255b68));
    func_02055dc8(self + 0x50, (int) func_ov004_02231b38, (int) self);
    func_ov004_02231c7c(self);
    func_0200430c(self + 0x3534);
    return 1;
}
