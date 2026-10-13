/* func_020f746c @ 0x020f746c, 0x308 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f7bc4(void *p, int a, void *h);
extern void NNS_SndPlayerWriteVariable(void *h, int v, int x);
extern void ciAddUNQUIETFilter(void *p, void *q);

typedef struct {
    int unk_00;
    void *unk_04;
    void *unk_08;
    char unk_0C;
    signed char d;
} UnkStruct_020f746c;

void func_020f746c(UnkStruct_020f746c *p, int code, void *q)
{
    switch (code) {
        case 1:
            if (p->d == 0) {
                func_020f7bc4(p, 0x4fc, &p->unk_04);
            } else {
                func_020f7bc4(p, 0x4fd, &p->unk_04);
            }
            {
                unsigned int ok = (unsigned int) (p->unk_08 != 0);
                if (ok > 0) {
                    break;
                }
            }
            func_020f7bc4(p, 0x500, &p->unk_08);
            break;
        case 0x46:
            NNS_SndPlayerWriteVariable(&p->unk_08, 1, 1);
            break;
        case 0xd2:
            NNS_SndPlayerWriteVariable(&p->unk_08, 2, 1);
            break;
        case 0xdc:
            NNS_SndPlayerWriteVariable(&p->unk_08, 1, 0);
            break;
        case 0xe6:
            if (p->d == 0) {
                func_020f7bc4(p, 0x4fe, &p->unk_04);
            } else {
                func_020f7bc4(p, 0x4ff, &p->unk_04);
            }
            break;
        case 0xfd:
            if (p->d == 1) {
                NNS_SndPlayerWriteVariable(&p->unk_08, 2, 2);
            }
            break;
        case 0x102:
            if (p->d == 0) {
                NNS_SndPlayerWriteVariable(&p->unk_08, 2, 2);
            }
            break;
        case 0x118:
            NNS_SndPlayerWriteVariable(&p->unk_08, 1, 1);
            break;
        case 0x172:
            NNS_SndPlayerWriteVariable(&p->unk_08, 1, 0);
            NNS_SndPlayerWriteVariable(&p->unk_08, 2, 1);
            break;
        case 0x17f:
            if (p->d == 1) {
                NNS_SndPlayerWriteVariable(&p->unk_04, 0, 2);
            }
            break;
        case 0x186:
            if (p->d == 0) {
                NNS_SndPlayerWriteVariable(&p->unk_04, 0, 2);
            }
            break;
        case 0x195:
            if (p->d == 1) {
                NNS_SndPlayerWriteVariable(&p->unk_08, 2, 3);
            }
            break;
        case 0x1a9:
            if (p->d == 0) {
                NNS_SndPlayerWriteVariable(&p->unk_08, 2, 3);
            }
            break;
        case 0x1df:
            p->d = (signed char) (p->d + 1);
            if (p->d == 2) {
                p->d = 0;
            }
            break;
    }
    ciAddUNQUIETFilter(p, q);
}
