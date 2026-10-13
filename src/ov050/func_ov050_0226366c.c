/* func_ov050_0226366c @ 0x0226366c, 0x24 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201612c(void *);
typedef struct {
    int a;
    int b;
} Pair;
extern Pair data_0213dd98;

void func_ov050_0226366c(void *this)
{
    func_0201612c(this);
    *(Pair *) ((char *) this + 0xb8) = data_0213dd98;
}
