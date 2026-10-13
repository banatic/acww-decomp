/* func_02034bd4 @ 0x02034bd4, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern unsigned short func_020b65c4(void);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
typedef struct {
    unsigned short id;
    unsigned short f0 : 6;
    unsigned short f6 : 1;
    unsigned short f7 : 1;
    unsigned short f8 : 1;
} Msg;
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
