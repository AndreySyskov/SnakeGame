#include <iostream>
using namespace std;


class Model {
   public:
   Model() : num_(0) {}


   void increment() {
       ++num_;
   }


   int getNum() const noexcept {
       return num_;
   }


   void setNum(int num) {
       num_ = num;
   }

   void move(int num){
    
   }


private:
   int num_;
};


class Controller {
   public:
   Controller(Model& model) : model_(model) {}


   int getNum() {
       return model_.getNum();
   }


   void setNum(int num) {
       model_.setNum(num);
   }


private:
   Model &model_;
};


class View {
   public:
   View(Controller &controller) : controller_(controller) {}


   void printNum() {
       const int num =  controller_.getNum();
       std::cout << num << std::endl;
   }


   void inputNum() {
       int num;
       std::cin >> num;
       controller_.setNum(num);
   }
private:
   Controller &controller_;
};


int main() {
   Model model;
   Controller controller(model);
   View view(controller);


   view.printNum();


  
   return 0;
}
