/* func_0203b5bc @ 0x0203b5bc, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_021f6948;
extern void func_ov004_02247438(unsigned int, int);
extern void func_ov003_02236564(unsigned int);
extern void func_0203be6c(unsigned int);
extern void func_01ffcbb0(void *, unsigned int);
extern unsigned int func_0203c57c(unsigned int);
extern unsigned int func_0203c568(unsigned int);
extern unsigned int func_0203c548(unsigned int);
extern void func_0203bd84(unsigned int, char *, unsigned int, unsigned int, unsigned int);

void func_0203b5bc(unsigned int arg)
{
    char buffer[12];
    unsigned int v1, v2, v3;
    if (data_021f6948[4] == 0) {
        func_ov004_02247438(arg, 0);
    } else {
        func_ov003_02236564(arg);
    }
    func_0203be6c(arg);
    func_01ffcbb0(buffer, arg);
    v1 = func_0203c57c(arg);
    v2 = func_0203c568(arg);
    v3 = func_0203c548(arg);
    func_0203bd84(arg, buffer, v1, v2, v3);
}
