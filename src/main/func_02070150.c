/* func_02070150 @ 0x02070150, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020df328[2];
extern unsigned short data_020df590[];
struct s_02070150 {
    char pad_00[8];
    void *unk_08;
};
extern struct s_02070150 *data_021cfca0;
extern void *data_021cfc84;
void func_0206f5b0(void);
int func_0202f134(unsigned short, void *, unsigned char, int);

int func_02070150(void)
{
    unsigned char b;
    void *r4;
    if (data_020df328[0] != 3) {
        return 0;
    }
    if (data_021cfca0 != 0) {
        r4 = data_021cfca0->unk_08;
    } else {
        r4 = data_021cfc84;
    }
    func_0206f5b0();
    b = data_020df328[1];
    if (func_0202f134(data_020df590[b], r4, b, 4) == 0) {
        return 0;
    }
    data_020df328[0] = 1;
    return 1;
}
