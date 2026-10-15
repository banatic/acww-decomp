/* func_02001bf0 @ 0x02001bf0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001c30(int mode);
extern void GX_SetGraphicsMode(int, int, int);

void func_02001bf0(int arg0)
{
    int r4;
    int r0;
    int r1;
    int r2;

    r4 = arg0;
    func_02001c30(arg0);
    r0 = 1;
    r1 = r4;
    r2 = r0;
    GX_SetGraphicsMode(r0, r1, r2);
}
