/* func_020a6c08 @ 0x020a6c08, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_020a6c08 {
    char pad_00[0x64];
    int unk_64;
} *data_020ccf94;

extern char data_021f4320;

int func_02073dd4(struct UnkStruct_020a6c08 *p, int val);
void func_020a6250(void *p);
void func_020a6188(void *p);
void func_020a68e0(void *p);
void func_020a669c(void *p);
void func_020a67d8(void *p);
void func_020a5c38(void *p);
void func_020a5750(void *p);
void func_020a636c(void *p);
void func_020a6294(void *p);

void func_020a6c08(void)
{
    int r4 = data_020ccf94->unk_64;
    if (func_02073dd4(data_020ccf94, r4) == 0) {
        return;
    }
    func_020a6250(&data_021f4320);
    func_020a6188(&data_021f4320);
    if (r4 == 0) {
        func_020a68e0(&data_021f4320);
        func_020a669c(&data_021f4320);
    }
    if (r4 != 0) {
        func_020a67d8(&data_021f4320);
    }
    if (r4 == 0) {
        func_020a5c38(&data_021f4320);
    }
    func_020a5750(&data_021f4320);
    func_020a636c(&data_021f4320);
    func_020a6294(&data_021f4320);
}
