/* func_0200b83c @ 0x0200b83c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0200b83c;

extern void func_0200e92c(UnkStruct_0200b83c *);
extern void func_0200e90c(UnkStruct_0200b83c *, int, int, short);
extern void func_0200e91c(UnkStruct_0200b83c *);
extern int func_0200e894(void *, UnkStruct_0200b83c *);
extern void func_0200b894(int *, int *, int, int, int);

int func_0200b83c(void *arg0, int *arg1, int arg2, int arg3, int arg4, short arg5)
{
    int a2 = arg2;
    int pair[2];
    UnkStruct_0200b83c obj;
    int out[4];

    func_0200e92c(&obj);
    func_0200e90c(&obj, 25, arg4, arg5);
    pair[0] = arg1[0];
    pair[1] = arg1[1];
    func_0200b894(out, pair, a2, 0xfff1, arg3);
    {
        int result = func_0200e894(arg0, &obj);
        func_0200e91c(&obj);
        return result;
    }
}
