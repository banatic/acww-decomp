/* func_ov094_0229a038 @ 0x0229a038, 0x22 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229a018(void *);
extern void func_ov094_02299ff8(void *);
extern void func_02004644(int, int);

void func_ov094_0229a038(void *p)
{
    func_ov094_0229a018(p);
    func_ov094_02299ff8(p);
    if (*(unsigned char *) ((char *) p + 0x13) != 0) {
        func_02004644(0x2d, 1);
    }
}
