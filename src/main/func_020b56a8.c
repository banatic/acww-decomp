/* func_020b56a8 @ 0x020b56a8, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205cacc(int, int);
extern int func_0209fb28(void *);
extern void func_020a01d4(int);
extern void func_020a16b0(void);
extern void func_0209ef7c(void *);
extern void func_02098540(void);
extern void func_020792c8(void);
extern void func_0209e6ec(void *, int);
extern void func_0209e604(void *);
extern void func_020792b4(void);
extern void func_0205cab0(void);
extern char data_021f3ba0[];
extern char data_021dc7a8[];

void func_020b56a8(int param)
{
    int r4 = param;
    int r0;
    int r1;

    func_0205cacc(0x5000, 0);
    r0 = r4;
    r0 += 0x5e;
    r0 = *(unsigned char *) r0;
    if (r0 == 4 || r0 == 1) {
        if (r0 == 4) {
            if (func_0209fb28(data_021f3ba0) == 0) {
                func_020a01d4(1);
            }
        }
        r4 += 0x5e;
        r0 = *(unsigned char *) r4;
        if (r0 == 4) {
            func_020a16b0();
        }
        func_0209ef7c(data_021dc7a8);
        func_02098540();
        func_020792c8();
        func_0209e6ec(data_021dc7a8, 3);
    } else {
        func_0209e6ec(data_021dc7a8, 4);
    }
    func_0209e604(data_021dc7a8);
    func_020792b4();
    func_0205cab0();
}
