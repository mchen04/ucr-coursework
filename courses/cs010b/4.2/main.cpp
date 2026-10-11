#include <iostream>
using namespace std ;

#include "ItemToPurchase.h"
#include "ShoppingCart.h"

void printMenu(ShoppingCart currShoppingCart) {
    char user_input ;
    cout << "MENU" << endl ;
    cout << "a - Add item to cart" << endl ;
    cout << "d - Remove item from cart" << endl ;
    cout << "c - Change item quantity" << endl ;
    cout << "i - Output items' descriptions" << endl ;
    cout << "o - Output shopping cart" << endl ;
    cout << "q - Quit" << endl << endl ;

    while (user_input != 'q') {
        if (user_input == 'a' || user_input == 'b' || user_input == 'c' || user_input == 'i' || user_input == 'o' || user_input == 'q' || user_input == 'd'){
            cout << "MENU" << endl ;
            cout << "a - Add item to cart" << endl ;
            cout << "d - Remove item from cart" << endl ;
            cout << "c - Change item quantity" << endl ;
            cout << "i - Output items' descriptions" << endl ;
            cout << "o - Output shopping cart" << endl ;
            cout << "q - Quit" << endl << endl ;
        }


        cout << "Choose an option: " << endl ;
        cin >> user_input ;

        if ( user_input == 'q' ){
            exit(1) ;
        }
        if (user_input == 'd'){
            string remove_name ;
            string dummy ;
            getline (cin, dummy) ;
            cout << endl << "REMOVE ITEM FROM CART" << endl ;
            cout << "Enter name of item to remove: " << endl ;
            getline (cin, remove_name) ;
            currShoppingCart.removeItem( remove_name ) ;
            cout << endl ; 
        }
        if (user_input == 'c'){
            string change_name; 
            int change_quant ;
            string dummy ;

            getline (cin, dummy) ;

            cout << endl << "CHANGE ITEM QUANTITY" << endl ;
            cout << "Enter the item name: " << endl ;
            getline (cin, change_name) ;
            cout << "Enter the new quantity: " << endl ;
            cin >> change_quant ;

            ItemToPurchase new_Item2(change_name, "none", 0, change_quant ) ;
            currShoppingCart.modifyItem(new_Item2) ;
            cout << endl ;

        }
        if (user_input == 'i'){
            cout << endl << "OUTPUT ITEMS' DESCRIPTIONS" << endl ;
            currShoppingCart.printDescription() ;
        }
        if (user_input == 'o'){
            cout << endl << "OUTPUT SHOPPING CART" << endl ;
            currShoppingCart.printTotal() ;
        }
        if (user_input == 'a'){
            string item_name ;
            string item_desc ;
            string dummy ;
            int item_price ;
            int item_quantity ;

            getline(cin, dummy) ;

            cout << endl << "ADD ITEM TO CART" << endl ;
            cout << "Enter the item name: " << endl ;
            getline(cin, item_name) ;
            cout << "Enter the item description: " << endl ;
            getline(cin, item_desc) ;
            cout << "Enter the item price: " << endl ;
            cin >> item_price ; 
            cout << "Enter the item quantity: " << endl ;
            cin >> item_quantity ;
            ItemToPurchase new_Item1( item_name, item_desc, item_price, item_quantity ) ;
            currShoppingCart.addItem(new_Item1) ;

            cout << endl ;
        }
    }
}

int main(){
    string cust_name ;
    string cust_date ;

    cout << "Enter customer's name: " ;
    getline(cin, cust_name ) ;
    cout << endl ;
    cout << "Enter today's date: " ;
    getline(cin, cust_date ) ;

    ShoppingCart currShoppingCart(cust_name, cust_date ) ;
    cout << endl << endl ;

    cout << "Customer name: " << currShoppingCart.customerName() << endl ;
    cout << "Today's date: " << currShoppingCart.date() << endl << endl ;

    printMenu(currShoppingCart) ;
}




