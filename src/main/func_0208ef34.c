/* func_0208ef34 @ 0x0208ef34, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern int data_020e236c;

typedef struct UnkStruct_0208ef34 {
    int *unk_00;
    char pad_04[8];
    char unk_0C[4];
} UnkStruct_0208ef34;

UnkStruct_0208ef34 *func_0208ef34(UnkStruct_0208ef34 *this)
{
    this->unk_00 = &data_020e236c;
    func_0208a1f4(&this->unk_0C);
    func_0208af00(this);
    return this;
}
