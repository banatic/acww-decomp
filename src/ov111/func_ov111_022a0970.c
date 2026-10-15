/* func_ov111_022a0970 @ 0x022a0970, 0x68 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern const char data_ov111_022a1068[];
extern const char data_ov111_022a0f88[];
extern const char data_ov111_022a1080[];
extern void *data_021fbe94;
extern int func_02002d14(const void *, void *, int, int, int, int);
extern int func_02002c6c(const void *, void *, int, int, int, int);
extern int func_ov095_0229c000(void *, const void *);
extern void func_ov111_0229efec(void *);
extern void func_ov095_0229bfd8(void *, int);

void func_ov111_022a0970(char *self)
{
    void *w = data_021fbe94;
    func_02002d14(data_ov111_022a1068, w, 6, 1, 1, 9);
    func_ov095_0229c000((void *) (self + 0xac), data_ov111_022a0f88);
    func_ov111_0229efec(self);
    self += 0xac;
    func_ov095_0229bfd8(self, 6);
    func_02002c6c(data_ov111_022a1080, w, 6, 0x13d, 0x13d, 0x1e9);
}
