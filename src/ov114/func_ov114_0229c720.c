/* func_ov114_0229c720 @ 0x0229c720, 0xb0 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002708(unsigned char);
extern void func_02001a04(unsigned int, unsigned int, int);
extern void func_020019f4(unsigned char *, unsigned char);
extern void func_0200277c(unsigned char);
extern void func_ov114_0229c890(unsigned char *);
extern void func_ov114_0229ce18(unsigned char *, int, int);

void func_ov114_0229c720(unsigned char *obj)
{
    unsigned char v = obj[0x12ba];
    unsigned char x = obj[0x12b8];
    unsigned char y = obj[0x12b9];

    if (x == y) {
        if (x != 0xff && v != 0x10) {
            if (v < 0xc) {
                if (v == 0) {
                    func_02002708(obj[0x12b3]);
                }
                obj[0x12ba] += 4;
                func_02001a04(*(unsigned int *) (obj + 0x12a8), *(unsigned int *) (obj + 0x12a4), obj[0x12ba]);
            } else {
                func_020019f4(obj, obj[0x12b9]);
            }
        }
    } else {
        if (v == 0) {
            func_ov114_0229c890(obj);
        } else if (v > 4) {
            obj[0x12ba] = v - 4;
            func_02001a04(*(unsigned int *) (obj + 0x12a8), *(unsigned int *) (obj + 0x12a4), obj[0x12ba]);
        } else {
            obj[0x12ba] = 0;
            func_0200277c(obj[0x12b3]);
        }
    }

    if (v != obj[0x12ba]) {
        func_ov114_0229ce18(obj, obj[0x12ba], 0x10);
    }
}
