/* func_02045df8 @ 0x02045df8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02045df8 {
    int m[4];
};
extern int func_02045cec(void *p, int a);
extern void func_02045db8(void *p);
extern struct UnkStruct_02045df8 data_021c7884[];

void func_02045df8(int *src, int a)
{
    int tmp[2];
    int r;

    tmp[0] = src[0];
    tmp[1] = src[1];
    r = func_02045cec(tmp, a);
    if (r >= 0) {
        func_02045db8(&data_021c7884[r]);
    }
}