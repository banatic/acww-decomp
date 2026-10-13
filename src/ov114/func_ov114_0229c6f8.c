/* func_ov114_0229c6f8 @ 0x0229c6f8, 0x28 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov114_0229ccc0(unsigned char *obj, unsigned char val);

void func_ov114_0229c6f8(unsigned char *obj, unsigned char val)
{
    obj[0x12b9] = val;
    if (obj[0x12b9] != obj[0x12b8]) {
        func_ov114_0229ccc0(obj, val);
    }
}
