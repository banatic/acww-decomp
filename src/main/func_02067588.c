/* func_02067588 @ 0x02067588, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a82a0(const char *data);

typedef struct SomeObj SomeObj;
typedef struct SomeVtbl {
    void (*unk_00)();
    void (*unk_04)();
    void (*unk_08)();
    void (*unk_0C)();
    void (*unk_10)(SomeObj *, int);
} SomeVtbl;
struct SomeObj {
    SomeVtbl *vtbl;
};

typedef struct UnkStruct_02067588 {
    char pad_00[0x14A8];
    SomeObj *obj;
    char data[0x9E8];
    unsigned char flag;
} UnkStruct_02067588;

void func_02067588(UnkStruct_02067588 *this)
{
    if (this->flag != 0) {
        int value = func_020a82a0(this->data);
        this->obj->vtbl->unk_10(this->obj, value);
        this->flag = 0;
    }
}
