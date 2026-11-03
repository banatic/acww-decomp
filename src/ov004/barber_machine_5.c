/* barber_machine_5: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222cdc8 @ 0x0222cdc8, 0x1c bytes, Thumb
 * func_ov004_0222cd8c @ 0x0222cd8c, 0x3c bytes, Thumb
 * func_ov004_0222cd50 @ 0x0222cd50, 0x3c bytes, Thumb
 * func_ov004_0222cd0c @ 0x0222cd0c, 0x44 bytes, Thumb
 * func_ov004_0222cc84 @ 0x0222cc84, 0x88 bytes, Thumb
 */

#include "types.h"

extern int func_020edf70(unsigned int size);
extern void *func_020324fc(void *);
extern void *func_02066a30(void *);
extern void *func_ov004_0222c87c(void *);
extern void *data_ov004_02254c58;
extern void *data_ov004_02254cc8;
extern void *func_020324c4(void *);
extern void *func_02066994(void *);
extern void *func_ov004_0222c7a0(void *);
extern void func_020edf54(void *);
extern void func_02055050(void *);
extern void func_02055060(void *, int, int, int, int, int);
extern int func_02055140(void *, int);
extern int func_ov004_0222c3c4(void *, int);
extern int func_ov004_0222c600(void *, void *, void *);
extern int func_ov004_0222c904(void *);
extern void *data_021c9b24;
extern void *data_ov004_02254d40;
extern void *data_ov004_02254d5c;
extern void *data_ov004_02258224;

void *func_ov004_0222cd8c(char *self);

void func_ov004_0222cdc8(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_020edf70(0x378)))) {
        func_ov004_0222cd8c((char *) conditionInput0);
    }
}

void *func_ov004_0222cd8c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    func_02066a30(self + 0x290);
    *(void **) (self) = &data_ov004_02254c58;
    *(void **) (self + 0x290) = &data_ov004_02254cc8;
    func_020324fc(self + 0x2d8);
    return self;
}

void *func_ov004_0222cd50(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02254c58;
    *(void **) (self + 0x290) = &data_ov004_02254cc8;
    func_020324c4(self + 0x2d8);
    func_02066994(self + 0x290);
    func_ov004_0222c7a0(self);
    return self;
}

void *func_ov004_0222cd0c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02254c58;
    *(void **) (self + 0x290) = &data_ov004_02254cc8;
    func_020324c4(self + 0x2d8);
    func_02066994(self + 0x290);
    func_ov004_0222c7a0(self);
    func_020edf54(self);
    return self;
}

int func_ov004_0222cc84(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) ((char *) &data_ov004_02258224) = self;
    *(u8 *) (self + 0x374) = 0x0;
    func_ov004_0222c600(self, &data_ov004_02254d40, &data_ov004_02254d5c);
    func_ov004_0222c904(self);
    if (func_ov004_0222c3c4(self + 0x1a4, 0x0) != 0x0 &&
        func_02055140(self + 0xec, *(int *) ((char *) &data_021c9b24)) != 0x0) {
        func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x0), 0x1, 0x1000, 0x0, 0x0);
        func_02055050(self + 0xec);
    }
    return 0x1;
}
