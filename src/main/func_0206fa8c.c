/* func_0206fa8c @ 0x0206fa8c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfd08[15];
extern void func_0206fa58(unsigned short a, unsigned short b);
extern void func_0206fb14(void);

void func_0206fa8c(int param)
{
    if (param != 0) {
        int i;
        int negOne = -1;
        for (i = 0; i < 15; i++) {
            unsigned short val = data_021cfd08[i];
            int idx;
            if ((unsigned int) val >= 0x38e4u && (unsigned int) val <= 0x3933u) {
                idx = ((int) val - 0x38e4) >> 2;
            } else {
                idx = negOne;
            }
            if (idx >= 0) {
                int arg;
                if ((unsigned int) idx < 20u) {
                    arg = 0x3934 + idx * 4;
                } else {
                    arg = 0x3934;
                }
                func_0206fa58(val, (unsigned short) arg);
            }
        }
    }
    func_0206fb14();
}
