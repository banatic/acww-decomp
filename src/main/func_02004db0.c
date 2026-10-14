/* func_02004db0 @ 0x02004db0, 0x184 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020d82b4;
extern void *data_020d832c;
extern void *data_020d8414;
extern void func_0200e91c(void);
extern void __cxa_vec_cleanup(void *list, int count, int size, void *ctor);
extern void func_0201a790(void *p);
extern void func_020f5914(void *p);
extern void func_020f5400(void *p);
extern void func_02032c50(void *p);
extern void func_0205f8d4(void *p);
extern void func_0205d51c(void *p);
extern void func_02064638(void *p);
extern void func_02056910(void *p);
extern void func_0205db6c(void *p);
extern void func_0205d8e8(void *p);
extern void func_0205dcd4(void *p);
extern void func_0205cce4(void *p);
extern void func_0205ef90(void *p);
extern void func_0205df18(void *p);
extern void func_02055764(void *p);
extern void func_0205e4ec(void *p);
extern void func_0205d0bc(void *p);
extern void func_0205f770(void *p);
extern void func_02054b64(void *p);
extern void func_020b7ed8(void *p);
extern void func_02089bbc(void *p);
extern void func_02066994(void *p);
extern void func_0203f080(void *p);

void *func_02004db0(char *self)
{
    *(void **) (self + 0) = &data_020d82b4;
    *(void **) (self + 0xec) = &data_020d832c;
    __cxa_vec_cleanup(self + 0x934, 0x1e, 0x1c, (void *) func_0200e91c);
    func_0201a790(self + 0x90c);
    *(void **) (self + 0x880) = &data_020d8414;
    func_020f5914(self + 0x880);
    func_020f5400(self + 0x83c);
    func_02032c50(self + 0x7a4);
    func_0205f8d4(self + 0x7a0);
    func_0205d51c(self + 0x774);
    func_02064638(self + 0x768);
    func_02056910(self + 0x73c);
    func_02056910(self + 0x710);
    func_0205db6c(self + 0x70f);
    func_0205d8e8(self + 0x70e);
    func_0205dcd4(self + 0x70d);
    func_0205cce4(self + 0x701);
    func_0205cce4(self + 0x700);
    func_0205ef90(self + 0x5a0);
    func_0205df18(self + 0x59c);
    func_02055764(self + 0x500);
    func_02055764(self + 0x464);
    func_0205e4ec(self + 0x428);
    func_02055764(self + 0x38c);
    func_0205d0bc(self + 0x389);
    func_0205f770(self + 0x388);
    func_02054b64(self + 0x234);
    func_020b7ed8(self + 0x214);
    func_02089bbc(self + 0x1c4);
    func_02089bbc(self + 0x174);
    func_02066994(self + 0xec);
    func_0203f080(self);
    return self;
}
