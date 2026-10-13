/* func_ov094_0229b19c @ 0x0229b19c, 0x34 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b184(void *);
extern void func_ov094_0229b1d0(void *);

typedef struct {
    char pad_00[0x26];
    unsigned char counter;
    unsigned char result;
} UnkStruct_0229b19c;

int func_ov094_0229b19c(UnkStruct_0229b19c *p)
{
    if (p->counter != 0) {
        p->counter--;
        p->result = (unsigned char) func_ov094_0229b184(p);
        return 0;
    } else {
        func_ov094_0229b1d0(p);
        return 1;
    }
}
