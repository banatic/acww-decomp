/* func_ov138_0229c6e8 @ 0x0229c6e8, 0x50 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov138_0229c574(void *, int);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a314(void *);
extern int func_ov138_0229c7a8(void *);
extern int func_ov138_0229c754(void *);
extern void func_ov138_0229c688(void *, int, int);

typedef struct {
    unsigned char pad_00[0x95];
    unsigned char state;
    unsigned char pad_96[2];
    unsigned char data[4];
} UnkStruct_0229c6e8;

void func_ov138_0229c6e8(UnkStruct_0229c6e8 *ptr)
{
    int v;
    int w;

    if (func_ov138_0229c574(ptr, 2) != 0 || (ptr->state != 3 && ptr->state != 4)) {
        func_ov002_0220a2b4(ptr->data);
    } else {
        func_ov002_0220a314(ptr->data);
    }

    v = func_ov138_0229c7a8(ptr);
    w = func_ov138_0229c754(ptr);
    func_ov138_0229c688(ptr, v, w);
}
