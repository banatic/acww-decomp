/* func_ov108_0229ca2c @ 0x0229ca2c, 0x6c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229ca2c {
    char pad_00[0x2ae];
    unsigned char byte_at_2ae;
    char pad_2AF[0xAA1];
    char sub2[1];
    char pad_D51[0x165F];
    char sub1[1];
};

extern int func_ov108_0229cc20(struct UnkStruct_0229ca2c *p, unsigned char b);
extern int func_ov108_0229cbe4(struct UnkStruct_0229ca2c *p, unsigned char b);
extern int func_0206fe54(void);
extern void func_0208aa60(void *a, int b, int c);
extern int func_ov108_0229cd70(struct UnkStruct_0229ca2c *p, unsigned char b);
extern int func_ov108_0229cd5c(struct UnkStruct_0229ca2c *p, unsigned char b);
extern int func_ov094_0229b9b4(void *a, void *b, int c);

void func_ov108_0229ca2c(struct UnkStruct_0229ca2c *p)
{
    int v1;
    int v2;

    v1 = func_ov108_0229cc20(p, p->byte_at_2ae) - 0x6d;
    v2 = func_ov108_0229cbe4(p, p->byte_at_2ae) - 0x78;
    if (func_0206fe54() != 0) {
        v2 -= 8;
    }
    func_0208aa60(&p->sub1, v1, v2);
    if (func_ov108_0229cd70(p, p->byte_at_2ae) != 0) {
        int v3;
        v3 = func_ov108_0229cd5c(p, p->byte_at_2ae);
        func_ov094_0229b9b4(&p->sub2, &p->sub1, v3);
    }
}
