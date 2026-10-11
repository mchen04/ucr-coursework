#ifndef ITEMTOPURCHASE_H
#define ITEMTOPURCHASE_H

class ItemToPurchase {
    public:
        ItemToPurchase() ;
        ItemToPurchase( string n, string d, int p, int q ) ;
        void setName( string n ) ;
        string name() const;
        void setPrice ( int p ) ;
        int price() const;
        void setQuantity ( int q) ;
        int quantity() const;
        void setDescription( string d ) ;
        string description() const ;
        void printItemCost() const ;
        void printItemDescription() const ;
    private:
        string _name ;
        int _price ;
        int _quantity ;
        string _description ;
} ;

#endif