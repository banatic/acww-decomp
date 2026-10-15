/* func_ov143_02299a9c @ 0x02299a9c, 0x38 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_ov002_02208098(int, unsigned char value);
extern void func_ov002_02207e9c(int, int, int);
extern void func_ov002_02208090(int, int);
extern void func_ov143_02299b70(int, int);
extern void func_ov143_02299664(int);

void func_ov143_02299a9c(int r0)
{
    int r4 = r0;
    *(unsigned char *) (r4 + 0xa4) = 0x10;
    func_ov002_02208098(r4, 9);
    func_ov002_02207e9c(r4, 0, 0);
    func_ov002_02208090(r4, 6);
    func_ov143_02299b70(r4, 5);
    func_ov143_02299664(r4);
}
