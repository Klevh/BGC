#include "BGC.h"

cell_t * _BGCollector = NULL;

void * mallocBGC(size_t size){
  cell_t * newCell;
  void   * result = NULL;

  if(size){
    newCell = malloc(sizeof(*newCell));
    if(newCell){
      newCell->object=malloc(size);
      if(newCell->object){
	newCell->size=size;
	newCell->next=_BGCollector;
	_BGCollector=newCell;
	result=newCell->object;
      }else{
	free(newCell);
      }
    }
  }
  
  return result;
}



int freeBGC(void * object){
  cell_t ** current=&_BGCollector;
  cell_t  * removed;
  int       error = 1;

  while(*current && (*current)->object!=object){
    current=&((*current)->next);
  }

  if(*current){
    removed = *current;
    *current=removed->next;
    free(removed->object);
    free(removed);
    error = 0;
  }

  return error;
}



void * reallocBGC(void * object,size_t size){
  cell_t ** cell=NULL;
  cell_t  * current = NULL;
  void    * result = NULL;

  if(size){
    if(object){
      cell=&_BGCollector;
      while(*cell && (*cell)->object!=object){
	cell=&((*cell)->next);
      }
      current = *cell;
    }
    if(!current){
      result = malloc(size);
      if(result){
	current=malloc(sizeof(*current));
	if(current){
	  current->size=size;
	  current->object=result;
	  current->next=_BGCollector;
	  _BGCollector=current;
	}else{
	  free(result);
	  result=NULL;
	}
      }
    }else{
      result=realloc(current->object,size);
      if(result){
	current->object=result;
      }
    }
  }
  
  return result;
}



void * callocBGC(size_t nmemb, size_t size){
  cell_t * newCell;
  void   * result = NULL;

  if(size && nmemb){
    newCell = malloc(sizeof(*newCell));
    if(newCell){
      newCell->object=calloc(nmemb,size);
      if(newCell->object){
	newCell->size=size*nmemb;
	newCell->next=_BGCollector;
	_BGCollector=newCell;
	result=newCell->object;
      }else{
	free(newCell);
      }
    }
  }
  
  return result;
}



int isAllocatedBGC(void * object){
  cell_t * current = _BGCollector;

  while(current && current->object!=object){
    current=current->next;
  }

  return current!=NULL;
}



void cleanBGC(){
  cell_t * current = _BGCollector;
  cell_t * removed;

  while(current){
    removed = current;
    current=current->next;
    free(removed->object);
    free(removed);
  }
  _BGCollector=NULL;
}
