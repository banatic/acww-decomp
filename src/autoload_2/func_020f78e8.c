/* func_020f78e8 @ 0x020f78e8, 0x27c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020f78e8 {
    int unk_00;
    int unk_04;
    int unk_08;
    signed char c;
    signed char d;
} UnkStruct_020f78e8;

extern int func_020f7bc4(UnkStruct_020f78e8 *obj, int id, int *slot);
extern void func_020f7c1c(UnkStruct_020f78e8 *obj, int arg);
extern int NNS_SndArcPlayerStartSeq(int *slot, int a);
extern void NNS_SndPlayerMoveVolume(int *slot, int a, int b);
extern int NNS_SndPlayerWriteVariable(int *slot, int a, int b);
extern void NNS_SndPlayerStopSeq(int *slot, int a);
extern void NNS_SndPlayerSetTrackVolume(int *slot, int a, int b);

void func_020f78e8(UnkStruct_020f78e8 *obj, int key, int arg)
{
    unsigned int ok;

    switch (key) {
        case 1:
            ok = (unsigned int) (obj->unk_08 != 0);
            if (ok == 0) {
                func_020f7bc4(obj, 0x4f2, &obj->unk_08);
            }
            obj->d = (signed char) (obj->d + 1);
            if (obj->d == 3) {
                obj->d = 0;
            }
            switch (obj->d) {
                case 0:
                    func_020f7bc4(obj, 0x4f6, &obj->unk_04);
                    break;
                case 1:
                    NNS_SndArcPlayerStartSeq(&obj->unk_04, 0xf7);
                    break;
                case 2:
                    NNS_SndPlayerMoveVolume(&obj->unk_04, 0x28, 0xf);
                    break;
            }
            break;
        case 0x28:
            NNS_SndPlayerWriteVariable(&obj->unk_04, 1, 1);
            break;
        case 0x32:
            NNS_SndPlayerWriteVariable(&obj->unk_04, 0, 2);
            break;
        case 0x96:
            func_020f7bc4(obj, 0x4f3, &obj->unk_08);
            NNS_SndPlayerWriteVariable(&obj->unk_04, 0, 0);
            break;
        case 0xc8:
            func_020f7bc4(obj, 0x4f4, &obj->unk_08);
            NNS_SndPlayerWriteVariable(&obj->unk_04, 1, 2);
            break;
        case 0x12c:
            NNS_SndPlayerWriteVariable(&obj->unk_04, 0, 3);
            break;
        case 0x177:
            func_020f7bc4(obj, 0x4f5, &obj->unk_08);
            break;
        case 0x181:
            if (obj->d == 2) {
                NNS_SndPlayerStopSeq(&obj->unk_04, 0xf);
            }
            break;
    }

    switch (obj->d) {
        case 0:
            NNS_SndPlayerSetTrackVolume(&obj->unk_04, 0xfff, 0x7f);
            NNS_SndPlayerSetTrackVolume(&obj->unk_08, 0xfff, 0x7f);
            break;
        case 1:
            NNS_SndPlayerSetTrackVolume(&obj->unk_04, 0xfff, 0x64);
            NNS_SndPlayerSetTrackVolume(&obj->unk_08, 0xfff, 0);
            break;
        case 2:
            NNS_SndPlayerSetTrackVolume(&obj->unk_08, 0xfff, 0x64);
            break;
    }

    func_020f7c1c(obj, arg);
}
