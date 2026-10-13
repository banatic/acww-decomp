/* func_ov100_0229d824 @ 0x0229d824, 0x8c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov002_02208098(unsigned char *, int);
int func_ov100_0229d42c(unsigned char *, int);
int func_ov100_0229d3d8(unsigned char *, int);
void func_ov002_02207cf8(unsigned char *);
int func_ov100_0229d194(unsigned char *, int);
void func_ov100_0229c2a0(unsigned char *, int);
void func_ov100_0229c2b0(unsigned char *, int);
void func_ov094_022999cc(void);

void func_ov100_0229d824(unsigned char *base, int param)
{
    unsigned char g1, g2;
    int val1, val2;

    base[0x291e] = (unsigned char) param;
    func_ov002_02208098(base, 1);
    g1 = data_021f6c58;
    g2 = data_021f6c54;
    val1 = func_ov100_0229d42c(base, base[0x291e]) - g1;
    *(int *) (base + 0x28cc) = val1;
    val2 = func_ov100_0229d3d8(base, base[0x291e]) - g2;
    *(int *) (base + 0x28d0) = val2;
    base[0x291f] = (unsigned char) param;
    func_ov002_02207cf8(base + 0x218c);
    if (func_ov100_0229d194(base, param) != 0) {
        func_ov100_0229c2a0(base, 4);
    } else {
        func_ov100_0229c2b0(base, 4);
        func_ov094_022999cc();
    }
}
