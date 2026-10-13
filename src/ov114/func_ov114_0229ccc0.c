/* func_ov114_0229ccc0 @ 0x0229ccc0, 0xb0 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_02062fbc(void *);
extern void func_020a8c1c(void *);
extern void func_02062ea4(void *, void *);
extern void func_02062f4c(void *);
extern int func_ov114_0229cd70(void *);
extern void func_020a8bb8(int, void *);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);

void func_ov114_0229ccc0(unsigned char *self, unsigned short param)
{
    unsigned short val;
    unsigned short v;
    unsigned int obj[0xb];
    int b;
    int x;

    func_02062fbc(obj);
    if (param == 0xff) {
        func_020a8c1c(obj);
    } else {
        b = self[0x12b7];
        switch (b) {
            case 0:
                if (param < 0x38) {
                    v = (unsigned short) (param + 0x12e8);
                } else {
                    v = 0x12e8;
                }
                break;
            case 1:
                if (param < 0x38) {
                    v = (unsigned short) (param + 0x12b0);
                } else {
                    v = 0x12b0;
                }
                break;
            default:
                func_02062f4c(obj);
                return;
        }
        val = v;
        func_02062ea4(obj, &val);
    }

    x = func_ov114_0229cd70(self);
    func_020a8bb8(x, obj);
    func_02070adc(x, self[0x12b1], 0xa1, 0x0d, 1, 3, 0);
    func_02070a04(x, 1, 0);
    func_02062f4c(obj);
}
