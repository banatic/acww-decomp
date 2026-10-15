/* func_ov105_0229e9d0 @ 0x0229e9d0, 0x54 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern char data_ov105_0229fb30;
extern char data_ov105_0229fb50;
extern char data_ov105_0229fb74;
extern int func_02002d14(void *, void *, int, int, int, int);
extern int func_02002ca4(void *, void *, int);
extern int func_02002c6c(void *, void *, int, int, int, int);

void func_ov105_0229e9d0(void *receiver)
{
    void *v;
    v = data_021fbe94;
    func_02002d14((void *) &data_ov105_0229fb30, v, 4, 4, 4, 4);
    func_02002ca4((void *) &data_ov105_0229fb50, v, 4);
    func_02002c6c((void *) &data_ov105_0229fb74, v, 4, 0x1e2, 0x1e2, 0x227);
}
