/* room_interior_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02034ce0 @ 0x02034ce0, 0xc bytes, Thumb
 * func_02034cc0 @ 0x02034cc0, 0x20 bytes, Thumb
 * func_02034ca0 @ 0x02034ca0, 0x20 bytes, Thumb
 * func_02034c64 @ 0x02034c64, 0x3c bytes, Thumb
 * func_02034bd4 @ 0x02034bd4, 0x90 bytes, Thumb
 */

typedef struct {
    unsigned short id;
    unsigned short f0 : 6;
    unsigned short f6 : 1;
    unsigned short f7 : 1;
    unsigned short f8 : 1;
} Msg;

extern char data_021c519c[];
extern void func_020051b0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned char data_021c5204[];
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_0209871c(int *, int);
extern void func_0204c048(int, int, int);
extern int data_021dc7bc;
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern unsigned short func_020b65c4(void);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);

void func_02034ce0(unsigned short *r0)
{
    *r0 = 0xfff1;
}

void func_02034cc0(void)
{
    __cxa_vec_cleanup((void *) (data_021c519c), 0x33, 2, (void (*)(void *)) func_020051b0);
}

void func_02034ca0(void)
{
    __cxa_vec_cleanup((void *) ((void *) data_021c5204), 0x33, 2, (void (*)(void *)) func_020051b0);
}

void func_02034c64(int a, int b)
{
    int tested_value0;
    int mask = b & 7;
    int result = 0;

    if ((tested_value0 = (int) (func_020984e8())) != 0) {
        int x = func_02099870(tested_value0);
        result = func_0209871c(&data_021dc7bc, x) & 3;
    }

    func_0204c048(a, result, mask);
}

void func_02034bd4(unsigned short *src, int a1, unsigned short a2, unsigned short a3)
{
    Msg m;
    void *ptr;
    if (func_02073d90(data_020ccf94) != 0) {
        m.id = *src;
        m.f0 = func_020b65c4();
        m.f6 = a2;
        m.f7 = a1;
        m.f8 = a3;
        ptr = data_020ccf94;
        func_02073820(ptr);
        func_020737f0(ptr, &m, 4);
        func_02073770(ptr, 0x14, 4);
    }
}
