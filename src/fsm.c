#include <stdlib.h>

#include "fsm.h"


struct fsm
{
	const state_ty *stt_matrix;
	int num_states;
	int num_events;
};


fsm_ty *FSMCreate(int num_states, int num_events, const state_ty *stt_matrix)
{
	/* malloc struct for fsm */
	fsm_ty *fsm = (fsm_ty *)malloc(sizeof(fsm_ty));
	
	if (fsm == NULL)
	{
		return NULL;
	}
	
	/* init fields */
	
	/* matrix */
	fsm->stt_matrix = stt_matrix;
	
	/* num_states */
	fsm->num_states = num_states;
	
	/* num_events */
	fsm->num_events = num_events;
	
	/* return fsm */
	return fsm;
}


int FSMTransit(fsm_ty *th_, int state, int event, void *param)
{
	/* go to  matrix[state][event] */
	const state_ty *curr = th_->stt_matrix + (state * th_->num_events) + event;
	
	/* call the func from there with param */
	curr->state_func(param);
	
	/* return the next state from the current state task */
	return curr->next_state;
}


void FSMDestroy(fsm_ty *th_)
{
	/* free the fsm struct */
	free(th_);
}
