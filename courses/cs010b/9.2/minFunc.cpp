#include "minFunc.h"
const int * min(const int arr[], int arrSize) {
    if ( arrSize == 0 || arr == nullptr){
      return nullptr;
    }
    if (arrSize == 1){
        return arr ;
    }

    const int *num = min(arr + 1, arrSize - 1) ;
    
    return *arr < *num ? arr : num ;
}