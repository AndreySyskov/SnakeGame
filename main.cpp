#include <iostream>
#include <vector>

using namespace std;

enum Element_of_game_field {
        snake,
        frame,
        snake_head,
        food,
        score_string
};

enum Move_direct{
        left,
        right,
        up,
        down
};

void display(Snake snake){
        
}


class Model {
    protected:
    int frame_width;
    int frame_height;
    public:
    //virtual void display() const = 0;
    virtual ~Model() {}
    
};

class GameFieldElement: public Model {
        protected:
        int x;
        int y;
        Element_of_game_field c;
        Move_direct z;
        public:
        GameFieldElement(int x, int y, Element_of_game_field c, Move_direct z) : x(x), y(y), c(c), z(z) {
        }
        
        
};

class GameElement : public GameFieldElement {
protected:
    vector<GameFieldElement*> game_element;
public:
    GameElement(int x, int y, Element_of_game_field c, Move_direct z)
        : GameFieldElement(x, y, c, z) {
        game_element.push_back(this);  // Добавляем себя в вектор
    }

    void addElement(GameFieldElement* element) {
        game_element.push_back(element);
    }

    ~GameElement() {
        for (auto element : game_element) {
            delete element;
        }
    }
};

class Snake: public GameElement{
        public:
        Snake(int frame_width, int frame_height, Move_direct z) : GameElement(frame_width/2, frame_width/2, snake, z){
                addElement(new GameFieldElement(frame_width/2+1, frame_width/2, snake, z));
        }
                


};

int main (){
        Snake snake(10, 0, Move_direct::right);


        return 0;
}

