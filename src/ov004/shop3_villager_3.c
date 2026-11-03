/* shop3_villager_3: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02221b68 @ 0x02221b68, 0x34 bytes, Thumb
 * func_ov004_02221b14 @ 0x02221b14, 0x54 bytes, Thumb
 * func_ov004_02221af4 @ 0x02221af4, 0x20 bytes, Thumb
 */

extern void *func_0202e8e4(void *argument0);
extern void *func_020edf70(int argument0);
extern void *func_ov004_022219ac(void *argument0);
extern void *data_ov004_02253fd4;
extern int func_0202e364(void *self);
extern void func_0201b38c(void *p, int a);
extern void func_0201b388(void *p, int a);
extern void func_0201b384(void *p, int a);
extern void func_0201c280(void *self, void *p);
extern void func_ov004_0222194c(void *p, void *self);
extern int func_0202e1fc(char *self);
extern void func_ov004_02221a64(char *self, int a);

void *func_ov004_02221b68(void)
{
    // DECLS
    char *self;
    // ENDDECLS
    self = (char *) func_020edf70(0xa44);
    if (self != 0) {
        func_0202e8e4(self);
        *(void **) (self) = &data_ov004_02253fd4;
        func_ov004_022219ac(self + 0x89c);
    }
    return self;
}

int func_ov004_02221b14(char *self)
{
    if (func_0202e364(self) == 0) {
        return 0;
    }
    func_0201b38c(self + 0x2a0, 0x1e);
    func_0201b388(self + 0x2a0, 0x1e);
    func_0201b384(self + 0x2a0, 0x1e);
    func_0201c280(self, self + 0x89c);
    func_ov004_0222194c(self + 0x89c, self);
    return 1;
}

int func_ov004_02221af4(char *self)
{
    int r;
    if (func_0202e1fc(self) == 0) {
        r = 0;
    } else {
        func_ov004_02221a64(self, 2);
        r = 1;
    }
    return r;
}
