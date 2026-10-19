/* func_020f72b8 @ 0x020f72b8, 0x180 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int pad_00;
    unsigned int unk_04;
    unsigned int unk_08;
} Snd;

extern int func_020f7bc4(Snd *p, int id, unsigned int *addr);
extern int NNS_SndPlayerWriteVariable(unsigned int *addr, int var, int value);
extern void func_020f7c1c(Snd *p, int arg);

void func_020f72b8(Snd *p, int cmd, int arg)
{
    switch (cmd) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4: {
            unsigned int flag4;
            unsigned int flag8;

            flag4 = (p->unk_04 != 0) ? 1 : 0;
            if (flag4 == 0) {
                func_020f7bc4(p, 0x501, &p->unk_04);
            }

            flag8 = (p->unk_08 != 0) ? 1 : 0;
            if (flag8 == 0) {
                func_020f7bc4(p, 0x502, &p->unk_08);
            }

            NNS_SndPlayerWriteVariable(&p->unk_04, 0, 1);
            NNS_SndPlayerWriteVariable(&p->unk_08, 0, 1);
            break;
        }
        case 0x5a:
            NNS_SndPlayerWriteVariable(&p->unk_04, 0, 2);
            NNS_SndPlayerWriteVariable(&p->unk_08, 0, 2);
            break;
        case 0x8c:
            NNS_SndPlayerWriteVariable(&p->unk_04, 0, 3);
            break;
        case 0xe1:
            NNS_SndPlayerWriteVariable(&p->unk_04, 0, 4);
            break;
        case 0xeb:
            NNS_SndPlayerWriteVariable(&p->unk_04, 0, 5);
            break;
        case 0xf5:
            NNS_SndPlayerWriteVariable(&p->unk_08, 0, 3);
            break;
    }

    func_020f7c1c(p, arg);
}
