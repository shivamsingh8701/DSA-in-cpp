class StockSpanner {
public:

    stack<int> s;              // stores indices
    vector<int> prices;        // stores previous prices

    StockSpanner() {
        
    }
    
    int next(int price) {

        prices.push_back(price);

        int i = prices.size() - 1;

        while (s.size() > 0 && prices[s.top()] <= price) {
            s.pop();
        }

        int ans;

        if (s.size() == 0) {
            ans = i + 1;
        }
        else {
            ans = i - s.top();
        }

        s.push(i);

        return ans;
    }
};