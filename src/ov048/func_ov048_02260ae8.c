/* func_ov048_02260ae8 @ 0x02260ae8, 0x64 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_02074150(void);
extern void func_02074120(void);
extern void func_ov048_02262378(void *self);
extern void func_ov048_022616b8(void *self, int n);
extern void func_ov048_022635f4(void *p, int n);
extern void func_020a6f10(int n);
extern void func_020a6ef0(int n);
extern void func_0206844c(void *obj, char *cmd, void *data);
extern void *data_ov048_02263d20;

void func_ov048_02260ae8(void *self)
{
    char *obj;
    int ret;
    char local;

    obj = *(char **) ((char *) self + 0x40);
    ret = func_02074150();
    if ((unsigned) (ret - 5) > 1) {
        return;
    }
    func_ov048_02262378(self);
    func_ov048_022616b8(self, 0);
    if (ret == 5) {
        *(unsigned int *) (obj + 0x14) = 0;
        func_ov048_022635f4(*(void **) ((char *) self + 0xb8), 13);
        func_020a6f10(1);
        func_020a6ef0(1);
    } else {
        local = 12;
        func_0206844c(obj, &local, data_ov048_02263d20);
    }
    func_02074120();
}
