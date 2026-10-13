/* func_0204dea0 @ 0x0204dea0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c80e0[5];
extern void func_0205c10c(void *self);
extern void *func_020e9948(void *self, int n);
extern void func_0204df54(void *p);
extern int func_0204dcb8(void *p, int i, void *self);
extern void func_0204de5c(void *self);

int func_0204dea0(void *self)
{
    int i;
    int ok;

    ok = 1;
    func_0205c10c(self);
    for (i = 0; i < 5; i++) {
        if (data_021c80e0[i] == 0) {
            data_021c80e0[i] = func_020e9948(self, 0x20);
            // Shared failure block, placed after the f3 test.
            if (data_021c80e0[i] == 0) {
                goto fail;
            }
            if (data_021c80e0[i] != 0) {
                func_0204df54(data_021c80e0[i]);
            }
            if (func_0204dcb8(data_021c80e0[i], i, self) == 0) {
                ok = 0;
                break;
            }
        }
        continue;
    fail:
        ok = 0;
        break;
    }
    if (ok == 0) {
        func_0204de5c(self);
    }
    return ok;
}
