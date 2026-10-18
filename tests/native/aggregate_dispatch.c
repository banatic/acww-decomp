/* Real dispatch, fault handling and trampoline, with a bounded ARM execution
 * loop and controlled external helpers. The game scheduler is tested by gates. */
#define run_until_return aggregate_test_run_until_return
#include "../../runtime/native_run.c"
#undef run_until_return
#include "aggregate_rom.h"

extern void func_02013304(void), func_020404b4(void), func_0207fc7c(void), func_020afa48(void);
extern uint64_t aggregate_pc_caller(int kind, uint32_t target, const uint32_t *args);
extern uint32_t aggregate_scalar_caller(uint32_t target, const uint32_t *args);
extern uint32_t aggregate_scalar_date_caller(void *object);
#ifndef AGG_TEST_CLEAN
#define AGG_TEST_CLEAN 0
#endif
static uint32_t agg_clean_schedule(uint32_t object, uint32_t event, uint32_t date);
const NativeFunction native_functions[4] = {
    {0x02013305, 0x80, func_02013304, NATIVE_RET_STRUCT3 | (2 << 4)},
    {0x020404b5, 0x94, func_020404b4, NATIVE_RET_UNION4 | (3 << 4)},
    {0x0207fc7d, 0x4c, func_0207fc7c, NATIVE_RET_PAIR8 | (2 << 4)},
    {0x020afa49, 0x8c, func_020afa48, NATIVE_RET_STRUCT4 | (1 << 4)}
};
const NativeFunction clean_functions[1] = {
    {0x020404b5, 0x94, agg_clean_schedule, NATIVE_RET_32 | (3 << 4) |
                                          (AGG_TEST_CLEAN == 2 || AGG_TEST_CLEAN == 4 ? CLEAN_STANDBY : 0)}
};
const uint32_t native_function_count = 4, clean_function_count = AGG_TEST_CLEAN ? 1 : 0;
const NativeBody native_bodies[1], clean_bodies[1];
const uint32_t native_body_count = 0, clean_body_count = 0;
const NativePrivate native_private[1];
const uint32_t native_private_count = 0;
const char *const native_module_names[1] = {"main"};
const uint32_t native_module_count = 1;

#define CHECK(x) do { if (!(x)) { fprintf(stderr,"Failed %d: %s\n",__LINE__,#x); exit(2); } } while (0)
static unsigned agg_repeat, agg_events, agg_phase;
static uint32_t agg_log[128][4];
static int agg_index;
static uint32_t agg_pair_index, agg_category;
static unsigned char agg_flag;
static uint32_t agg_arguments[4];
static Fn *agg_active;

