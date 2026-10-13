/* func_020f4338 @ 0x020f4338, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fd1bc;
extern void func_020f1ecc(void *);
extern void func_020f1d84(void *, int);

void func_020f4338(unsigned char *p, unsigned int code)
{
    int v;
    switch (code) {
        case 0:
        case 4:
            v = 0x85;
            break;
        case 1:
        case 3:
            v = 0x86;
            break;
        case 2:
            v = 0x87;
            break;
        default:
            break;
    }
    func_020f1ecc(&data_021fd1bc);
    func_020f1d84(&data_021fd1bc, v);
    p[6] = 1;
}
