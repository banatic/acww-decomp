/* rmo_telephone_8: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02231904 @ 0x02231904, 0x1c bytes, Thumb
 * func_ov004_022318f8 @ 0x022318f8, 0xc bytes, Thumb
 * func_ov004_022318a4 @ 0x022318a4, 0x54 bytes, Thumb
 * func_ov004_02231850 @ 0x02231850, 0x54 bytes, Thumb
 * func_ov004_022317f4 @ 0x022317f4, 0x5c bytes, Thumb
 */

extern int func_020edf70(unsigned int size);
extern unsigned int data_ov004_022588c8;
extern void *func_020324fc(void *);
extern void *func_02066a30(void *);
extern void *func_020b7f70(void *);
extern void *func_020b82ec(void *);
extern void *func_ov004_0222c87c(void *);
extern void *data_ov004_022558f8;
extern void *data_ov004_02255974;
extern void *func_020324c4(void *);
extern void *func_02066994(void *);
extern int func_020b7f60(void *);
extern void *func_020b82d0(void *);
extern void *func_ov004_0222c7a0(void *);
extern void func_020edf54(void *);

void *func_ov004_022318a4(char *self);

void func_ov004_02231904(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x644)))) {
        func_ov004_022318a4((char *) conditionInput0);
    }
}

unsigned int func_ov004_022318f8(void)
{
    return data_ov004_022588c8;
}

void *func_ov004_022318a4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    func_02066a30(self + 0x290);
    *(void **) (self) = &data_ov004_022558f8;
    *(void **) (self + 0x290) = &data_ov004_02255974;
    func_020324fc(self + 0x2d8);
    func_020b82ec(self + 0x374);
    func_020b7f70(self + 0x61c);
    return self;
}

void *func_ov004_02231850(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022558f8;
    *(void **) (self + 0x290) = &data_ov004_02255974;
    func_020b7f60(self + 0x61c);
    func_020b82d0(self + 0x374);
    func_020324c4(self + 0x2d8);
    func_02066994(self + 0x290);
    func_ov004_0222c7a0(self);
    return self;
}

void *func_ov004_022317f4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022558f8;
    *(void **) (self + 0x290) = &data_ov004_02255974;
    func_020b7f60(self + 0x61c);
    func_020b82d0(self + 0x374);
    func_020324c4(self + 0x2d8);
    func_02066994(self + 0x290);
    func_ov004_0222c7a0(self);
    func_020edf54(self);
    return self;
}
