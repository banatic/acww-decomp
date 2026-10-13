/* func_020784f8 @ 0x020784f8, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *p);
extern int func_0207f294(int a);
extern int func_0207cf74(int x);
extern void func_02078540(int a, int b, int c, int d, unsigned char e);

extern unsigned char data_020ccf94[];

void func_020784f8(int a, int b, int c, int d, unsigned char e)
{
    if (func_02073d90(*(void **) data_020ccf94) == 0) {
        return;
    }
    a = func_0207f294(a);
    if (func_0207cf74(a) == 0) {
        return;
    }
    func_02078540(a, b, c, d, e);
}
