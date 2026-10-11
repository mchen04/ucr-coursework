#include <iostream>
using namespace std ;

#include "ShoppingCart.h"

ShoppingCart::ShoppingCart() {
    _customerName = "none" ;
    _currentDate = "January 1, 2016" ;
}

ShoppingCart::ShoppingCart( string n, string d) {
    _customerName = n ;
    _currentDate = d ;
}

string ShoppingCart::customerName() const{
    return _customerName ;
}

string ShoppingCart::date() const{
    return _currentDate ;
}

void ShoppingCart::addItem(ItemToPurchase i){
    _cartItems.push_back(i) ;
}

void ShoppingCart::removeItem( string n ) {

    bool InCart = false ;

    for (int i = 0 ; i < numItemsInCart(); i++ ){
        if ( _cartItems.at(i).name() == n ){
            _cartItems.erase( _cartItems.begin() + i ) ;
            InCart = true ;
        }
    }

    if ( !InCart ){
        cout << "Item not found in cart. Nothing removed." << endl ;
    } 
}

void ShoppingCart::modifyItem(ItemToPurchase item) {

    bool InCart = false ;

    for (int i = 0 ; i < numItemsInCart(); i++ ){
        if ( _cartItems.at(i).name() == item.name() ){
            if (item.quantity() != 0 ) {
                _cartItems.at(i).setQuantity(item.quantity()) ;
            }
            if (item.price() != 0 ) {
                _cartItems.at(i).setPrice(item.price()) ;
            }
            if (item.description() != "none" ) {
                _cartItems.at(i).setDescription(item.description()) ;
            }
            InCart = true ;
        }
    }

    if ( !InCart ){
        cout << "Item not found in cart. Nothing modified." << endl ;
    } 
}

int ShoppingCart::numItemsInCart() const {
    return _cartItems.size() ;
}

int ShoppingCart::costOfCart() const {
    int sum = 0 ;
    for ( int i = 0; i < numItemsInCart(); i++ ){
        sum += ( _cartItems.at(i).price() * _cartItems.at(i).quantity() ) ;
    }
    return sum ;
}

int ShoppingCart::totalQuantity() const {
    int sum = 0 ;
    for ( int i = 0; i < numItemsInCart(); i++ ){
        sum += ( _cartItems.at(i).quantity() ) ;
    }
    return sum ;
}

void ShoppingCart::printTotal() const {

    cout << customerName() << "'s Shopping Cart - " << date() << endl ;
    cout << "Number of Items: " << totalQuantity() << endl << endl ;

    if ( numItemsInCart() == 0 ){
        cout << "SHOPPING CART IS EMPTY" << endl ;
    }

    else {
        for ( int i = 0; i < numItemsInCart(); i++ ){
            cout << _cartItems.at(i).name() << " " << _cartItems.at(i).quantity() << " @ $" << _cartItems.at(i).price() << " = $" << _cartItems.at(i).quantity() * _cartItems.at(i).price() << endl ;
        }
    }

    cout << endl << "Total: $" << costOfCart() << endl << endl ;

}

void ShoppingCart::printDescription() const {
    cout << customerName() << "'s Shopping Cart - " << date() << endl << endl ; 
    cout << "Item Descriptions" << endl ;

    for ( int i = 0; i < numItemsInCart(); i++ ){
        cout << _cartItems.at(i).name() << ": " << _cartItems.at(i).description() << endl ;
    }
    cout << endl ;
}
