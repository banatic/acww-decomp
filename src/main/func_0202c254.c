/* func_0202c254 @ 0x0202c254, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202c254 {
    char pad_00[0x1d];
    unsigned char flag : 1;
};

extern int func_0209dcac(int, int *, struct UnkStruct_0202c254 *);

extern unsigned char data_020c89f0[];

void *func_0202c254(int a, int *b, struct UnkStruct_0202c254 *c)
{
    *b = func_0209dcac(a, b, c);
    c->flag = 1;
    return (void *) data_020c89f0;
}
