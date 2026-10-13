/* func_ov112_0229efe8 @ 0x0229efe8, 0x70 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void *data_021c9b28;

extern int func_02073d90(void *);
extern void *func_020e9958(void *heap, unsigned int size);
extern void func_020e993c(void *heap, void *p);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
extern short func_02073d80(void *);

void func_ov112_0229efe8(void *obj)
{
    void *heap;
    unsigned char *buf;
    void *ptr;

    if (func_02073d90(data_020ccf94) != 0) {
        heap = data_021c9b28;
        buf = (unsigned char *) func_020e9958(heap, 0xc1);
        buf[0] = 0;
        MI_CpuCopy8((char *) obj + 0xc4, buf + 1, 0xc0);
        ptr = data_020ccf94;
        func_02073820(ptr);
        func_020737f0(ptr, buf, 0xc1);
        func_02073770(ptr, 0x16, 4);
        *(short *) ((char *) obj + 0xb4) = func_02073d80(ptr);
        func_020e993c(heap, buf);
    }
}
