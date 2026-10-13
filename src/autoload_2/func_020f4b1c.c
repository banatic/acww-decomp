/* func_020f4b1c @ 0x020f4b1c, 0x8c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned short bankNo;
    unsigned char volume;
    unsigned char channelPrio;
    unsigned char playerPrio;
    unsigned char playerNo;
    unsigned short pad_06;
} NNSSndSeqParam;

extern const NNSSndSeqParam *NNS_SndArcGetSeqArcParam(int seqArcNo, int index);
extern void OS_Terminate(void);

int func_020f4b1c(int val, int base)
{
    const NNSSndSeqParam *param;
    int result;

    param = NNS_SndArcGetSeqArcParam(val / 1000, val % 1000);
    if (param == 0) {
        OS_Terminate();
    }

    result = base + (param->playerPrio - 100);
    if (result > 0) {
        if (result >= 0x7f) {
            result = 0x7f;
        }
        return result;
    }
    return 0;
}
