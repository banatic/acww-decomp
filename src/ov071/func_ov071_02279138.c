/* func_ov071_02279138 @ 0x02279138, 0x54 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int a;
    int b;
};

extern struct Pair data_ov071_0227a364[2];
extern struct Pair data_ov071_0227a170;
extern struct Pair data_ov071_0227a130;
extern int data_ov071_0227a344;

void func_ov071_02279138(int arg0, struct Pair *out, int index)
{
    if ((data_ov071_0227a344 & 1) == 0) {
        data_ov071_0227a364[0] = data_ov071_0227a170;
        data_ov071_0227a364[1] = data_ov071_0227a130;
        data_ov071_0227a344 |= 1;
    }
    *out = data_ov071_0227a364[index];
}