static void agg_event(uint32_t kind, uint32_t a, uint32_t b, uint32_t c)
{
    CHECK(agg_events < 128);
    uint32_t *event = agg_log[agg_events++];
    event[0] = kind; event[1] = a; event[2] = b; event[3] = c;
}
static uint32_t agg_clean_schedule(uint32_t object, uint32_t event, uint32_t date)
{
    agg_event(8, object, event, date);
    return object ^ event ^ date ^ 0x87654321u;
}
int func_02013384(void *self, void *arg)
{
    CHECK((uintptr_t) self == 0x02390000 && (uintptr_t) arg == 0x02391000);
    agg_event(1, (uint32_t) (uintptr_t) self, (uint32_t) (uintptr_t) arg, (uint32_t) agg_index);
    return agg_index;
}
void MI_CpuFill8(void *destination, int value, int size)
{
    CHECK(size >= 0 && size < 100);
    agg_event(2, (uint32_t) value, (uint32_t) size, 0);
    memset(destination, value, (size_t) size);
}
void MI_CpuCopy8(const void *source, void *destination, int size)
{
    CHECK(size == 3);
    const unsigned char *p = source;
    agg_event(3, p[0], p[1], p[2]);
    memcpy(destination, source, (size_t) size);
}
void *func_020409c8(void *base, int index)
{
    CHECK((uintptr_t) base == 0x021dc7a8 + 0x17218);
    agg_event(4, (uint32_t) (uintptr_t) base, (uint32_t) index, 0);
    /* Actual helper 020409c8 returns six-byte records, indices 1 through 5.
     * Its halfword fields are aligned; an arbitrary odd fixture pointer would
     * exercise a different (unaligned ARM load) contract. */
    return index < 1 || index > 5 ? NULL : (char *) base + 20 + 6 * (index - 1);
}
uint32_t func_0209c2d4(unsigned char *flag, uint32_t category)
{
    CHECK(category == agg_category && *flag == 3);
    agg_event(5, category, *flag, agg_pair_index);
    *flag = agg_flag;
    return agg_pair_index;
}
void *func_020afad4(void *object)
{
    CHECK((uintptr_t) object == 0x02390000);
    agg_event(6, (uint32_t) (uintptr_t) object, 0, 0);
    return (void *) (uintptr_t) 0x02393000;
}
void func_0209e140(unsigned char *packet, int count)
{
    CHECK(count == 1);
    uint32_t first, second;
    memcpy(&first, packet, 4); memcpy(&second, packet + 4, 4);
    agg_event(7, first, second, (uint32_t) count);
    packet[3] ^= 0x81; packet[4] ^= 0x42; packet[5] ^= 0x24;
}
static int agg_hook(ArmCpu *state, void *user)
{
    uint32_t address = (uint32_t) (uintptr_t) user;
    switch (address) {
        case 0x02013384:
            state->r[0] = (uint32_t) func_02013384((void *)(uintptr_t)state->r[0], (void *)(uintptr_t)state->r[1]); break;
        case 0x02117568:
            MI_CpuFill8((void *)(uintptr_t)state->r[0], (int)state->r[1], (int)state->r[2]); break;
        case 0x021175fc:
            MI_CpuCopy8((void *)(uintptr_t)state->r[0], (void *)(uintptr_t)state->r[1], (int)state->r[2]); break;
        case 0x020409c8:
            state->r[0] = (uint32_t)(uintptr_t)func_020409c8((void *)(uintptr_t)state->r[0], (int)state->r[1]); break;
        case 0x0209c2d4:
            state->r[0] = func_0209c2d4((void *)(uintptr_t)state->r[0], state->r[1]); break;
        case 0x020afad4:
            state->r[0] = (uint32_t)(uintptr_t)func_020afad4((void *)(uintptr_t)state->r[0]); break;
        case 0x0209e140:
            func_0209e140((void *)(uintptr_t)state->r[0], (int)state->r[1]); break;
        default: CHECK(0);
    }
    state->r[15] = state->r[14] & ~1u;
    if (state->r[14] & 1) state->cpsr |= ARM_CPSR_T;
    else state->cpsr &= ~ARM_CPSR_T;
    return 0;
}
static ArmHook agg_hooks(void *user, uint32_t address, void **hook_user)
{
    (void) user;
    *hook_user = (void *) (uintptr_t) address;
    switch (address) {
        case 0x02013384: case 0x02117568: case 0x021175fc: case 0x020409c8:
        case 0x0209c2d4: case 0x020afad4: case 0x0209e140: return agg_hook;
        default: return NULL;
    }
}
static int agg_io_read(void *user, uint32_t address, int size, uint32_t *value)
{
    (void) user;
    return host_access(address, size, value, 0);
}
static int agg_io_write(void *user, uint32_t address, int size, uint32_t value)
{
    (void) user;
    return host_access(address, size, &value, 1);
}
void aggregate_test_run_until_return(void)
{
    CHECK(agg_phase == 2);
    Record expected = {.kind = CROSS_CALL_OUT, .function = agg_active->address & ~1u};
    memcpy(expected.args, agg_arguments, sizeof(expected.args));
    check_arguments(&expected, agg_active->address & ~1u);
    CHECK(arm_run(cpu, ARM_RETURN_ADDRESS, 10000) == ARM_RETURNED);
}

