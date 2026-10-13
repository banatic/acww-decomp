/* func_02040adc @ 0x02040adc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f39c8[4];
extern void func_02040b6c(void *out, void *p0);

void func_02040adc(void *p0, int flag)
{
    int local[2];
    unsigned char *base = data_021f39c8;
    if (flag == 0) {
        base[0] = 1;
        base[1] = 1;
        base[2] = 0;
        base[3] = 0;
        return;
    }
    local[0] = 0;
    local[1] = 0;
    func_02040b6c(local, p0);
    base[0] = ((unsigned char *) local)[3];
    base[1] = ((unsigned char *) local)[4];
    base[2] = ((unsigned char *) local)[5];
}
