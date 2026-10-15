/* func_0207f454 @ 0x0207f454, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct _S {
    char pad_00[0x64];
    int unk_64;
};
extern struct _S *data_020ccf94;
extern int func_02073dd4(struct _S *a, int b);
extern void *func_0208150c(void *a);
extern int func_02003704(void *a);
extern char *func_0207dfd4(void *a, int b);
extern int func_0207f76c(void *a, char *b);
extern void func_0207dfec(void *a);
extern void *func_0207f294(void *a);
extern int func_02052fdc(void *a);
extern void *func_0207f1c8(void *a);
extern void *func_0209b5e8(void *a);
extern void func_0209b998(void *object);

void func_0207f454(void *self)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }
    if (func_02003704(func_0208150c(self)) == 0) {
        return;
    }
    {
        char *p = func_0207dfd4(self, 0);
        int flag = 0;
        int i;
        for (i = 0; i < 4; i++) {
            if (func_0207f76c(self, p) != 0) {
                flag = 1;
            }
            p += 2;
        }
        func_0207dfec(self);
        if (flag) {
            func_02052fdc(func_0207f294(self));
        }
        func_0209b998(func_0209b5e8(func_0207f1c8(self)));
    }
}
