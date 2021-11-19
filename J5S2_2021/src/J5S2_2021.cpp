#include <iostream>

enum EColor
{
    Black = false,
    Gold = true
};

enum EType
{
    Row = 0,
    Column = 1
};

void Enter(uint32_t&, const char*);
void EnterModification(EType& type, uint32_t& stored, uint32_t& limit);

int main ()
{
    // get M from console input
    uint32_t M;
    Enter(M, "M");

    // get N from console input
    uint32_t N;
    Enter(N, "N");
    
    // get K from console input
    uint32_t K;
    Enter(K, "K");

    // construct the canvas
    bool canvas[M][N];

    // fill canvas
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            canvas[i][j] = Black;
        }
    }
    
    // get row/column modification
    for (int i = 0; i < K; i++)
    {
        EType type;
        uint32_t value;
        
        
        EnterModification(type, value, M);
        
        std::cout << type << std::endl;
        std::cout << value << std::endl;
    }
    
    return 0;
}

void Enter(uint32_t& stored, const char* ID)
{
    // notification message
    std::cout<<"Please enter " << ID << std::endl;
    
    // create cache pointer
    int32_t* cache = new int32_t();
    std::cin >> *cache;
    
    // safety check
    if (cache == nullptr) return;
    
    // if input is invalid, re-do this
    if (*cache <= 0)
    {
        Enter(stored, ID);
        return;
    }
    
    // set stored to input
    stored = *cache;
    
    // free memory
    delete cache;
}

void EnterModification(EType& type, uint32_t& stored, uint32_t& limit)
{
    // create cache pointer
    char* cache;
    std::cin >> cache;
    
    // safety check
    if (cache == nullptr) return;
    
    if (cache[0] == 'R')
    {
        type = Row;
    } else
    {
        type = Column;
    }
    
    cache[0] = '\0';
    
    // if input is invalid, re-do this
    if (atoi(cache) < limit)
    {
        EnterModification(type, stored, limit);
        return;
    }
    
    // set stored to input
    stored = atoi(cache);
}