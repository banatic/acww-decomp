/* func_ov123_0229a2f8 @ 0x0229a2f8, 0x48 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov123_0229c9c4[];
extern unsigned char data_ov123_0229c9a4[];
extern unsigned char data_ov123_0229c9b4[];
extern void func_0206fdd4(char *p, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4, unsigned int v5);
extern void func_ov123_02299640(char *a, int x);

void func_ov123_0229a2f8(char *a, unsigned int b, unsigned int c)
{
    if (b > 12) {
        return;
    }
    func_0206fdd4(a + 0x230, data_ov123_0229c9a4[b], data_ov123_0229c9c4[b], data_ov123_0229c9b4[b],
                  data_ov123_0229c9c4[b] + 2, c);
    func_ov123_02299640(a, 16);
}
