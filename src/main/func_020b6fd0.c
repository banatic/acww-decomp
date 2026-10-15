/* func_020b6fd0 @ 0x020b6fd0, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54ac;
extern unsigned char data_020e54b0;
extern int data_021f69d0;
extern void *data_021f693c;
extern void *data_021c8ca0;
extern unsigned char data_021f692c;
extern int data_021f6944;
extern int data_020e55bc[];
extern int data_021f6948;

extern void func_02041a9c(void);
extern int func_020a6ee0(void);
extern void func_020a6ef0(int);
extern void func_0203f070(void);
extern int func_020b5e84(void *);
extern void func_020b7228(void);
extern int func_020b6590(void);
extern void func_020b7e84(void *);
extern void func_020b7130(void);
extern void func_020b71dc(int);

int func_020b6fd0(void)
{
    unsigned char c;
    int callResult;

    func_02041a9c();
    c = data_020e54ac;
    callResult = func_020a6ee0();

    if (c == 0x2e || c == 0xd || c == 0xc || c == 0xe || c == 0x2f) {
        if (callResult != 4) {
            func_020a6ef0(4);
        }
    }

    func_0203f070();
    data_020e54b0 = data_020e54ac;
    data_020e54ac = (unsigned char) func_020b5e84(&data_021f69d0);
    func_020b7228();
    data_021c8ca0 = &data_021f693c;
    func_020b7e84((void *) func_020b6590());
    data_021f692c = 0;
    data_021f6944 = data_020e54ac;
    func_020b7130();
    {
        int v = data_020e55bc[data_020e54ac];
        data_021f6948 = v;
        func_020b71dc(v);
    }
    return 1;
}
