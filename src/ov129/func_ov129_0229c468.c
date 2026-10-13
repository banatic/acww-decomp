/* func_ov129_0229c468 @ 0x0229c468, 0x50 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov129_0229b7ec(void *p, int a);
extern int func_ov002_0220a768(void *p, int a);
extern const unsigned char data_ov129_0229db40[];

int func_ov129_0229c468(void *p)
{
    unsigned char b;
    if (func_ov129_0229b7ec(p, 2)) {
        return *(int *) ((char *) p + 0x94);
    }
    b = *((unsigned char *) p + 0xae);
    switch (b) {
        case 4:
            return func_ov002_0220a768((char *) p + 0x1d4, 6);
        case 5:
            return func_ov002_0220a768((char *) p + 0x1d4, 5);
        default:
            return data_ov129_0229db40[b];
    }
}
