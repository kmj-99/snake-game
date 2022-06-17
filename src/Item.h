class Item{
    public:
        int x;
        int y;
        bool itemType;
        int lifeTime;
        Item(int x, int y, bool itemType, int lifeTime = 5) : x(x), y(y), itemType(itemType), lifeTime(lifeTime) {};

};
