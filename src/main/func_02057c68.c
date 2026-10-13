/* func_02057c68 @ 0x02057c68, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct GStruct {
    char pad_00[0xbc];
    int unk_BC;
    char pad_C0[0x15];
    unsigned char unk_D5;
} GStruct;

extern GStruct *data_021c9350;
extern int func_020ea990(void *a, void *b);
extern int func_0205989c(void *p);

int func_02057c68(void *param)
{
    int result = 0;
    if (param != 0) {
        GStruct *p = data_021c9350;
        if (p != 0) {
            if (func_020ea990((char *) param + 0x5c, (char *) p + 0x60) <= p->unk_BC) {
                result = 1;
            } else {
                if (func_0205989c(p) != 0 && data_021c9350->unk_D5 == 0) {
                    result = 1;
                }
            }
        }
    }
    return result;
}
