/* func_ov094_0229aaac @ 0x0229aaac, 0x50 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern void *func_02099734(void);
extern void *func_02098f48(void *, int);

unsigned short func_ov094_0229aaac(void *obj, int val)
{
    void *tmp;
    void **field;
    unsigned short *list;

    func_020984e8();
    tmp = func_02099734();

    if (val >= 0 && val <= 14) {
        list = (unsigned short *) func_02098f48(tmp, 0);
        return list[val];
    }

    if (val >= 15 && val <= 29) {
        field = (void **) ((char *) obj + 0xa34);
        if (*field != 0) {
            return ((unsigned short *) *field)[val - 15];
        }
    }
    return 0xfff1;
}
