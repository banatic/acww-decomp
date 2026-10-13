/* func_02042218 @ 0x02042218, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02042218 {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
} UnkStruct_02042218;

extern UnkStruct_02042218 *data_020ccf94;
extern unsigned char data_ov003_02260538;
extern int func_02073dd4(UnkStruct_02042218 *p, unsigned int field);
extern int func_020b6660(void);
extern int func_020b6640(void);
extern void func_ov003_0222ddac(void);

void func_02042218(unsigned char *param)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }
    if (func_020b6660() != 0 || func_020b6640() != 0) {
        if (param[1] != 0) {
            data_ov003_02260538 = 1;
        }
        if (param[1] != 0 || param[0] != 0) {
            func_ov003_0222ddac();
        }
        param[0] = 0;
        param[1] = 0;
    }
}
