/* func_02069460 @ 0x02069460, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206b97c(void *this, int value);

typedef struct {
    char pad_00[0x24];
    int unk_24;
} UnkStruct_02069460;

void func_02069460(UnkStruct_02069460 *this)
{
    int tmp = this->unk_24;
    tmp = (int) ((char *) tmp + 0x14b8);
    tmp = (int) ((char *) tmp + 0x1cc);
    func_0206b97c(this, tmp);
}
