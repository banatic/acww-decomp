/* func_020a6d24 @ 0x020a6d24, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a6d24 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_020a6d24;

extern UnkStruct_020a6d24 *data_020ccf94;
extern int data_021f4320;
extern unsigned char data_021c75b8;

int func_02073dd4(UnkStruct_020a6d24 *p, int f);
int func_020a6684(int *p);
void func_020b65c4(int arg);
int func_020a6c98(void);
int func_020a6364(int *p);
void func_020a70a8(int arg);
void func_020a6688(int *p, int n);

void func_020a6d24(void)
{
    UnkStruct_020a6d24 *p;
    int cond;

    p = data_020ccf94;
    if (func_02073dd4(p, p->unk_64) != 0) {
        if (func_020a6684(&data_021f4320) == 3) {
            cond = (data_021c75b8 == 0) ? 1 : 0;
            if (cond != 0) {
                func_020b65c4(cond);
                if (func_020a6c98() == 0) {
                    func_020a70a8(func_020a6364(&data_021f4320));
                }
                func_020a6688(&data_021f4320, 5);
            }
        }
    }
}
