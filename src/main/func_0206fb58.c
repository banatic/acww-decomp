/* func_0206fb58 @ 0x0206fb58, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern void *func_02099734(void);
extern unsigned short *func_02098f48(void *p, int i);
extern unsigned char func_02098e8c(void *p, int i);
extern unsigned short data_021cfce8[16];
extern unsigned char data_021cfcd8[16];

void func_0206fb58(void)
{
    void *obj;
    int i;
    func_020984e8();
    obj = func_02099734();
    i = 0;
    while (i < 15) {
        data_021cfce8[i] = *func_02098f48(obj, i);
        data_021cfcd8[i] = func_02098e8c(obj, i);
        i++;
    }
}
