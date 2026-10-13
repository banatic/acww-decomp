/* func_ov100_0229dad0 @ 0x0229dad0, 0x48 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229cd10(int, unsigned char);
extern int func_ov100_0229c2b0(int, int);
extern int func_ov100_0229cecc(int);
extern int func_ov002_02209f70(int);
extern int func_ov002_02208098(int, int);

void func_ov100_0229dad0(int arg0)
{
    if (func_ov002_02209f70(arg0 + 0x2274) == 0) {
        func_ov100_0229cd10(arg0, *(unsigned char *) (arg0 + 0x2923));
        func_ov100_0229c2b0(arg0, 0x40);
        func_ov002_02208098(arg0, 0xf);
        func_ov100_0229cecc(arg0);
    } else {
        func_ov002_02208098(arg0, 4);
    }
}
