/* func_0208eea0 @ 0x0208eea0, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a1d0(void *ptr);
extern int func_0208aef0(void *obj);
extern int func_0208a1b0(void *ptr, int arg);
extern int func_0208aeec(void *obj);
extern int func_0208a198(void *ptr, int arg);
extern void func_02088df8(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);

typedef struct {
    int pad_00;
} UnkStruct_0208eea0;

struct UnkStruct_0208eea0_2 {
    unsigned char pad_00[0x0c];
    UnkStruct_0208eea0 sub;
    unsigned char pad_10[0x10];
    int flag;
};

void func_0208eea0(struct UnkStruct_0208eea0_2 *obj)
{
    int v7, v4, v6, sum;
    UnkStruct_0208eea0 *sub;

    if (obj->flag == 0) {
        return;
    }

    v7 = func_0208a1d0(&obj->sub);
    v4 = func_0208aef0(obj);
    v4 += func_0208a1b0(&obj->sub, -1);
    v6 = func_0208aeec(obj);
    sub = &obj->sub;
    sum = v6 + func_0208a198(sub, -1);
    func_02088df8(0, v7, v4, sum, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
