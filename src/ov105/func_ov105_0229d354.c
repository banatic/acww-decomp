/* func_ov105_0229d354 @ 0x0229d354, 0x3c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229d76c(int arg0, unsigned int arg1);
extern int func_ov105_0229d75c(int, int);
extern int func_ov105_0229d718(int, int);
extern void func_ov094_0229b938(int, int);

void func_ov105_0229d354(int r4, int r5)
{
    if (func_ov105_0229d76c(r4, r5) == 0) {
        if (func_ov105_0229d75c(r4, r5) == 0) {
            return;
        }
    }
    func_ov094_0229b938(r4 + 0xd5c, func_ov105_0229d718(r4, r5));
}
