/* func_ov115_0229de2c @ 0x0229de2c, 0x34 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a05c(unsigned char *p, int a, int b, int c, int d);
extern void func_ov002_02208098(unsigned char *p, int a);

void func_ov115_0229de2c(unsigned char *obj, int arg1, int arg2)
{
    func_ov002_0220a05c(&obj[0x94], arg1, arg2, 3, 1);
    obj[0x142c] = obj[0x8d];
    func_ov002_02208098(obj, 3);
}
