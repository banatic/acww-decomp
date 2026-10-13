/* func_ov003_0222535c @ 0x0222535c, 0x4a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int w[12];
} Big;
void func_ov003_022253a8(void *a, void *b, Big s);
void func_020ad228(void *c);

void func_ov003_0222535c(void *a, void *b, void *c, Big s)
{
    func_ov003_022253a8(a, b, s);
    func_020ad228(c);
}
