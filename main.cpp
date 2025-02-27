
#include <iostream>
#include <vector>
#include <chrono> // для таймера задержки
#include <thread> // для таймера задержки
#include <cstdlib> // для очистки экрана
#include <ncurses.h> // библиотека для неприрывного ввода
#include <cstring> // для strlen
#include <random> // случайные числа для генератора еды

using namespace std;

enum class GameFieldElement {
    Empty,
    Snake,
    Food, 

};

enum class Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NO
};

class Point{
    public:
    Point(int x, int y, GameFieldElement cell, Direction direction): x(x), y(y), cell(cell), direction(direction) {
       
    }

    int get_x(){
        return x;
    }

    int get_y(){
        return y;
    }

    void set_x(int new_x) { 
        x = new_x; }

    void set_y(int new_y) { 
        y = new_y; }

    GameFieldElement get_cell(){
        return cell;
    }

    Direction get_direction(){
        return direction;
    }

    void set_direction(Direction new_derection){
        direction=new_derection;
    }
    
    private:
    int x;
    int y;
    GameFieldElement cell;
    Direction direction;
   };

class GameElement {
    public:
    GameElement(){};

    void add_point(int x, int y, GameFieldElement cell, Direction dir) {
        points_.push_back(Point(x, y, cell, dir));

    }

    void add_point(Point point){
        points_.push_back(point);
        
    }

    vector <Point>& get_GameElement(){
        return points_;
    }

    private:
    vector <Point> points_;
};

class Snake : public GameElement {
    public:
    Snake() {
        current_direction_of_snake = Direction::RIGHT;
    };

    void move(){
      //cout<<"inside move"<<endl;
        auto& snake=get_GameElement();
        auto& head_snake=snake[0];
        int head_x = snake[0].get_x();
        int head_y = snake[0].get_y();
        
           
            
            switch(current_direction_of_snake){
                case(Direction::LEFT) : head_snake.set_y(head_snake.get_y()-1); break;
                case(Direction::RIGHT) : head_snake.set_y(head_snake.get_y()+1); break;
                case(Direction::UP) : head_snake.set_x(head_snake.get_x()-1); break;
                case(Direction::DOWN) : head_snake.set_x(head_snake.get_x()+1); break;
            }

           // Model.test_collision_food_or_body();
        
            
        for (int i=1; i<snake.size(); i++){
                int temp_x = snake[i].get_x();
                int temp_y = snake[i].get_y();
                snake[i].set_x(head_x);
                snake[i].set_y(head_y);
                head_x=temp_x;
                head_y=temp_y;
        }
                
    }
    void grow(){
        
    };

    

    void set_direction(Direction new_direction){
    current_direction_of_snake=new_direction;
   }

    Direction get_current_direction(){
    return current_direction_of_snake;
   }

private:
Direction current_direction_of_snake; 



};

class Food:public GameElement{
    public:
    Food(){}

};

class Model {
   public:
   Model(int w, int h) : 
    
   w(w), // столбцы cols ширина
   h(h), // строки rows высота
     
   output_array(h, vector<GameFieldElement>(w, GameFieldElement::Empty))
   
   {
    // Создаем змею
    snake.add_point(h/2, w/2, GameFieldElement::Snake, Direction::RIGHT); // Установка змеи в середину поля
    snake.add_point(h/2, w/2-1, GameFieldElement::Snake, Direction::RIGHT);
    snake.add_point(h/2, w/2-2, GameFieldElement::Snake, Direction::RIGHT);
    snake.add_point(h/2, w/2-3, GameFieldElement::Snake, Direction::RIGHT);
    snake.add_point(h/2, w/2-4, GameFieldElement::Snake, Direction::RIGHT);

    // Создаем еду

    food.add_point(rand_x_not_in_snake(), rand_y_not_in_snake(), GameFieldElement::Food, Direction::NO); // Версия с одной едой на поле

   }


   int get_w(){
    return w;
   }

   int get_h(){
    return h;
   }


    Snake& get_Snake(){
        return snake;
    }

    Food& get_Food(){
        return food;
    }

    void update(){
       // cout<<"Inside update"<<endl;
        refresh_array();

        snake.move();
        trans_snake_to_array();
        trans_food_to_array();
        
        
    }

    void refresh_array(){
        //output_array.clear();
        for (auto& row: output_array){
            for (auto& value : row) {
                value = GameFieldElement::Empty;
            }
        }
    }

    // -------Блок функций, который переводят элементы в массив, нужно сделать универсальную------
    void trans_snake_to_array(){
        //cout<<"Inside trans"<<endl;
        
        for(auto& point_of_game_element : snake.get_GameElement()){
            int x = point_of_game_element.get_x();
            int y = point_of_game_element.get_y();
            output_array[x][y]=GameFieldElement::Snake;
        }

    }

    void trans_food_to_array(){
       // cout<<"Inside trans"<<endl;
        
        for(auto& point_of_game_element : food.get_GameElement()){
            int x = point_of_game_element.get_x();
            int y = point_of_game_element.get_y();
            output_array[x][y]=GameFieldElement::Food;
        }

    }
//-------------Конец блока-----------


