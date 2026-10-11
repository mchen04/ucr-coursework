#include <iostream>
using namespace std ;

#include "ItemToPurchase.h"

ItemToPurchase::ItemToPurchase(){
    _name = "none" ;
    _price = 0 ;
    _quantity = 0 ;
    _description = "none" ;
}

ItemToPurchase::ItemToPurchase( string n, string d, int p, int q ){
    _name = n ;
    _price = p ;
    _quantity = q ;
    _description = d ;
}

void ItemToPurchase::setName( string n ) {
    _name = n ;
}

string ItemToPurchase::name() const {
    return _name ;
}
        
void ItemToPurchase::setPrice ( int p ) {
    _price = p ;
}

int ItemToPurchase::price() const {
    return _price ;
}

void ItemToPurchase::setQuantity ( int q ) {
    _quantity = q ;
}

int ItemToPurchase::quantity() const {
    return _quantity ;
}

void ItemToPurchase::setDescription( string d ) {
    _description = d ;
}

string ItemToPurchase::description() const {
    return _description ;
}
        
void ItemToPurchase::printItemCost() const {
    cout << _name << " " << _quantity << " @ $" << _price << " = $" << (_quantity * _price) << endl ;
}

void ItemToPurchase::printItemDescription() const {
    cout << _name << ": " << _description << "." << endl ;
}