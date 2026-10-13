/* func_020a7278 @ 0x020a7278, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} UnkStruct_020a7278;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
} TableEntry;

extern UnkStruct_020a7278 *data_020ccf94;
extern TableEntry data_021f4320[];

extern void func_020a7738(TableEntry *entry, unsigned char *c0, unsigned char *c1, unsigned char *c2);
extern int func_020a6684(TableEntry *data_021f4320);
extern int func_020a668c(TableEntry *data_021f4320);

int func_020a7278(void)
{
    int idx;
    unsigned char local[3];

    idx = data_020ccf94->unk_64;
    if (idx >= 4) {
        return 1;
    }

    func_020a7738(&data_021f4320[idx], &local[0], &local[1], &local[2]);

    if (local[2] == 0) {
        return local[1];
    }

    if (func_020a6684(data_021f4320) < 7) {
        return local[1];
    }

    return func_020a668c(data_021f4320);
}
