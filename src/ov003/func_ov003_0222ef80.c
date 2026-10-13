/* func_ov003_0222ef80 @ 0x0222ef80, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ea990(void *p, int *blk);

int func_ov003_0222ef80(int a, unsigned char *obj, int idx, int c, int e)
{
    int v = (signed char) obj[0x24d];
    int blk[3];

    if (c == 0) {
        return 0;
    }
    if (v < 0 || v != idx) {
        return 1;
    }
    blk[0] = c;
    blk[1] = 0;
    blk[2] = e;
    func_020ea990(obj + 0x204, blk);
    return 0;
}
