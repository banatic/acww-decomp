/* func_0206ab84 @ 0x0206ab84, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8750(void *);

typedef struct {
    unsigned char pad_00[0x24];
    unsigned char *data;
    unsigned char pad_28[0x10];
    unsigned char something[0x16];
    unsigned char flag;
} UnkStruct_0206ab84;

void func_0206ab84(UnkStruct_0206ab84 *x)
{
    func_020a8750(x->something);
    x->flag = 1;
    x->data[0x1a49] = 1;
}
