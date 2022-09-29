#ifndef __FSM_H_
#define __FSM_H_

typedef struct fsm fsm_ty;
typedef struct state state_ty;
typedef int(*fptr)(void *);


struct state
{
	int next_state;
	fptr state_func;
};


fsm_ty *FSMCreate(int num_states, int num_events, const state_ty *stt_matrix);


int FSMTransit(fsm_ty *th_, int state, int event, void *param);


void FSMDestroy(fsm_ty *th_);



#endif


