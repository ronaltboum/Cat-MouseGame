#include "MiniMax.h"
#include <stdlib.h>

typedef struct MiniMaxResult* MiniMaxResultRef;
typedef struct MiniMaxResult MiniMaxResult;

struct MiniMaxResult getBestChild_considering_alpha_beta(void* state, unsigned int maxDepth,
	ListRef (*getChildren) (void* state), FreeFunc freeState,
	int (*evaluate) (void* state), int isMaxPlayer,int alpha, int beta);


struct MiniMaxResult getBestChild(void* state, unsigned int maxDepth,
	ListRef (*getChildren) (void* state), FreeFunc freeState,
	int (*evaluate) (void* state), int isMaxPlayer){

		return getBestChild_considering_alpha_beta
			(state, maxDepth, getChildren, freeState, evaluate, isMaxPlayer,
			MIN_EVALUATION-1, MAX_EVALUATION+1);
}


struct MiniMaxResult getBestChild_considering_alpha_beta(void* state, unsigned int maxDepth,
	ListRef (*getChildren) (void* state), FreeFunc freeState,
	int (*evaluate) (void* state), int isMaxPlayer,int alpha, int beta){

		int childCnt;  
		ListRef Childs;
		ListRef tempChild; 
		
		struct MiniMaxResult tempMiniMaxResult;
		struct MiniMaxResult childMiniMaxResult;

		int state_evaluation=evaluate(state);

		if((maxDepth==0)||(state_evaluation == MAX_EVALUATION) || (state_evaluation == MIN_EVALUATION)) {  
			
			tempMiniMaxResult.value= state_evaluation; 
			return tempMiniMaxResult;
		}
		
		Childs= getChildren(state);    //if getChildren.len ==0  then Childs = NULL
		
		if (isEmpty(Childs) == 1){ 
			tempMiniMaxResult.value = state_evaluation;
			return tempMiniMaxResult; 
		}

		tempChild=Childs;
		childCnt=0;
		
		if (isMaxPlayer == 1){ //it's max player turn
			
			tempMiniMaxResult.value = MIN_EVALUATION - 1; 
			while (tempChild != NULL){ 
				childMiniMaxResult= 
					getBestChild_considering_alpha_beta
					(headData(tempChild),maxDepth - 1, getChildren, freeState, evaluate, 0 , alpha, beta); 
				
				if (childMiniMaxResult.value > tempMiniMaxResult.value){ 
					tempMiniMaxResult.value = childMiniMaxResult.value; 
					tempMiniMaxResult.index = childCnt; //update index of best child
				}

				if (childMiniMaxResult.value>alpha)
					alpha=childMiniMaxResult.value;
			
				if (beta<=alpha){
					//printf("beta value: %d , alpha value: %d\n", beta,alpha);
					break;
				}
			

			childCnt++;
			tempChild = tail(tempChild); 
			} 
		}
		
		else if (isMaxPlayer == 0){ //it's min player turn
			tempMiniMaxResult.value = MAX_EVALUATION + 1;
			
			while (tempChild != NULL){
				
				childMiniMaxResult= getBestChild_considering_alpha_beta
					(headData(tempChild),maxDepth - 1, getChildren, freeState, evaluate, 1 , alpha, beta);
				

				if (childMiniMaxResult.value < tempMiniMaxResult.value){
					tempMiniMaxResult.value = childMiniMaxResult.value;
					tempMiniMaxResult.index = childCnt;	//update index of best child
				}

				if (childMiniMaxResult.value<beta)
					beta=childMiniMaxResult.value;

					if (beta<=alpha){
						//printf("beta value: %d , alpha value: %d\n", beta,alpha);
						break;
					}
				

				childCnt++;
			    tempChild = tail(tempChild);
			} 
		}

		if(Childs != NULL)
			destroyList(Childs, freeState);
		return tempMiniMaxResult;
}