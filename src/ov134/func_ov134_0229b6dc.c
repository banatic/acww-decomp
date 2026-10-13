/* func_ov134_0229b6dc @ 0x0229b6dc, 0x48 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229b5ac(unsigned char *p, int a, int b, int c, int d, int e, int f);

void func_ov134_0229b6dc(unsigned char *p)
{
    int r3 = 3;
    int val = p[0xad];
    int idx = p[0xa5];
    switch (idx) {
        case 0:
            r3 = 5;
            val += 0x7d0;
            break;
        case 1:
        case 2:
            val += 1;
            break;
        default:
            break;
    }
    func_ov134_0229b5ac(p, 8, 0xcb, r3, val, 0xf, 0);
}
