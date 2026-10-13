/* func_ov103_0229d318 @ 0x0229d318, 0x4c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(const unsigned char *);
extern void func_ov002_02208098(unsigned char *, int);
void func_ov103_0229cbac(unsigned char *, int);
void func_ov103_0229dd60(unsigned char *);
void func_ov103_0229c994(unsigned char *);

void func_ov103_0229d318(unsigned char *p)
{
    if (func_ov002_02209f64(p + 0x2274) == 0) {
        func_ov002_02208098(p, p[0x2da7]);
        if (p[0x2da7] == 5) {
            func_ov103_0229cbac(p, p[0x2da4]);
        }
        func_ov103_0229dd60(p);
    }
    func_ov103_0229c994(p);
}
