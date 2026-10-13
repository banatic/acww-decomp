/* func_020a8c38 @ 0x020a8c38, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e3d94;
extern int data_020da6dc;

struct SomeObject {
    void *vtable;
    int unk_04;
    char unk_08;
};

void func_020a9b44(void *ptr);

struct SomeObject *func_020a8c38(struct SomeObject *this)
{
    this->vtable = (void *) &data_020e3d94;
    func_020a9b44(&this->unk_08);
    this->vtable = (void *) &data_020da6dc;
    return this;
}
