#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include "ItemToPurchase.h"

#include <vector>

using namespace std; 

class ShoppingCart {
    private:
        string _customerName ;
        string _currentDate ; 
        vector < ItemToPurchase > _cartItems ; 

    public:
        ShoppingCart() ;
        ShoppingCart( string n, string d) ;

    

} ;

#endif