    void set_direction(Direction new_direction){
         snake.set_direction(new_direction);
   }

    vector <vector<GameFieldElement>>& get_Output_array(){
        
        
        return output_array;
    }



int rand_x_not_in_snake() {  // Вызов генератора каждый раз - затратен, иногда подвисает, нужно выловить ошибку зависания функции
                             // Одна еда на поле, в противном случае нужно проверять, нет ли попадания генератора на еду
    mt19937 generator(random_device{}());
    uniform_int_distribution<int> distribution(1, get_h() - 1);

    while (true) {
        int rand_x = distribution(generator);
        int current_x;

        for (auto &snake_element : snake.get_GameElement()) {
            current_x = snake_element.get_x();
            if (rand_x == current_x) {
                break;
            }
        }

        if (rand_x != current_x) {
            return rand_x;
        }
    }
} 

int rand_y_not_in_snake() {
    mt19937 generator(random_device{}());
    uniform_int_distribution<int> distribution(1, get_w() - 1);

    while (true) {
        int rand_y = distribution(generator);
        int current_y;

        for (auto &snake_element : snake.get_GameElement()) {
            current_y = snake_element.get_y();
            if (rand_y == current_y) {
                break;
            }
        }

        if (rand_y != current_y) {
            return rand_y;
        }
    }
}

void test_collision_food_or_body(){
    auto& food = get_Food();
}
 
private:
   
   int w;
   int h;
   
   
   Snake snake;
   Food food;

   vector <vector<GameFieldElement>> output_array;
   
};

// Предварительное объявление класса View, без этого не компилилось
class View;

class View {
    public:

 
 /*
    void print_w() {
        const int num =  controller_.get_w();
        std::cout << num << std::endl;
    }
 */

  
 void output_Array(std::vector<std::vector<GameFieldElement>> const& Output_)
 {
     int max_y, max_x;
     getmaxyx(stdscr, max_y, max_x); // Получаем размеры окна
 
     // Очистим экран
     clear();
 
     // Ширина и высота игрового поля
     size_t width = Output_[0].size();
     size_t height = Output_.size();
 
     // Проверяем, чтобы размер поля был меньше размера окна
     /*
     if (height > max_y || width > max_x)
     {
         mvprintw(max_y / 2, (max_x - strlen("Поле слишком большое")) / 2,
                  "Поле слишком большое");
         refresh();
         getch();
         return;
     }
    */
 
     // Вывод верхнего края
     mvaddch(0, 0, '#');
     for (size_t i = 0; i < width; ++i)
     {
         mvaddch(0, i + 1, '-');
     }
     mvaddch(0, width + 1, '#');
 
     // Вывод содержимого поля
     for (size_t y = 0; y < height; ++y)
     {
         mvaddch(y + 1, 0, '|'); // Левый край
         for (size_t x = 0; x < width; ++x)
         {
             char ch = ' ';
             if (Output_[y][x] == GameFieldElement::Snake)
             {
                 ch = '*';
             }
             if (Output_[y][x] == GameFieldElement::Food)
             {
                 ch = '#';
             }
             mvaddch(y + 1, x + 1, ch);
         }
         mvaddch(y + 1, width + 1, '|'); // Правый край
     }
 
     // Вывод нижнего края
     mvaddch(height + 1, 0, '#');
     for (size_t i = 0; i < width; ++i)
     {
         mvaddch(height + 1, i + 1, '-');
     }
     mvaddch(height + 1, width + 1, '#');
 
     // Обновляем экран
     refresh();
 }
 
 


 private:

    
 };

class Controller {
   public:
   Controller(Model& model, View& view) : model_(model), view_(view) {
   
    initscr(); // инициализация ncurses
    cbreak(); // отключение буферизации ввода
    noecho(); // отключение эха ввода
   }


   int get_w() {
       return model_.get_w();
   }



    Snake& get_Snake(){
        return model_.get_Snake();
    }

    vector <vector<GameFieldElement>> get_Output_array(){
        return model_.get_Output_array();
    }

    void update(){
        return model_.update();
    }

    void run(){ // переписать под enum???
        char input = 'd'; // костыль запускает игру, змея движется ВПРАВО (RIGTH)
        while(true){
            //char input=getch();
            cbreak();
            nodelay(stdscr, true);
            set_direction(input);
            input=getch();
            model_.update();
            view_.output_Array(model_.get_Output_array());
            //input=getch();
            this_thread::sleep_for(std::chrono::milliseconds(500));

        }
    }

    void set_direction(char input){


       // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(input){
        case ('a'):model_.set_direction(Direction::LEFT); break;
        case ('d'):model_.set_direction(Direction::RIGHT); break;
        case ('w'):model_.set_direction(Direction::UP); break;
        case ('s'):model_.set_direction(Direction::DOWN); break;
        default: break;}

    }


private:
   Model &model_;
   View &view_;
   
};



int main() {
   Model model(30, 15);
   View view;
   Controller controller(model, view);

controller.run();


   return 0;
}