/* __sinit_020c74c4 @ 0x020c74c4, 0x74 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5c20(void *);
extern void *FX_Div();
extern struct {
    long f0;
} data_021fd23c;
extern struct {
    long f0;
} data_021fd244;
extern struct {
    long f0;
} data_021fd240;
extern unsigned char data_021fd248;

void __sinit_020c74c4(void)
{
    void *_r1;
    void *_r2;
    void *_r3;
    func_020f5c20((void *) &data_021fd248);
    _r1 = FX_Div(520192, 2458);
    data_021fd23c.f0 = (long) _r1;
    _r2 = FX_Div(520192, 1638, (void *) &data_021fd23c);
    data_021fd244.f0 = (long) _r2;
    _r3 = FX_Div(520192, 819, (void *) &data_021fd244);
    data_021fd240.f0 = (long) _r3;
}
