/* func_020feff4 @ 0x020feff4, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    char pad_00[0x2e];
    unsigned short unk_2E;
} UnkStruct_020feff4;

void func_020feff4(UnkStruct_020feff4 *p, int unused, int v)
{
    unsigned short tmp;
    unsigned short q;

    q = ((255 - v) * 31) / 255;
    tmp = p->unk_2E;
    p->unk_2E = (tmp & ~0x3e0) | ((q & 0x1f) << 5);
}
