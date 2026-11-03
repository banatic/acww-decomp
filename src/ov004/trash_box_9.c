/* trash_box_9: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222fc90 @ 0x0222fc90, 0x1c bytes, Thumb
 * func_ov004_0222fc84 @ 0x0222fc84, 0xc bytes, Thumb
 * func_ov004_0222fc3c @ 0x0222fc3c, 0x48 bytes, Thumb
 * func_ov004_0222fbf4 @ 0x0222fbf4, 0x48 bytes, Thumb
 * func_ov004_0222fba4 @ 0x0222fba4, 0x50 bytes, Thumb
 */

extern int func_020edf70(unsigned int size);
extern unsigned int data_ov004_02258490;
extern void *func_020324fc(void *);
extern void *func_02066a30(void *);
extern void *func_020b82ec(void *);
extern void *func_ov004_0222c87c(void *);
extern void *data_ov004_022553d8;
extern void *data_ov004_02255454;
extern void *func_020324c4(void *);
extern void *func_02066994(void *);
extern void *func_020b82d0(void *);
extern void *func_ov004_0222c7a0(void *);
extern void func_020edf54(void *);

void *func_ov004_0222fc3c(char *self);

void func_ov004_0222fc90(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x620)))) {
        func_ov004_0222fc3c((char *) conditionInput0);
    }
}

unsigned int func_ov004_0222fc84(void)
{
    return data_ov004_02258490;
}

void *func_ov004_0222fc3c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    func_02066a30(self + 0x290);
    *(void **) (self) = &data_ov004_022553d8;
    *(void **) (self + 0x290) = &data_ov004_02255454;
    func_020324fc(self + 0x2d8);
    func_020b82ec(self + 0x374);
    return self;
}

void *func_ov004_0222fbf4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022553d8;
    *(void **) (self + 0x290) = &data_ov004_02255454;
    func_020b82d0(self + 0x374);
    func_020324c4(self + 0x2d8);
    func_02066994(self + 0x290);
    func_ov004_0222c7a0(self);
    return self;
}

void *func_ov004_0222fba4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022553d8;
    *(void **) (self + 0x290) = &data_ov004_02255454;
    func_020b82d0(self + 0x374);
    func_020324c4(self + 0x2d8);
    func_02066994(self + 0x290);
    func_ov004_0222c7a0(self);
    func_020edf54(self);
    return self;
}
