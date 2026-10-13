/* func_02082eb4 @ 0x02082eb4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020830d0(void *this);
extern void func_020edb3c(void *this);

typedef struct {
    void *vtable;
} UnkStruct_02082eb4;

extern UnkStruct_02082eb4 data_020e1a54;

UnkStruct_02082eb4 *func_02082eb4(UnkStruct_02082eb4 *this)
{
    this->vtable = &data_020e1a54;
    func_020830d0(this);
    func_020edb3c(this);
    return this;
}
