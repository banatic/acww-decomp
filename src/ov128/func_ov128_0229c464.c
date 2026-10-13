/* func_ov128_0229c464 @ 0x0229c464, 0x46 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f60(int);
extern void func_02001b6c(int);
extern void func_02001b7c(int);
extern void func_02002808(int, int, int, int, int);

void func_ov128_0229c464(int param)
{
    int u;
    int v;

    u = func_ov002_02207f60(param) - 64;
    if (u < 0) {
        u = 0;
    }

    v = func_ov002_02207f60(param) - 48;

    if (v > 0) {
        goto then;
    }
    func_02001b6c(2);
    goto end;
then:
    func_02001b7c(2);
    func_02002808(3, 0, u, 0xff, v);
end:;
}
