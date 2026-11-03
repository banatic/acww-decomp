/* block_02042200: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204226c @ 0x0204226c, 0x34 bytes, Thumb
 * func_02042218 @ 0x02042218, 0x54 bytes, Thumb
 * func_02042200 @ 0x02042200, 0x18 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x30];
    struct {
        unsigned int : 6;
        signed int bit6 : 1;
        signed int bit7 : 1;
        unsigned int : 24;
    } flags;
} UnkStruct_0204226c;

typedef struct UnkStruct_02042218 {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
} UnkStruct_02042218;

extern UnkStruct_0204226c data_021c79c4;
extern UnkStruct_02042218 *data_020ccf94;
extern unsigned char data_ov003_02260538;
extern int func_02073dd4(UnkStruct_02042218 *p, unsigned int field);
extern int func_020b6660(void);
extern int func_020b6640(void);
extern void func_ov003_0222ddac(void);
extern int func_0204678c(void);
extern int data_021c776c;

void func_0204226c(unsigned char *dest)
{
    if (data_021c79c4.flags.bit7) {
        dest[0] = 1;
    } else {
        dest[0] = 0;
    }
    if (data_021c79c4.flags.bit6) {
        dest[1] = 1;
    } else {
        dest[1] = 0;
    }
}

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

void func_02042200(void)
{
    func_0204678c();
    func_0204226c((unsigned char *) (&data_021c776c));
}
