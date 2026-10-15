/* func_02082068 @ 0x02082068, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e194c[];
extern void *func_020a887c(void *this);
extern void func_020edb3c(void *this);

typedef struct {
    void *unk_00;
} UnkStruct_02082068;

UnkStruct_02082068 *func_02082068(UnkStruct_02082068 *this)
{
    this->unk_00 = data_020e194c;
    func_020a887c(this);
    func_020edb3c(this);
    return this;
}
