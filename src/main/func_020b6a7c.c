/* func_020b6a7c @ 0x020b6a7c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02030dcc(void);
extern void func_0208a0a0(void);
extern unsigned char data_021c75b8;
extern unsigned char data_021c75b0;
extern int data_021f69d0;
extern void *func_020b5e84(void *);
extern int func_020b64c0(void *);
extern void *func_020b5e10(void);
extern int SBServerGetState(void *);
extern int SBServerGetFlags(void *);
extern void func_020b5e44(int, int);

int func_020b6a7c(int a0)
{
    unsigned int ok;
    int st;

    func_02030dcc();
    func_0208a0a0();
    if (data_021c75b8 == 2) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok == 0) {
        if (data_021c75b0 == 0) {
            return 1;
        }
    }
    if (func_020b64c0(func_020b5e84(&data_021f69d0)) != 0) {
        st = SBServerGetState(func_020b5e10());
        func_020b5e44(st, SBServerGetFlags(func_020b5e10()));
    }
    return 1;
}
