/* func_020b87ac @ 0x020b87ac, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b8854(void *self);
extern void func_020b8a3c(void *self);
extern void func_020b88f0(void *self, int);
extern void func_020b88d8(void *self);
extern int func_0208a9c8(void *self);
extern void func_020b86d0(void *self);
extern int func_020b8878(void *self);
extern void func_020b8a4c(void *self);
extern void func_020b89cc(void *self);
extern void func_020b9068(void *self, int);
extern void func_020b873c(void *self);
extern void func_020b8a5c(void *self);
extern void func_020b8a10(void *self);
extern void func_020b87a4(void *self);

void func_020b87ac(void *self)
{
    if (func_020b8854(self)) {
        func_020b8a3c(self);
        func_020b88f0(self, 1);
        func_020b88d8(self);
        if (func_0208a9c8((char *) self + 8)) {
            func_020b86d0(self);
        }
    } else {
        if (func_020b8878(self)) {
            func_020b8a4c(self);
            func_020b89cc(self);
            func_020b9068((char *) self + 8, 0);
            if (func_0208a9c8((char *) self + 8)) {
                func_020b873c(self);
            }
        } else {
            if (*(int *) ((char *) self + 0xf4) != 0) {
                func_020b8a5c(self);
                func_020b8a10(self);
                func_020b9068((char *) self + 8, 0);
                if (func_0208a9c8((char *) self + 8)) {
                    func_020b87a4(self);
                }
            }
        }
    }
}
