/* func_02083178 @ 0x02083178, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083c30(void *p, unsigned int n);
extern unsigned char *func_020831c0(void);
extern void func_02083260(unsigned char *data);

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_02083178;

void func_02083178(UnkStruct_02083178 *p, unsigned int n)
{
    func_02083c30(p, n);
    if (n < p->unk_04) {
        func_02083260(func_020831c0() + 8 + n * 0x6c);
    }
}
