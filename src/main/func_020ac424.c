/* func_020ac424 @ 0x020ac424, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(unsigned int a, unsigned int b);
extern void func_02113088(unsigned int a, unsigned int b, unsigned int c);

typedef struct {
    unsigned int pad_00;
    unsigned int data;
} UnkStruct_020ac424;

void func_020ac424(UnkStruct_020ac424 *p)
{
    DC_FlushRange(p->data, 0x800);
    func_02113088(p->data, 0, 0x800);
}
