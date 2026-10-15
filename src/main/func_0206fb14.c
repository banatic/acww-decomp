/* func_0206fb14 @ 0x0206fb14, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099734(int);
extern void func_0209a088(unsigned short *p, unsigned char c, int i);
extern unsigned short data_021cfce8[];
extern unsigned char data_021cfcd8[];

void func_0206fb14(void)
{
    unsigned short local;
    int i;
    func_02099734((int) func_020984e8());
    local = 0xfff1;
    for (i = 0; i < 15; i++) {
        local = data_021cfce8[i];
        func_0209a088(&local, data_021cfcd8[i], i);
    }
}
