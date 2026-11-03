/* menu_dispatch_2: 4 functions, module ov092
 * mwccarm 1.2/base -O4,s
 * func_ov092_022994a0 @ 0x022994a0, 0x24 bytes, Thumb
 * func_ov092_02299480 @ 0x02299480, 0x1e bytes, Thumb
 * func_ov092_02299460 @ 0x02299460, 0x1e bytes, Thumb
 * func_ov092_0229945c @ 0x0229945c, 0x4 bytes, Thumb
 */

extern void *func_ov002_02207f80(int argument0);
extern void *func_ov002_0220830c(void *argument0);
extern void *data_ov092_02299508;
extern void func_020041fc(void);
extern void func_0206f54c(void);
extern void func_0206fe38(void);
extern void func_ov092_02298f5c(void *);
extern void func_020041ec(void);
extern void func_0206ef34(void);
extern void func_ov092_02298f58(char *self);

void *func_ov092_022994a0(void)
{
    // DECLS
    char *self;
    // ENDDECLS
    self = (char *) func_ov002_02207f80(0x94);
    if (self != 0) {
        func_ov002_0220830c(self);
        *(void **) (self) = &data_ov092_02299508;
    }
    return self;
}

int func_ov092_02299480(char *self)
{
    // DECLS
    // ENDDECLS
    func_0206f54c();
    ((void) (((void) (func_ov092_02298f5c(self)), func_020041fc())), func_0206fe38());
    return 0x1;
}

int func_ov092_02299460(char *self)
{
    func_0206f54c();
    func_0206ef34();
    func_ov092_02298f58(self);
    func_020041ec();
    return 1;
}

int func_ov092_0229945c(void)
{
    return 1;
}
