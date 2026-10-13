/* func_0200c5e0 @ 0x0200c5e0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020103c0(void *base, unsigned short *local);
typedef struct {
    unsigned short unk_00;
    unsigned char pad_02[10];
    unsigned char unk_0C;
} UnkStruct_0200c5e0;
void func_0200c5e0(void *base)
{
    UnkStruct_0200c5e0 *p;
    unsigned short val;
    p = (UnkStruct_0200c5e0 *) ((char *) base + 0x7d4);
    if (p->unk_0C == 0) {
        val = p->unk_00;
        if (func_020103c0(base, &val)) {
            p->unk_0C = 1;
        }
    }
}
