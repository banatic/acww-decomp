/* func_0208d560 @ 0x0208d560, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051694(void *arg);
extern void func_0205166c(void *arg, int flag);

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    int unk_44;
} UnkStruct_0208d560;

void func_0208d560(UnkStruct_0208d560 *obj)
{
    if (obj->unk_40 != 0) {
        obj->unk_44 = obj->unk_44 - 1;
        if (obj->unk_44 <= 0) {
            obj->unk_44 = 20;
            func_02051694(obj->unk_40);
        } else if (obj->unk_44 == 8) {
            func_0205166c(obj->unk_40, 0);
        }
    }
}
