/* func_020c18c4 @ 0x020c18c4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct GStruct GStruct;
struct GStruct {
    char pad_00[0x2ac];
    unsigned char unk_2AC;
    char pad_2AD[0x3a7];
    int unk_654;
};

extern GStruct *data_021fbbe0;
extern int func_0201a3e4(void *p);

int func_020c18c4(void)
{
    if (data_021fbbe0 != 0) {
        if (func_0201a3e4(&data_021fbbe0->unk_2AC) == 0xba && data_021fbbe0->unk_654 == 0) {
            return 1;
        }
        return 0;
    }
    return 1;
}
