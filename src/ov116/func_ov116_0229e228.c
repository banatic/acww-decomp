/* func_ov116_0229e228 @ 0x0229e228, 0x88 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02208054(char *self, int a);
extern void func_ov116_0229df8c(char *self);
extern int func_ov114_0229d564(char *p, unsigned char a, unsigned char b);
extern int func_ov114_0229d3f4(char *p, unsigned char a, unsigned char b);
extern int func_ov114_0229ca50(char *p, unsigned char a, unsigned char b);
extern unsigned char *func_ov002_02208098(char *self, unsigned char value);
void func_ov116_0229e228(char *self)
{
    unsigned int cond;
    unsigned char b;
    unsigned char c;
    if (func_ov002_02208054(self, 1)) {
        func_ov116_0229df8c(self);
        return;
    }
    cond = ((data_021fbdd8 != 0) && (data_021fbddc != 0)) ? (1) : (0);
    if (cond > 0) {
        if (b) {
            b = data_021f6c58;
            c = data_021f6c54;
        } else {
            b = data_021f6c58;
            c = data_021f6c54;
        }
        if (func_ov114_0229d564(self + 0xf8, b, c) == 0) {
            if (func_ov114_0229d3f4(self + 0xf8, b, c) != 0) {
                func_ov002_02208098(self, 1);
                return;
            }
            self = self + (0xf8 & 0xFFFFFFFFFFFFFFFF);
            if (func_ov114_0229ca50(self, b, c)) {
                return;
            }
        }
    }
}
