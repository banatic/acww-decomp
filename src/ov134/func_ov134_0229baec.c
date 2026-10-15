/* func_ov134_0229baec @ 0x0229baec, 0xd0 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern void *data_ov134_0229c05c[];
extern void *data_ov134_0229c02c[];
extern unsigned char data_ov134_0229c44c[];
extern unsigned char data_ov134_0229c464[];
extern unsigned char data_ov134_0229c47c[];
extern unsigned char data_ov134_0229c490[];
extern unsigned char data_ov134_0229c4ac[];

extern int func_02002c6c(void *a, void *b, int c, int d, int e, int f);
extern int func_02002d14(void *a, void *b, int c, int d, int e, int f);
extern int func_02002ca4(void *a, void *b, int c);
extern int func_02064af4(void *a, void *b, int c);
extern void func_ov134_0229a8e8(void *self);

int func_ov134_0229baec(unsigned char *self)
{
    void *p = data_021fbe94;

    func_02002c6c(data_ov134_0229c44c, p, self[0xa2], 0x10, 0x10, 0x80);
    func_02002d14(data_ov134_0229c464, p, self[0xa2], 1, 1, 0xa);
    func_02002d14(data_ov134_0229c05c[self[0xa0]], p, self[0xa2], 1, 1, 2);
    func_02002ca4(data_ov134_0229c47c, p, self[0xa2]);
    func_02064af4(data_ov134_0229c02c[self[0xa0]], self + 0x870, 0x800);
    func_ov134_0229a8e8(self);
    func_02064af4(data_ov134_0229c490, self + 0x1070, 0x800);
    return func_02064af4(data_ov134_0229c4ac, self + 0x2870, 0x20);
}
