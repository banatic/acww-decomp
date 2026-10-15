/* func_020aed38 @ 0x020aed38, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020aed38 {
    int unk_00;
    int unk_04;
};

extern int func_020aefd4(unsigned short *);
extern void func_020b0164(void *buffer, int *index, int a, int b, unsigned int count, int unused, unsigned char flag);

void func_020aed38(struct UnkStruct_020aed38 *a, int *b)
{
    int v;
    v = func_020aefd4((unsigned short *) a);
    func_020b0164(&a->unk_04, b, 0, 0, v, 0x25, 0);
}
