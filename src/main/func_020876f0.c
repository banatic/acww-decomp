/* func_020876f0 @ 0x020876f0, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020876f0 {
    char pad_00[10];
    char arr[32];
};

extern int func_020644cc(int);
extern void func_020877ac(struct UnkStruct_020876f0 *, int, int);
extern char func_02087784(struct UnkStruct_020876f0 *);
extern char func_020877dc(struct UnkStruct_020876f0 *, int, int);

void func_020876f0(struct UnkStruct_020876f0 *p)
{
    int v = func_020644cc(6) + 7;
    func_020877ac(p, 2, v - 3);
    p->arr[v - 3] = func_02087784(p);
    p->arr[v - 2] = func_02087784(p);
    p->arr[v] = func_020877dc(p, 0x1b33, 0x4f6);
    p->arr[v - 1] = func_020877dc(p, 0x168f, 0x4a4);
    p->arr[v + 1] = func_020877dc(p, 0x168f, 0x4a4);
    func_020877ac(p, v + 2, 14);
}
