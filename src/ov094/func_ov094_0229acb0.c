/* func_ov094_0229acb0 @ 0x0229acb0, 0x34 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_02299a90(unsigned short x);
extern int func_0204c6b8(void *p);

int func_ov094_0229acb0(int arg0, void *p, int sel)
{
    switch (sel) {
        case 1:
            return 0xb3;
        case 2:
            if (func_ov094_02299a90(*(unsigned short *) p) != 0) {
                return func_0204c6b8(p);
            } else {
                return 0xb4;
            }
        default:
            return func_0204c6b8(p);
    }
}
