/* func_020a68e0 @ 0x020a68e0, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef unsigned char u8;
typedef unsigned int u32;

struct Manager;

extern void func_02137550(void *, u32);
typedef struct {
    u32 a, b;
} Pair;
extern u32 data_020e3cdc[2];
extern struct Manager *data_020ccf94;

extern void func_020a6738(void *, u32 *, u32 *);
extern void func_020a6890(void *, u32 *, u32 *);
extern void func_020a7738(void *, u8 *, u8 *, u8 *);
extern void func_020a7820(u8 *);
extern void func_020a77f4(u8 *, int, u8, u8, u8, u32);
extern void func_020a7810(u8 *);
extern void func_02073820(struct Manager *);
extern void func_020737f0(struct Manager *, u8 *, int);
extern void func_02073770(struct Manager *, int, int);

void func_020a68e0(void *self)
{
    u32 off;
    u8 work[8];
    u32 arr[2];
    u32 out[2];
    u32 i;
    int idx;
    struct Manager *m;
    u32 val;

    *(Pair *) arr = *(Pair *) data_020e3cdc;
    func_02137550(out, 8);
    func_020a6738(self, arr, out);
    func_020a6890(self, &arr[1], &out[1]);

    i = 0;
    m = data_020ccf94;
    for (; i < 2; i++) {
        off = i * 4;
        idx = *(int *) ((u8 *) arr + off);
        if (idx >= 4) {
            continue;
        }

        func_020a7738((u8 *) self + 3 * idx, work, work + 1, work + 2);
        func_020a7820(&work[3]);
        val = *(u32 *) ((u8 *) out + off);
        func_020a77f4(&work[3], idx, work[0], work[1], work[2], val);
        func_02073820(m);
        func_020737f0(m, &work[3], 2);
        func_02073770(m, 9, 4);
        func_020a7810(&work[3]);
    }
}
