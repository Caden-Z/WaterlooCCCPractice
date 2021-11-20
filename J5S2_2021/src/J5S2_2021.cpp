#include <iostream>
#include <vector>
#include <string>
#include <climits>

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
void EnterModification(EType&, uint32_t&, const uint32_t&, const uint32_t&);
uint32_t Clamp(const uint32_t&, const uint32_t&, const uint32_t&);
uint32_t Preview(const std::vector<std::vector<bool>>&);

int main ()
{
    // get M from console input
    uint32_t m;
    Enter(m, "M");

    // get N from console input
    uint32_t n;
    Enter(n, "N");
    
    // get K from console input
    uint32_t k;
    Enter(k, "K");

    /* the table? dunno
    if (m == 1 && n == 1 || n <= 100 || m <= 100)
    {
        k = Clamp(k, 1, 100);
    } else if (m <= 5000000 && n <= 5000000)
    {
        k = Clamp(k, 1, 1000000);
    }
    */

    // shouldn't happen but just for safety
    if (m == NULL || n == NULL || k == NULL) return 1;
    
    // construct the canvas, using vector as MSVS compiler apparently does not support variable length array
    // pre-defining size to avoid slow code
    // filling it up with EColor::Black
    std::vector<std::vector<bool>> canvas(m, std::vector<bool>(n, Black));
    
    // get row/column modification
    for (int i = 0; i < k; i++)
    {
        EType type;
        uint32_t value;
        
        EnterModification(type, value, m, n);

        switch (type)
        {
        case Row:
            for (int i = 0; i < canvas[value].size(); i++)
            {
                // flip
                canvas[value][i] = !canvas[value][i];
            }
            break;
        case Column:
            for (int i = 0; i < canvas.size(); i++)
            {
                // flip
                canvas[i][value] = !canvas[i][value];
            }
            break;
        }
    }
    
    std::cout << Preview(canvas) << std::endl;
    
    return 0;
}

void Enter(uint32_t& stored, const char* ID)
{
    // notification message
    std::cout<<"Please enter " << ID << std::endl;
    
    // create cache pointer
    int32_t* cache = new int32_t();
    std::cin >> *cache;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
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

void EnterModification(EType& type, uint32_t& stored, const uint32_t& M, const uint32_t& N)
{
    // create cache pointer

    std::string cache;

    // redo if the first character is not R or C
    do
    {
        std::getline(std::cin, cache);

        if (cache.empty()) return;
    
        if (cache[0] == 'R')
        {
            type = Row;
        } else if (cache[0] == 'C')
        {
            type = Column;
        }
    } while (cache[0] != 'R' && cache[0] != 'C');

    // TODO: bad code
    std::string string = { cache[2] };
    
    // if input is invalid, re-do this
    switch (type)
    {
    case Row:
        if (std::stoi(string) > M)
        {
            EnterModification(type, stored, M, N);
            return;
        }
        break;
    case Column:
        if (std::stoi(string) > N)
        {
            EnterModification(type, stored, M, N);
            return;
        }
        break;
    }
    
    
    // set stored to input
    stored = std::stoi(string) - 1;
}

uint32_t Clamp(const uint32_t& num, const uint32_t& min, const uint32_t& max)
{
    if (min >= max) std::cout << "Yo WTF bro your min is bigger or is max" << std::endl;
    if (num < min) return min;
    if (num > max) return max;

    return num;
}

uint32_t Preview(const std::vector<std::vector<bool>>& canvas)
{
    uint32_t gold_cells = 0;
    for (std::vector<bool> row : canvas)
    {
        for (bool cell : row)
        {
            if (cell == Gold)
            {
                gold_cells++;
                std::cout << "G";
            } else
            {
                std::cout << "B";
            }
        }
        std::cout << std::endl;
    }

    return gold_cells;
}