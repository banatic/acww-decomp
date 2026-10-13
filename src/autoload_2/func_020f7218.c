/* func_020f7218 @ 0x020f7218, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f1d3c(void *, int);
extern void NNS_SndArcPlayerStartSeq(void *, unsigned short);
extern int data_021fd1bc;

typedef struct {
    char pad_00[4];
    char unk_04[10];
    unsigned char unk_0E;
} UnkStruct_020f7218;

void func_020f7218(UnkStruct_020f7218 *p)
{
    int n = 3;
    int v;
    do {
        v = func_020f1d3c(&data_021fd1bc, n);
    } while ((v & 0xff) == p->unk_0E);
    p->unk_0E = v & 0xff;
    NNS_SndArcPlayerStartSeq(&p->unk_04, (unsigned short) (p->unk_0E + 0xad));
}
