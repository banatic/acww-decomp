/* func_02077b70 @ 0x02077b70, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204fa5c(void *, int);
extern int FS_LoadOverlayImage(void *);
extern void FS_StartOverlay(void *);

struct UnkStruct_02077b70 {
    int unk_00;
    unsigned char unk_04;
    unsigned char pad_05[3];
    unsigned char unk_08[1];
};

int func_02077b70(struct UnkStruct_02077b70 *s, int val)
{
    int result;

    s->unk_04 = 1;
    s->unk_00 = val;
    func_0204fa5c(s->unk_08, val);
    FS_LoadOverlayImage(s->unk_08);
    FS_StartOverlay(s->unk_08);
    result = 0;
    s->unk_04 = result;
    return result;
}
