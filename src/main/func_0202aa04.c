/* func_0202aa04 @ 0x0202aa04, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020984e8(void);
extern int func_02099870(void);
extern void func_02094fd4(void *);
extern void func_02095074(int, void *);
extern void func_0208150c(void *);
extern int func_020036e8(void);
extern int func_0202aab0(void *, void *, int);
extern void func_020a8bb8(void *, void *);
extern void func_0209df64(void *);
extern void func_02081c40(void *, void *);
extern void func_0207a62c(void *, void *);
extern void func_020802c8(void *, void *, int);
extern void func_02068404(void *, int, void *);
extern void func_02094fbc(void *);
extern unsigned char data_021e5a2c;

typedef struct {
    char pad_00[0x830];
    void *unk_830;
} UnkStruct_0202aa04;

struct UnkStruct_0202aa04_2 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x100 - 0x44];
    UnkStruct_0202aa04 *unk_100;
    char pad_104[0x12c - 0x104];
    void *unk_12C;
};

typedef struct {
    u32 data[8];
} Mutex;

void func_0202aa04(struct UnkStruct_0202aa04_2 *self)
{
    int local1;
    Mutex mutex1;
    Mutex mutex2;
    int handle;

    func_020984e8();
    handle = func_02099870();

    func_02094fd4(&mutex1);
    func_02094fd4(&mutex2);
    func_02095074(handle, &mutex2);

    func_0208150c(self->unk_100->unk_830);

    if (func_0202aab0(&mutex1, &mutex2, func_020036e8()) == 0) {
        func_020a8bb8(&mutex1, &mutex2);
    }

    if (self->unk_12C != 0) {
        func_0209df64(&local1);
        func_02081c40(self->unk_12C, &mutex1);
        func_0207a62c(&data_021e5a2c, &local1);
    } else {
        func_020802c8(self->unk_100->unk_830, &mutex1, handle);
    }

    func_02068404(self->unk_40, 0, &mutex1);
    func_02094fbc(&mutex2);
    func_02094fbc(&mutex1);
}
