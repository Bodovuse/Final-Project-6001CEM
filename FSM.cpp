#include <iostream>
#include <string>

using namespace std;

// Define states for Buyer
enum class BuyerState {
    WAITING,
    OFFER_RECEIVED,
    TRANSACTION_COMPLETED
};

// Define states for Seller
enum class SellerState {
    WAITING,
    OFFER_MADE,
    STOCK_REPLENISHED
};

// Define events for Buyer
enum class BuyerEvent {
    ACCEPT_OFFER,
    REJECT_OFFER,
    MAKE_TRANSACTION
};

// Define events for Seller
enum class SellerEvent {
    MAKE_OFFER,
    GET_STOCK
};

class Buyer {
public:
    void processEvent(BuyerEvent event);
private:
    BuyerState currentState = BuyerState::WAITING;
};

class Seller {
public:
    void processEvent(SellerEvent event);
private:
    SellerState currentState = SellerState::WAITING;
};

void Buyer::processEvent(BuyerEvent event) {
    switch (currentState) {
        case BuyerState::WAITING:
            if (event == BuyerEvent::ACCEPT_OFFER) {
                currentState = BuyerState::TRANSACTION_COMPLETED;
                cout << "Transaction completed!" << endl;
            } else if (event == BuyerEvent::REJECT_OFFER) {
                cout << "Offer rejected." << endl;
            }
            break;
        case BuyerState::OFFER_RECEIVED:
            if (event == BuyerEvent::MAKE_TRANSACTION) {
                currentState = BuyerState::TRANSACTION_COMPLETED;
                cout << "Transaction completed!" << endl;
            }
            break;
        default:
            cout << "Invalid state for Buyer!" << endl;
            break;
    }
}

void Seller::processEvent(SellerEvent event) {
    switch (currentState) {
        case SellerState::WAITING:
            if (event == SellerEvent::MAKE_OFFER) {
                currentState = SellerState::OFFER_MADE;
                cout << "Offer made." << endl;
            } else if (event == SellerEvent::GET_STOCK) {
                currentState = SellerState::STOCK_REPLENISHED;
                cout << "Stock replenished." << endl;
            }
            break;
        default:
            cout << "Invalid state for Seller!" << endl;
            break;
    }
}

int main() {
    Buyer buyer;
    Seller seller;

    // Simulate interaction
    seller.processEvent(SellerEvent::MAKE_OFFER);
    buyer.processEvent(BuyerEvent::REJECT_OFFER);
    seller.processEvent(SellerEvent::GET_STOCK);
    buyer.processEvent(BuyerEvent::MAKE_TRANSACTION);

    return 0;
}