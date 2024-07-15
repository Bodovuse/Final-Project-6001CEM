#include <iostream>
#include <vector>
#include <D:\Uni\6000CEM individual project\6001Testing\goap-cpp\include\goap\goap.hpp>

struct marketState {
    bool isProfitMarginMet {false};
    bool haveStock{false};//
    bool isStockEmpty {true};
    bool isOfferAccepted {false};//
    bool isInventoryFull {false};//
    bool haveInventorySpace {true};//
    bool isBudgetSpent {false};
    bool offerMade {false};//

};


bool operator==(const marketState& b, const marketState& a)
{
    return a.offerMade == b.offerMade && a.haveStock == b.haveStock && a.isInventoryFull == b.isInventoryFull && a.haveInventorySpace == b.haveInventorySpace
    &&a.isOfferAccepted==b.isOfferAccepted && a.haveInventorySpace==b.haveInventorySpace;
}



struct ProfitGoal : goap::Goal<marketState> {
    int distance_to(const marketState& state) const override
    {
        return goap::Distance().shouldBeTrue(state.isProfitMarginMet);
    }
};

struct ItemGoal : goap::Goal<marketState> {
    int distance_to(const marketState& state) const override
    {
        return goap::Distance().shouldBeTrue(state.isInventoryFull);
    }
};

struct offerGoal : goap::Goal<marketState>{
int distance_to(const marketState& state) const override
    {
        return goap::Distance().shouldBeTrue(state.offerMade);
    }
};

class Transaction : public goap::Action<marketState>{
public:


    bool can_run(const marketState& state) override
    {
        return  state.isOfferAccepted ;
    }

    void plan_effects(marketState& state) override
    {
        state.haveStock = false;
        state.isStockEmpty = true;
        state.isProfitMarginMet = true;
        state.haveInventorySpace = false; 
        state.isInventoryFull = true;
        
    }

    bool execute(marketState& state) override
    {

        std::cout << "recieved ammount " << std:: endl;
        state.haveStock = false;
        state.isStockEmpty = true;
        state.isProfitMarginMet = true; 
        state.haveInventorySpace = false;
        state.isInventoryFull = true;

        return true;
    }
};

class AcceptOffer : public goap::Action<marketState>{
public:


    bool can_run(const marketState& state) override
    {
        return  state.haveInventorySpace;
    }

    void plan_effects(marketState& state) override
    {
        
        state.isOfferAccepted = true; 
        
    }

    bool execute(marketState& state) override
    {

        std::cout << "accepting Offer " << std:: endl;
        
        state.isOfferAccepted = true; 

        return true;
    }
};

class MakeOffer : public goap::Action<marketState>{
public:


    bool can_run(const marketState& state) override
    {
        return state.haveStock;
    }

    void plan_effects(marketState& state) override
    {
        state.offerMade = true ;
        
    }

    bool execute(marketState& state) override
    {

        std::cout << "Making Offer " << std:: endl;
        state.offerMade = true ;

        return true;
    }
};


class RejectOffer : public goap::Action<marketState> {
public:
    bool can_run(const marketState& state) override
    {
        return state.haveStock ;
    }

    void plan_effects(marketState& state) override
    {
        state.isOfferAccepted = false; 
    }

    bool execute(marketState& state) override
    {
        std::cout << "Rejecting Offer!" << std::endl;
        state.isOfferAccepted = false;
        
        return true;
    }
};


class GetStock : public goap::Action<marketState> {
public:
    bool can_run(const marketState& state) override
    {
        return true;
    }

    void plan_effects(marketState& state) override
    {
        state.haveStock = true;
        state.isStockEmpty = false;
    }

    bool execute(marketState& state) override
    {
        std::cout << "Getting more Stock!" << std::endl;
        state.haveStock = true;
        state.isStockEmpty = false;
        
        return true;
    }
};

int Buyer()
{
    AcceptOffer offer_accepted;
    RejectOffer offer_rejected;
    Transaction transaction;
    
    
    ItemGoal goal;
    marketState state;

    std::vector<goap::Action<marketState>*> actions{&offer_rejected, &offer_accepted, &transaction};

    goap::Planner<marketState> planner;

    constexpr int max_path_len = 10;
    goap::Action<marketState>* path[max_path_len];

    auto len = planner.plan(state, goal, actions.data(), actions.size(), path, max_path_len);

    if (len == goap::kErrorNoPathFound) {
        std::cout << "Could not find a plan for Buyer!" << std::endl;
        return 1;
    }

    if (len == goap::kErrorNotEnoughMemory) {
        std::cout << "Not enough memory reserved to explore all options for Buyer!" << std::endl;
        return 1;
    }

    // Execute all the steps in the plan
    for (int i = 0; i < len; i++) {
        path[i]->execute(state);
    }

    return 0;
};

int Seller()
{
    MakeOffer make_offer;
    GetStock get_stock;
    Transaction transaction;
    ProfitGoal goal;
    offerGoal offer_goal;
    marketState state;

    std::vector<goap::Action<marketState>*> actions{&make_offer, &get_stock, &transaction};

    goap::Planner<marketState> planner;

    constexpr int max_path_len = 10;
    goap::Action<marketState>* path[max_path_len];

    auto len = planner.plan(state, offer_goal, actions.data(), actions.size(), path, max_path_len);

    if (len == goap::kErrorNoPathFound) {
        std::cout << "Could not find a plan for Seller!" << std::endl;
        return 1;
    }

    if (len == goap::kErrorNotEnoughMemory) {
        std::cout << "Not enough memory reserved to explore all options for Seller!" << std::endl;
        return 1;
    }

    // Execute all the steps in the plan
    for (int i = 0; i < len; i++) {
        path[i]->execute(state);
    }

    return 0;
};

int BuyerRecursion(int n){
    if (n>1){
        return Buyer();
    }
    else{
        return 0;
    }
    
    
};

int SellerRecursion(int n){
    if (n>1){
        return Seller();
    }
    else{
        return 0;
    }
};

int AgentRecursion(int n){
    if (n>1){
        Seller();
        Buyer();
        return 1;
    }
    else{
        return 0;
    }
};

int main()
{
    
    
    //SellerRecursion(3);
    //BuyerRecursion(3);
    AgentRecursion(3);

};
