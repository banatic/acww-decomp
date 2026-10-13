/* func_ov003_02225ebc @ 0x02225ebc, 0xac bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223cf74;
extern void *data_ov003_0223cf78;
extern void *data_ov003_0223cf70;
extern void *data_021fbe94;
extern char data_ov003_0223dcb4[];
extern char data_ov003_0225f0b4[];
extern int data_ov003_0223cfa0[];
extern int data_ov003_0223cfe4[];

extern void *func_020ea298(void *p, int n);
extern void *GX_ResetBankForSubOBJExtPltt(int a, void *h);
extern int func_ov003_0222726c(char *self);
extern int func_ov003_02225f68(char *self);
extern void func_ov003_02223a90(void *p);
extern void func_ov003_02223c58(int *p);
extern void func_ov003_02221a38(int *p);
extern void func_020467ac(void);

int func_ov003_02225ebc(char *self)
{
    int ok = 0;
    if (data_ov003_0223cf74 == 0) {
        data_ov003_0223cf74 = func_020ea298(data_ov003_0223dcb4, data_ov003_0225f0b4 - data_ov003_0223dcb4);
    }
    if (data_ov003_0223cf78 == 0) {
        data_ov003_0223cf78 = GX_ResetBankForSubOBJExtPltt(0x8c00, data_021fbe94);
    }
    if (func_ov003_0222726c(self)) {
        data_ov003_0223cf70 = self;
        if (func_ov003_02225f68(self)) {
            *(int *) (self + 0x6a6c) = 0;
            func_ov003_02223a90(self + 0x4b20);
            func_ov003_02223c58(data_ov003_0223cfa0);
            func_ov003_02221a38(data_ov003_0223cfe4);
            func_020467ac();
            ok = 1;
        } else {
            data_ov003_0223cf70 = 0;
        }
    }
    return ok;
}
