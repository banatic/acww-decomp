/* func_020a6d84 @ 0x020a6d84, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a6d84 {
    char pad_00[0x64];
    unsigned int unk_64;
} UnkStruct_020a6d84;

extern UnkStruct_020a6d84 *data_020ccf94;

int func_02073dd4(UnkStruct_020a6d84 *p, unsigned int arg);
int func_02073394(UnkStruct_020a6d84 *p);
void func_020a7454(unsigned int arg);

void func_020a6d84(void)
{
    UnkStruct_020a6d84 *ptr = data_020ccf94;
    if (func_02073dd4(ptr, ptr->unk_64)) {
        unsigned int ret = func_02073394(ptr);
        if (ret) {
            func_020a7454(ret);
        }
    }
}
