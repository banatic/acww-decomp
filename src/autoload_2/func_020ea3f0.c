/* func_020ea3f0 @ 0x020ea3f0, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ea450(void *p, unsigned int unused1, unsigned int unused2, unsigned int unused3);
extern int data_0213e608;

typedef struct {
    void *unk_00;
    char pad_04[16];
    unsigned int unk_14;
} UnkStruct_020ea3f0;

void *func_020ea3f0(UnkStruct_020ea3f0 *p, int a, int b, int c, unsigned int d)
{
    func_020ea450(p, a, b, c);
    p->unk_00 = (void *) &data_0213e608;
    p->unk_14 = d;
    return p;
}
