/* func_0208effc @ 0x0208effc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x48];
    void *unk_48;
} UnkStruct_0208effc;

extern void func_020a8fb8(void *ptr);

void func_0208effc(UnkStruct_0208effc *a)
{
    if (a->unk_48) {
        func_020a8fb8(a->unk_48);
        a->unk_48 = 0;
    }
}
