extern struct SampleData lockstep_sample_bass_data;
struct InstrumentPCM instrument_pcm_lockstep_bass = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &lockstep_sample_bass_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x000000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x015029,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x13E350,
};

extern struct SampleData lockstep_sample_step_data;
struct InstrumentPCM instrument_pcm_lockstep_step = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &lockstep_sample_step_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x000000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x034867,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData lockstep_sample_shot_r_data;
struct InstrumentPCM instrument_pcm_lockstep_shot_r = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &lockstep_sample_shot_r_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x000000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x034867,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData lockstep_sample_shot_l_data;
struct InstrumentPCM instrument_pcm_lockstep_shot_l = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &lockstep_sample_shot_l_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x000000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x034867,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern union Instrument inst_bank_47[];
struct InstrumentSubRhythm instrument_rhy_drum47 = {
    /* Type      */ INSTRUMENT_SUB_RHYTHM,
    /* Base Key  */ 36,
    /* Sub-Bank  */ inst_bank_47
};
