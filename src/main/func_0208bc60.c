/* func_0208bc60 @ 0x0208bc60, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208bc60 {
    unsigned char pad_00[0x24];
    unsigned char unk_24;
    unsigned char pad_25[3];
    int unk_28;
};

extern int func_0208c620(void *);
extern void func_0203e1ec(void);
extern void func_0208bd90(struct UnkStruct_0208bc60 *);

void func_0208bc60(struct UnkStruct_0208bc60 *param)
{
    if (func_0208c620(&param->unk_28)) {
        func_0203e1ec();
        param->unk_24 = 0;
        func_0208bd90(param);
    }
}
