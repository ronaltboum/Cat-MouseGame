
#include <stdlib.h>
#include "ListUtils.h"

typedef struct List
{
	void* data;
	ListRef next;
}List;

ListRef newList(void* headData){
	ListRef list = (ListRef)malloc(sizeof(List)); 
	if (list == NULL)
		return NULL;
	list->data = headData; 
	list->next = NULL; 
	return list;
}

void* headData(ListRef list){
	if (list == NULL) 
		return NULL;
	return list->data; 
}

ListRef tail(ListRef list){
	if ((list == NULL) || (list->next == NULL)) 
		return NULL;
	return list->next; 
}

ListRef append(ListRef list, void* data){
	
	ListRef subList;

	if (data == NULL) 
		return NULL;

	if (list->data == NULL){
		list->data = data;
		return list;
	}

	subList = newList(data);
	if (subList == NULL)
		return NULL;
	
	while (list->next != NULL)
		list = list->next;
	
	list->next = subList;
	return subList;
}


void destroyList(ListRef list, FreeFunc freeData){
	ListRef first_free_list = list; 
	ListRef old_free_list = list; 

	while (first_free_list != NULL){
		freeData(first_free_list->data); 
		first_free_list = first_free_list->next; 
		free(old_free_list); 
		old_free_list = first_free_list; 
	}
}


int isEmpty(ListRef list){
	if (list->data == NULL)
		return 1;
	return 0;
}