int main(void)
{
    CHECK(memory_init() == 0 && native_os_init() == 0);
    io_unmapped = host_access;
    Fn entries[4];
    memset(entries, 0, sizeof(entries));
    for (unsigned i = 0; i < 4; i++) {
        const NativeFunction *n = &native_functions[i];
        entries[i] = (Fn) {.address=n->address, .size=n->size, .module=0, .native=n,
                          .name="aggregate", .params=i==1?3:i==3?1:2,
                          .arg_words=i==2?3:i==1?3:i==3?1:2, .guest_frame=-1, .guest_spill_arg=-1};
        memcpy((void *)(uintptr_t)(n->address & ~1u), aggregate_rom[i], n->size);
    }
    entries[2].argument_contract = 0x103;
    fns = entries; fn_count = 4;
    module_count = 1; modules[0].resident = resident_ready = 1;
    strcpy(modules[0].name, "main");
    entry_bits = calloc((ENTRY_END - ENTRY_BASE) / 16, 1);
    CHECK(entry_bits != NULL);
    for (unsigned i=0;i<4;i++) {
        uint32_t bit=((entries[i].address&~1u)-ENTRY_BASE)>>1;
        entry_bits[bit>>3] |= (uint8_t)(1u<<(bit&7));
    }
    ArmCpu state;
    cpu = &state;
    if (AGG_TEST_CLEAN) {
        int selected=AGG_TEST_CLEAN==1 || AGG_TEST_CLEAN==3;
        for(unsigned i=0;i<4;i++) entries[i].status='N';
        CHECK(patch_clean() == 0);
        for (unsigned n=0;n<1000;n++) {
            uint32_t args[4]={0x02390000,0x99,0xaabbcc00u|n%6,0};
            memset((void *)(uintptr_t)args[0],0x3c,256);
            arm_init(cpu); cpu->hook_at=agg_hooks;
            cpu->r[13]=0x023f0000; cpu->r[14]=ARM_RETURN_ADDRESS;
            memcpy(cpu->r,args,sizeof(args));
            agg_events=0;
            entries[1].status='N';
            entries[1].native=selected?&clean_functions[0]:&native_functions[1];
            uint32_t expected=selected?args[0]^args[1]^args[2]^0x87654321u:0;
            CHECK(aggregate_scalar_caller((uint32_t)(uintptr_t)clean_functions[0].host,args)==expected);
            CHECK(aggregate_pc_caller(NATIVE_RET_UNION4,(uint32_t)(uintptr_t)native_functions[1].host,args)==expected);
            CHECK(aggregate_pc_caller(NATIVE_RET_UNION4,entries[1].address,args)==expected);
            CHECK(call_native(cpu,&entries[1])==0 && cpu->r[0]==expected);
        }
        puts(selected?"1000 selected Clean union/scalar cases pass: direct, DS pointer and ARM entry":
                      "1000 standby Clean scalar/union cases pass: direct, DS pointer and ARM entry");
        if(AGG_TEST_CLEAN>=3) {
            entries[1].status='R';
            CHECK(patch_kept()==0);
            agg_active=&entries[1]; agg_phase=2;
            for(unsigned n=0;n<1000;n++) {
                uint32_t args[4]={0x02390000,0x99,0xaabbcc00u|n%6,0};
                memcpy(agg_arguments,args,sizeof(args));
                arm_init(cpu); cpu->hook_at=agg_hooks;
                cpu->io_read=agg_io_read; cpu->io_write=agg_io_write;
                cpu->r[13]=0x023f0000; memcpy(cpu->r,args,sizeof(args));
                agg_events=0;
                CHECK(aggregate_scalar_caller((uint32_t)(uintptr_t)clean_functions[0].host,args)==0);
                CHECK(aggregate_pc_caller(NATIVE_RET_UNION4,(uint32_t)(uintptr_t)native_functions[1].host,args)==0);
                CHECK(aggregate_pc_caller(NATIVE_RET_UNION4,entries[1].address,args)==0);
                CHECK(arm_call(cpu,entries[1].address,10000)==ARM_RETURNED && cpu->r[0]==0);
                CHECK(cpu->r[13]==0x023f0000);
            }
            puts("1000 Clean bridge cases also pass with the selected implementation forced Reference");
        }
        return 0;
    }
    uint8_t initial[256], reference[256];
    uint32_t expected_log[128][4];
    unsigned cases = 0;
    for (agg_repeat=0;agg_repeat<160;agg_repeat++) {
        for(unsigned i=0;i<4;i++) {
            agg_active=&entries[i];
            int kind=native_return(agg_active->native);
            agg_index=(int)(agg_repeat%31)-1;
            agg_pair_index=agg_repeat%8==7 ? 0xffffffffu : agg_repeat%8;
            agg_flag=(unsigned char)(agg_repeat%3);
            agg_category=0x80000000u+agg_repeat*71;
            for(unsigned b=0;b<sizeof(initial);b++) initial[b]=(uint8_t)(b*7+agg_repeat);
            memcpy((void *)(uintptr_t)0x02390000,initial,sizeof(initial));
            for(unsigned k=1;k<=5;k++) {
                uint8_t *entry=(uint8_t *)(uintptr_t)(0x021dc7a8+0x17218+20+6*(k-1));
                entry[0]=(uint8_t)(0x80+k); entry[1]=(uint8_t)(0xf0-k);
                entry[2]=(unsigned char)(k%3==0?0x45:k%3==1?0x40:0x20);
            }
            *(uint32_t *)(uintptr_t)0x02393000=0x00e5c3a1u | ((agg_repeat%2) << 24);
            for(unsigned k=0;k<10;k++) *(uint32_t *)(uintptr_t)(0x021d1330+4*k)=0x80000000u+agg_repeat*32+k;
            *(uint32_t *)(uintptr_t)0x0213dd98=0;
            *(uint32_t *)(uintptr_t)0x0213dd9c=0xfffe0000u+agg_repeat;
            uint32_t args[4]={0x02390000,0x02391000,0,0};
            if(i==1) { const uint32_t categories[]={0x45,0x60,0x40,0x20,0x99};
                       args[1]=categories[agg_repeat%5]; args[2]=0xaabbcc00u | (agg_repeat%10); }
            if(i==2) { args[0]=0x023aff04; args[1]=0x87654321; args[2]=agg_category; }
            memcpy(agg_arguments,args,sizeof(args));
            uint64_t expected_value=0;
            unsigned expected_events=0;
            for(agg_phase=0;agg_phase<3;agg_phase++) {
                memcpy((void *)(uintptr_t)0x02390000,initial,sizeof(initial));
                memset((void *)(uintptr_t)0x023aff00,0x5a,16);
                arm_init(cpu); cpu->hook_at=agg_hooks;
                cpu->io_read=agg_io_read; cpu->io_write=agg_io_write;
                cpu->r[13]=0x023f0000; cpu->r[14]=ARM_RETURN_ADDRESS;
                for(unsigned r=4;r<=11;r++) cpu->r[r]=0x44440000u+r;
                memcpy(cpu->r,args,sizeof(args));
                agg_events=0;
                if(agg_phase==0) {
                    CHECK(arm_call(cpu,agg_active->address,10000)==ARM_RETURNED);
                    expected_value=cpu->r[0];
                    if(i==2) expected_value|=(uint64_t)cpu->r[1]<<32;
                    memcpy(reference,(void *)(uintptr_t)0x02390000,sizeof(reference));
                    expected_events=agg_events;
                    memcpy(expected_log,agg_log,sizeof(expected_log));
                } else if(agg_phase==1) {
                    agg_active->status='N';
                    CHECK(call_native(cpu,agg_active)==0);
                    if(cpu->r[0]!=(uint32_t)expected_value)
                        fprintf(stderr,"Aggregate %u repeat %u got %08x:%08x expected %08x:%08x\n",i,agg_repeat,
                                cpu->r[1],cpu->r[0],(uint32_t)(expected_value>>32),(uint32_t)expected_value);
                    CHECK(cpu->r[0]==(uint32_t)expected_value);
                    if(i==2) CHECK(cpu->r[1]==(uint32_t)(expected_value>>32));
                } else {
                    agg_active->status='R';
                    uint64_t result=aggregate_pc_caller(kind,agg_active->address,args);
                    uint64_t expected_pc=expected_value;
                    if(i==0) expected_pc=((expected_value>>8)&255)|((expected_value&255)<<8)|(expected_value&0xff0000);
                    if(i==2) expected_pc=(expected_value<<32)|(expected_value>>32);
                    CHECK(result==expected_pc);
                    CHECK(native_pop_bytes==
#ifdef _WIN32
                          0
#else
                          4
#endif
                    );
                }
                CHECK(cpu->r[13]==0x023f0000);
                for(unsigned r=4;r<=11;r++) CHECK(cpu->r[r]==0x44440000u+r);
                CHECK(memcmp(reference,(void *)(uintptr_t)0x02390000,sizeof(reference))==0);
                CHECK(agg_events==expected_events && memcmp(agg_log,expected_log,agg_events*sizeof(agg_log[0]))==0);
                CHECK(*(uint32_t *)(uintptr_t)0x023aff00==0x5a5a5a5a && *(uint32_t *)(uintptr_t)0x023aff0c==0x5a5a5a5a);
                if(i==2 && agg_phase<2) {
                    CHECK(*(uint32_t *)(uintptr_t)0x023aff04==(uint32_t)(expected_value>>32));
                    CHECK(*(uint32_t *)(uintptr_t)0x023aff08==(uint32_t)expected_value);
                }
                if(i==3 && agg_phase==1) {
                    agg_events=0;
                    CHECK(aggregate_scalar_date_caller((void *)(uintptr_t)args[0])==(uint32_t)expected_value);
                    CHECK(agg_events==expected_events && memcmp(agg_log,expected_log,agg_events*sizeof(agg_log[0]))==0);
                }
            }
            cases++;
        }
    }
    CHECK(cases==640 && calls_in==640 && calls_out==640);
    puts("640 cases across four actual ROM bodies agree through call_native and fault/trampoline/call_reference; memory, calls, return bytes, typed Pair arguments, stack cleanup and preserved registers checked");
    return 0;
}
