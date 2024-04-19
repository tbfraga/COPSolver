#include <windows.h>

#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#define IDC_STATIC                -1

// Main Window

#define IDI_SCDL                 101
#define IDI_CLOSE_GRAPH          102


#define IDR_SCDL_MENU            201

#define ID_FILE_PROBLEM_DEFINER         301
#define ID_FILE_BENCHMARK_SCHEDULER     302
#define ID_FILE_CLOSE                   303
#define ID_FILE_EXIT                    304
#define ID_FILE_CREATE_N5               305
#define ID_FILE_SA_CYCLES_NUMBER        306
#define ID_FILE_SA_TSFM_TENURE          307
#define ID_FILE_SA_TSFM_MAXITE          308
#define ID_FILE_SA_TSSM_TENURE          309
#define ID_FILE_SA_TSSM_MAXITE          310
#define ID_FILE_SA_PCFM_MAXITE          311
#define ID_FILE_SA_SPSFM_MPERC          312
#define ID_FILE_SA_SPSSM_MPERC          313
#define ID_FILE_CREATE_GANTT            314
#define ID_FILE_PRINT_TIME_SLOT         315
#define ID_FILE_CPV_POPSIZE             316
#define ID_FILE_CPV_NCYCLES             317

// *** Problem Definer Dialog

#define IDD_PROBLEM_DEFINER             340

// *** Scheduler Dialog

#define IDD_SCDL_BOX                350
#define IDC_SCHEDULER               360
#define IDC_SHOW_NGH_GANTT          361
#define IDC_SENSITIVITY_ANALYSIS    362

// *** Sensibility Analysis Dialog

#define IDD_SENSIBILITY_ANALYSIS    450

#define IDET_INITIAL_VALUE          451
#define IDET_FINAL_VALUE            452
#define IDET_INCREASE_VALUE         453
#define IDET_REPETITIONS_NUMBER     454

#define IDC_SUM                     455
#define IDC_MULTIPLICATION          456
#define IDC_EXPONENT                457

#define IDC_PRINT_ALL               458
#define IDC_PRINT_BEST              459

#define IDC_NO_CONVERGENCE_ANALYSIS 460
#define IDC_BY_CYCLE                461
#define IDC_BY_ITERATION            462

#define IDC_NO_EXTRA_STOP_CRITERION 463
#define IDC_BEST_MAKESPAN_FOUND     464


// *** Set Population Size Dialog

#define IDD_SET_POPULATION_SIZE     470

// *** Set Number of Cycles Dialog

#define IDD_SET_CYCLES_NUMBER       471


// Benchmark definitions

#define IDCB_BCMK_KIND           701
#define IDCB_BCMK_CLASS          702
#define IDCB_BCMK                703

// Solution modes

#define IDC_OPTIMALE             801
#define IDC_ANALITICAL           802
#define IDC_VISUAL               803

// Solving method definitions

#define IDCB_METHOD_MODE         901
#define IDCB_HYBRID_MODEL        902
#define IDCB_METHOD_01           903
#define IDCB_METHOD_02           904
#define IDCB_METHOD_03           905

// Problem specifications

#define IDSC_PROBLEM_NAME       1101
#define IDSC_PROBLEM_KIND       1102
#define IDSC_JOB_NUMBER         1103
#define IDSC_MCN_NUMBER         1104
#define IDSC_BEST_MKP_KNOW      1105

// Final results

#define IDSC_PREVIOUS_MAKESPAN  1106
#define IDSC_MAKESPAN           1107
#define IDSC_COPUTING_TIME      1108
#define IDSC_SOLUTIONS_EVAL     1109

// Method specifications

#define IDSC_METHOD             1110
#define IDET_POPULATION_SIZE    1111
#define IDSC_INITIAL_SOLUTION   1112
#define IDCB_INITIAL_SOLUTION   1113
#define IDCB_SOLUTION_INDEX     1114
#define IDET_CYCLES_NUMBER      1115

