/* func_020a7394 @ 0x020a7394, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021f4320[];
extern int data_020ccf94;
extern void func_020a7738(char *base, unsigned char *p0, unsigned char *p1, unsigned char *p2);
extern void func_020a774c(char *base, unsigned char v0, unsigned char v1, unsigned char v2);
extern void func_02073598(int value);

void func_020a7394(int a, int b, int c, int d, int mask)
{
    unsigned char local[3];
    char *base;

    base = data_021f4320 + 3 * a;
    func_020a7738(base, &local[0], &local[1], &local[2]);
    if ((mask & 1) != 0) {
        local[0] = (unsigned char) b;
    }
    if ((mask & 2) != 0) {
        local[1] = (unsigned char) c;
    }
    if ((mask & 4) != 0) {
        local[2] = (unsigned char) d;
    }
    func_020a774c(base, local[0], local[1], local[2]);
    func_02073598(data_020ccf94);
}
