/* func_0207122c @ 0x0207122c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209f150(void *, int);
extern int func_02070fa0(void *);
extern void func_0209e474(void *);
extern int func_02071188(void *);
extern void func_0209f128(void *, int);
extern unsigned char data_021dc7a8;

void func_0207122c(unsigned char *param)
{
    unsigned char local[8];
    if (func_0209f150(&data_021dc7a8, 3) != 0) {
        return;
    }
    if (func_02070fa0(param) == 0) {
        return;
    }
    *((unsigned int *) local) = 0;
    *((unsigned int *) local + 1) = 0;
    func_0209e474(local);
    if ((param[0x62] == local[5]) && (param[0x61] == local[4])) {
        if (param[0x60] == local[3]) {
            return;
        }
    }
    if (func_02071188(param) == 0) {
        return;
    }
    func_0209f128(&data_021dc7a8, 3);
}
