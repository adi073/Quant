#include <iostream>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memeory>
#include <variant>
#include <optional>
#include <tuple>
#include <format>

enum class OrderType{

};

enum class Side{
    Buy,
    Sell
};

using Price = std::int32_t;
using Quantity = std::uint32_t;
using Order_id = std::uint64_t;

// Will be used in some public api's to get info about the state of the order book
struct LevelInfo{
    Price price_;
    Quantity quantity_;
}

using LevelInfo = std::vector<LevelInfo>;

// We want to encapsulate out levelInfo object to represent out sides
// Our order book can have 2 sides 
// Each side has a list of levels and we want to be able to represent the order book level infos

class OrderbookLevelInfos{
// Aggregate internal state of orderbook
    public:
        OrderbookLevelInfos (const LevelInfos &bids, const LevelInfos &ask) : bids_(bids), asks_(asks){}
        
// some public api's
        const LevelInfos &GetBids() const {
            return bids_;
        }
        
        const LevelInfos &GetBids() const{
            return asks_;
        }
    
    private:
        LevelInfo bids_;
        LevelInfo asks_;
};

// Things that will be added to orderbook. Those will be order objects.
class Order{
    public:
        Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity) : 
            orderType_(),
            orderId_(orderId),
            side_(side),
            initialQuantity_(quantity),
            remainingQuantity_(quantity)
            {}
        
        OrderId GetOrderId() const{
            return orderId_;
        }
        
        Price GetPrice() const{
            return price_;
        }

        Side GetSide() const{
            return side_;
        }

        OrderType GetOrderType() const{
            return orderType_;
        }

        Quantity GetInitialQuantity() const{
            return initialQuantity_;
        }

        Quantity GetRemainingQuantity() const{
            return remainingQuantity_;
        }
        
        Quanity GetFilledQuantity() const{
            return GetInitialQuantity() - GetRemainingQuantity();
        }
        
        bool IsFilled() const {return GetRemainingQuantity() == 0;}

        void Fill(Quantity quantity){
            if (quantity > GetRemainingQuantity()){
                throw std::logic_error(std::format("Order ({}) cannot be filled for more than its remaining quantity.", GetOrderId()));
            }
            remainingQuantity_ -= quantity;
        }
    private:
        OrderType orderType_;
        OrderId orderId_;
        Size size_;
        Price price_;
        Quantity initialQuantity;
        Quantity remainingQuantity;
};

// As we are going to store a single order in multiple data structures in an order book 
// we are going to need reference scemantics to make things easier, so we are using order pointer
using OrderPointer = std::shared_pointer<Order>;
using OrderPointers = std::list<OrderPointer>;

class OrderModify{
    public:
        OrderModify(OrderId orderId, Side side, Price price, Quantity quantity) : 
            orderId_(orderId),
            side_(side),
            price_(price), 
            quantity_(quantity)
            {}

        OrderId GetOrderId() const {return orderId_;}
        Side GetSide() const {return side_;}
        Price GetPrice() const {return price_;}
        Quantity GetQuantity const {return quantity_;}
        
// Transform a order that already exists into a new order
        OrderPointer ToOrderPointer(OrderType type) const{
            return std::make_shared<Order>(type, GetOrderId(), GetPrice(), GetQuantity());
        }
    private:
        OrderId orderId_;
        Price price_;
        Side side_;
        Quantity quantity_;
};

struct TradeInfo
{
    OrderId orderId_;
    Price price_;
    Quantity quantity_;
};

class Trade
{
    public:
        Trade(const TradeInfo &bidTrade, const TradeInfo &askTrade) :
            bidTrade_(bidTrade),
            askTrade_(askTrade)
            {}
        const TradeInfo &GetBidTrade() const {return bidTrade_;}
        const TradeInfo &GetAskTrade() const {return adkTrade_;}
    private:
        TradeInfo bidTrade_;
        TradeInfo askTrade_;
}; 

using Trade = std::vector<Trade>;

// Now the actual order book starts
class OrderBook
{
    private:
        struct OrderEntry
        {
            OrderPointer order_{nullptr};
            OrderPointers::iterator location_;
        };

        std::map<Price, OrderPointers, std::greater<Price>> bids_;
        std::map<Price, OrderPointers, std::less<Price>> asks_;
        std::unordered_map<OrderId, OrderEntry> orders_;

        bool CanMatch(Side side, Price price) const
        {
            if (side == Side::buy)
            {
                if (asks_.empty())
                    return False;

                const auto &[bestAsk, _] = 
            }
        }
}


int main(){

}
30:45

