#define IDGB_METHOD_1           1130
#define IDGB_METHOD_2           1140
#define IDGB_METHOD_3           1150

// *** First Taboo Search dialog

#define IDC_SHOW_GANTT              1291

#define IDD_TABOO_SEARCH_1      1200

#define IDCB_TS_INITIAL_SOLUTION    1201
#define IDCB_TS01_CRITICAL_PATH     1202
#define IDCB_TS01_NGH_METHOD        1203
#define IDET_TS01_TENURE            1204
#define IDET_TS01_MAXITE            1205

#define IDD_TABOO_SEARCH_2      1300
#define IDD_TABOO_SEARCH_3      1400

// *** First Particle Colission Dialog

#define IDD_PARTICLE_COLLISION_01       1500

#define IDCB_PC01_PERTURBATION_METHOD   1501
#define IDCB_PC01_EXPLOITATION_METHOD   1502
#define IDET_PC01_MAXITE                1503

// *** Taboo Search Dialog for Particle Collision

#define IDD_TABOO_SEARCH_PC             1600

// *** Parallel Taboo Search Dialog 1

#define IDD_PARALLEL_TABOO_SEARCH_01    1700

#define IDCB_PTS_INITIAL_SOLUTION   1701
#define IDET_PTS01_POPULATION_SIZE  1702
#define IDCB_PTS01_CRITICAL_PATH    1703
#define IDCB_PTS01_NGH_METHOD       1704
#define IDET_PTS01_TENURE           1705
#define IDET_PTS01_MAXITE           1706

// *** Parallel Taboo Search Dialog 2

#define IDD_PARALLEL_TABOO_SEARCH_02    1800

#define IDET_PTS02_POPULATION_SIZE  1801
#define IDCB_PTS02_CRITICAL_PATH    1802
#define IDCB_PTS02_NGH_METHOD       1803
#define IDET_PTS02_TENURE           1804
#define IDET_PTS02_MAXITE           1805

// *** Parallel Taboo Search Dialog 3

#define IDD_PARALLEL_TABOO_SEARCH_03    1900

#define IDET_PTS03_POPULATION_SIZE  1901
#define IDCB_PTS03_CRITICAL_PATH    1902
#define IDCB_PTS03_NGH_METHOD       1903
#define IDET_PTS03_TENURE           1904
#define IDET_PTS03_MAXITE           1905

// *** First Particle Colission Dialog

#define IDD_PARALLEL_PARTICLE_COLLISION_01       2000

// *** First Similar Particle Swarm dialog

#define IDD_PARTICLE_SWARM_01   2400

#define IDCB_PS_INITIAL_SOLUTION    2401
#define IDET_PS01_POPULATION_SIZE   2402
#define IDCB_PS01_CROSSOVER_METHOD  2403
#define IDCB_PS01_MUTATION_METHOD   2404
#define IDET_PS01_MUTATION_PERCENT  2405
#define IDET_PS01_MAXITE            2406

// *** Second Similar Particle Swarm dialog

#define IDD_PARTICLE_SWARM_02   2500

#define IDET_PS02_POPULATION_SIZE   2501
#define IDCB_PS02_CROSSOVER_METHOD  2502
#define IDCB_PS02_MUTATION_METHOD   2503
#define IDET_PS02_MUTATION_PERCENT  2504
#define IDET_PS02_MAXITE            2505

// *** Third Similar Particle Swarm dialog

#define IDD_PARTICLE_SWARM_03   2600

#define IDET_PS03_POPULATION_SIZE   2601
#define IDCB_PS03_CROSSOVER_METHOD  2602
#define IDCB_PS03_MUTATION_METHOD   2603
#define IDET_PS03_MUTATION_PERCENT  2604
#define IDET_PS03_MAXITE            2605

// *** Gantt solution representation dialog

#define IDD_SOLUTION_GANTT          2700

#define IDD_SOLUTION_GANTT_VECTOR   2800

// *** Message dialog

#define IDD_WAIT_MESSAGE            2900

#endif // RESOURCE_H_INCLUDED
