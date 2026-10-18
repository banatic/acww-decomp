/* Include the actual publication implementation; no replacement event matcher. */
#include "../../runtime/native_run.c"

const NativeFunction native_functions[1], clean_functions[1];
const uint32_t native_function_count = 0, clean_function_count = 0;
const NativeBody native_bodies[1], clean_bodies[1];
const uint32_t native_body_count = 0, clean_body_count = 0;
const NativePrivate native_private[1];
const uint32_t native_private_count = 0;
const char *const native_module_names[1] = {"main"};
const uint32_t native_module_count = 0;

extern ArmCpu *publication_cpu(void);
extern void publication_reset_clock(uint64_t now, uint64_t end, int irq);
extern unsigned publication_advances(void), publication_old_seen(void), publication_irq_requested(void);
extern int publication_nested_return(int old_boundary);
extern void func_020bb090(void);
extern void func_020ba340(void);

#define CHECK(x)                                                                                                              \
    do {                                                                                                                      \
        if (!(x)) {                                                                                                           \
            fprintf(stderr, "Failed: " #x "\n");                                                                              \
            exit(2);                                                                                                          \
        }                                                                                                                     \
    } while (0)

static unsigned irq_visits;
static int irq_shift_expected = -1;
static unsigned shift_callbacks;

void func_020be2d4(void *self, void *arg)
{
    CHECK((uintptr_t) self == 0x021f8b48u && (uintptr_t) arg == 0x021f8ab0u);
    CHECK(ds_word(0x021f8accu) == 0 && cpu->steps == 520);
    shift_callbacks++;
}

static int irq_return(ArmCpu *c, void *user)
{
    (void) user;
    CHECK(ds_word(0x021f6f70u) == 0);
    if (irq_shift_expected >= 0) {
        CHECK(ds_word(0x021f8accu) == (uint32_t) irq_shift_expected);
    }
    irq_visits++;
    uint32_t resume = c->r[14] - 4, saved = c->spsr;
    c->steps += 6;
    c->irq_line = 0;
    arm_set_cpsr(c, saved);
    c->r[15] = resume;
    return ARM_HOOK_AGAIN;
}

static ArmHook publication_hooks(void *user, uint32_t address, void **hook_user)
{
    (void) user;
    if (address == ARM_HIGH_VECTORS + 0x18) {
        return irq_return;
    }
    return native_hook_at(address, hook_user);
}

static Record event;

static void verify_recording(uint32_t entry, uint32_t size, uint32_t pc, uint32_t address, uint16_t store)
{
    publication_reset_clock(100, 512, 0);
    cpu = publication_cpu();
    Fn owner = {
        .address = entry | 1u, .size = size, .module = 0, .status = 'N', .native = &native_functions[0], .name = "publisher"};
    fns = &owner;
    fn_count = 1;
    modules[0].resident = resident_ready = 1;
    uint32_t bit = (entry - ENTRY_BASE) >> 1;
    entry_bits[bit >> 3] |= (uint8_t) (1u << (bit & 7));
    struct Frame frame = {.native = 1};
    stream_count = 1;
    streams[0].frames = &frame;
    streams[0].depth = 1;
    record_out = tmpfile();
    CHECK(record_out != NULL);
    record_count = 0;
    cpu->observe_word_store = record_publication;
    cpu->cpsr |= ARM_CPSR_T;
    *(uint16_t *) (uintptr_t) pc = store;
    *(uint16_t *) (uintptr_t) (pc + 2) = 0x4770; /* bx lr */
    for (unsigned pass = 0; pass < 3; pass++) {
        owner.status = pass == 1 ? 'R' : 'N';
        frame.native = pass != 2;
        cpu->cpsr |= ARM_CPSR_T;
        cpu->r[0] = 7;
        cpu->r[1] = store == 0x6008 ? address : address - 0x1c;
        cpu->r[2] = 7;
        cpu->r[14] = ARM_RETURN_ADDRESS;
        cpu->r[15] = pc;
        CHECK(arm_run(cpu, ARM_RETURN_ADDRESS, 10) == ARM_RETURNED);
        CHECK(record_count == 1 && ds_word(address) == 7);
    }
    rewind(record_out);
    uint32_t raw[RECORD_WORDS];
    CHECK(fread(raw, sizeof(raw), 1, record_out) == 1);
    CHECK(raw[1] == CROSS_PUBLISH && raw[2] == pc && raw[3] == 100);
    CHECK(raw[5] == 7 && raw[6] == address && raw[7] == 4);
    CHECK(fgetc(record_out) == EOF);
    fclose(record_out);
    record_out = NULL;
    fns = NULL;
    fn_count = 0;
    entry_bits[bit >> 3] = 0;
    memset(streams, 0, sizeof(streams));
}

static void prepare(uint64_t now, uint64_t end, uint64_t at, int irq)
{
    publication_reset_clock(now, end, irq);
    cpu = publication_cpu();
    cpu->hook_at = publication_hooks;
    memset(streams, 0, sizeof(streams));
    stream_count = 1;
    streams[0].next = 1;
    event = (Record){0, CROSS_PUBLISH, 0x020bb16e, (uint32_t) at, (uint32_t) (at >> 32), 1, {0x021f6f70, 4, 0, 0}, 0};
    records = &event;
    record_count = 1;
    running = replaying = 1;
    recording = diverged = record_ended = 0;
    publications = replay_events = 0;
    irq_visits = 0;
    irq_shift_expected = -1;
    CHECK(bus_write(0x021f6f70u, 4, 0));
    CHECK(bus_write(THREAD_INFO_CURRENT, 4, 0));
    native_publish_hook = publish_word;
}

static void unchanged_on_failure(void)
{
    if (ds_word(0x021f6f70u) != 0 || publications != 0) {
        _Exit(98);
    }
    fputs("Rejected before publishing or copying the expected value\n", stderr);
}

int main(int argc, char **argv)
{
    CHECK(memory_init() == 0);
    entry_bits = calloc((ENTRY_END - ENTRY_BASE) / 16, 1);
    CHECK(entry_bits != NULL);
    verify_recording(0x020bb090, 0xfc, 0x020bb16e, 0x021f6f70, 0x6008); /* str r0, [r1] */
    verify_recording(0x020ba340, 0x1c, 0x020ba348, 0x021f8acc, 0x61ca); /* str r2, [r1, #0x1c] */
    if (argc > 1 && strcmp(argv[1], "old-boundary") == 0) {
        return publication_nested_return(1);
    }
    if (argc > 1 && strcmp(argv[1], "old-shift") == 0) {
        prepare(500, 512, 520, 1);
        CHECK(bus_write(0x021f8accu, 4, 1));
        irq_shift_expected = 0;
        /* The former gradient-only boundary leaves the shift unpublished
         * throughout this wait. The IRQ must catch the stale selector. */
        idle_until(520);
        return 2;
    }
    if (argc > 1) {
        prepare(100, 512, 100, 0);
        CHECK(atexit(unchanged_on_failure) == 0);
        uint32_t pc = 0x020bb16e, address = 0x021f6f70, value = 1;
        if (strcmp(argv[1], "value") == 0) {
            value = 0;
        } else if (strcmp(argv[1], "width") == 0) {
            event.args[1] = 2;
        } else if (strcmp(argv[1], "order") == 0) {
            event.kind = CROSS_RETURN;
        } else if (strcmp(argv[1], "pc") == 0) {
            pc += 2;
        } else if (strcmp(argv[1], "destination") == 0) {
            address += 4;
        } else if (strcmp(argv[1], "missing") == 0) {
            streams[0].next = 0;
            streams[1].key = STREAM_IRQ;
            streams[1].next = 1;
            stream_count = 2;
        } else if (strcmp(argv[1], "late") == 0) {
            prepare(101, 512, 100, 0);
        } else {
            return 2;
        }
        native_publish_word(pc, (uint32_t *) (uintptr_t) address, value);
        return 2;
    }
    CHECK(publication_nested_return(0) == 0);
    for (unsigned extent = 32; extent <= 512; extent *= 16) {
        for (int delta = -1; delta <= 1; delta++) {
            uint64_t at = 512u + (uint64_t) delta;
            prepare(512 - extent, 512, at, 0);
            native_publish_word(0x020bb16e, (uint32_t *) (uintptr_t) 0x021f6f70, 1);
            CHECK(ds_word(0x021f6f70) == 1 && publications == 1 && streams[0].next == 0);
            CHECK(cpu->steps == at);
            CHECK(publication_advances() == (unsigned) (delta >= 0));
            CHECK(publication_old_seen() == publication_advances());
        }
    }
    prepare(500, 512, 520, 1);
    native_publish_word(0x020bb16e, (uint32_t *) (uintptr_t) 0x021f6f70, 1);
    CHECK(irq_visits == 1 && publication_irq_requested() == 1);
    CHECK(cpu->steps == 520 && publications == 1 && publication_old_seen() == 1);

    /* Compile and execute the real transformed Native source against mapped DS
     * globals. The published selector and buffer contents come from its body. */
    prepare(100, 512, 100, 0);
    CHECK(bus_write(0x021f7274, 2, 0x4210));
    CHECK(bus_write(0x021f7276, 2, 0x4210));
    CHECK(bus_write(0x021f7278, 4, 0));
    CHECK(bus_write(0x021f727c, 4, 191));
    func_020bb090();
    CHECK(publications == 1 && ds_word(0x021f6f70) == 1);
    for (unsigned i = 0; i < 192; i++) {
        CHECK(*(uint16_t *) (uintptr_t) (0x021f6f74 + 0x180 + i * 2) == 0x4210);
    }
    event.check = 0;
    streams[0].next = 1;
    func_020bb090();
    CHECK(publications == 2 && ds_word(0x021f6f70) == 0);
    for (unsigned i = 0; i < 192; i++) {
        CHECK(*(uint16_t *) (uintptr_t) (0x021f6f74 + i * 2) == 0x4210);
    }
    /* HBlank samples a separate line-shift selector while the gradient is
     * still being calculated. Run both real compiled bodies around that IRQ. */
    prepare(500, 512, 520, 1);
    Record sequence[2] = {{0, CROSS_PUBLISH, 0x020ba348, 505, 0, 0, {0x021f8acc, 4, 0, 0}, 2}, event};
    records = sequence;
    record_count = 2;
    CHECK(bus_write(0x021f8accu, 4, 1));
    irq_shift_expected = 0;
    shift_callbacks = 0;
    func_020ba340();
    CHECK(publications == 1 && shift_callbacks == 1 && irq_visits == 1 && streams[0].next == 2);
    func_020bb090();
    CHECK(publications == 2 && streams[0].next == 0 && ds_word(0x021f6f70u) == 1);
    puts("Publication preserves computed data, slice ordering, nested returns, IRQ waits and independent line shifts");
    return 0;
}
