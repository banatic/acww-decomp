/* func_ov066_0226a278 @ 0x0226a278, 0x70 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct GStruct {
    unsigned char pad_00[0x90];
    unsigned short flags;
} GStruct;

extern GStruct *data_ov066_0226bdf4;
extern int func_ov066_0226a160(unsigned short val);

int func_ov066_0226a278(unsigned int idx)
{
    while (idx < 14) {
        if (data_ov066_0226bdf4->flags & (1u << idx)) {
            if (func_ov066_0226a160((unsigned short) (idx + 1))) {
                return 1;
            }
        }
        idx = (unsigned short) (idx + 1);
    }
    return 0;
}
